#!/usr/bin/perl

use strict;
use inc::Module::Install;

my %LOCATIONS;

Check_Custom_Installation();

print "\n", '-'x78, "\n\n";

name            ('yagg');
author          ('David Coppit <david@coppit.org>');
abstract_from   ('yagg');
version_from    ('yagg');
license         ('gpl');

install_script  ('yagg');
  
build_requires  (
                  'Test::More' => 0,
                  'File::Find' => 0,
                  'File::Spec::Functions' => 0,
                  'Cwd' => 0,
                );
requires        ( 
                  'Carp' => 0,
                  'URI' => 0,
                  'Data::Dumper' => 0,
                  'FileHandle' => 0,
                  'File::Temp' => 0,
                  'File::Path' => 0,
                  'Getopt::Std' => 0,
                  'IPC::Open3' => 0,
                  'Text::Template' => 0,
                  'Parse::Yapp::Driver' => 1.05,
                );
  
include         ('ExtUtils/AutoInstall.pm');

clean_files     ('output','t/temp');

Configure_Programs();

print "\n", '-'x78, "\n\n";

auto_include_deps ( );
auto_install    ( );
WriteAll();

print "\n", '-'x78, "\n\n";

MakeParsers();

foreach my $program (keys %LOCATIONS)
{
  warn "Warning: prerequisite program \"$program\" not found\n"
    unless defined $LOCATIONS{$program};
}

exit;

# -------------------------------------------------------------------------

sub MakeParsers
{
  die "No \"yapp\" available to create the parsers\n"
    unless defined $LOCATIONS{'yapp'}{'path'};

  print "Running yapp to create the parsers\n";

  system("$LOCATIONS{'yapp'}{'path'} -m 'yagg::NonterminalParser' -o 'lib/yagg/NonterminalParser.pm' etc/nonterminal_parser_grammar.yp") == 0
    or die "Could not run yapp to create the NonterminalParser.pm file: $!";
  system("$LOCATIONS{'yapp'}{'path'} -m 'yagg::TerminalParser' -o 'lib/yagg/TerminalParser.pm' etc/terminal_parser_grammar.yp") == 0
    or die "Could not run yapp to create the TerminalParser.pm file: $!";
}

# --------------------------------------------------------------------------

sub Configure_Programs
{
  print<<"EOF";
yagg uses a number of external programs. For security reasons, it is best if
you provide their full path. In the following prompts, we will try to guess
these paths from your Perl configuration and your \$PATH.

You MUST specify GNU make. ssh is only necessary if you plan to use the remote
execution capabilities of the -o flag. yapp is part of the Parse::Yapp Perl
module distribution.

EOF

  my %info = (
      'yapp'      => { default => 'yapp', argname => 'YAPP' },
      'ln'        => { default => 'ln', argname => 'LN' },
      'cp'        => { default => 'cp', argname => 'CP' },
      'cpp'       => { default => 'cpp', argname => 'CPP' },
      'rm'        => { default => 'rm', argname => 'RM' },
      'mv'        => { default => 'mv', argname => 'MV' },
      'grep'      => { default => 'grep', argname => 'GREP' },
      'chmod'     => { default => 'chmod', argname => 'CHMOD' },
      'rsync'     => { default => 'rsync', argname => 'RSYNC' },
      'g++'       => { default => 'g++', argname => 'CXX',
                       types    => {
                          'GNU' => { fetch => \&Get_GNU_Version,
                                     numbers => '[3.0,)', },
                       },
                     },
      'ld'        => { default => 'g++', argname => 'LD' },
      'ar'        => { default => 'ar', argname => 'AR' },
      'mkdir'     => { default => 'mkdir', argname => 'MKDIR' },
      'date'      => { default => 'date', argname => 'DATE' },
      'perl'      => { default => $^X, argname => 'PERL' },
      'dirname'   => { default => 'dirname', argname => 'DIRNAME' },
      'expr'      => { default => 'expr', argname => 'EXPR' },
      'make'      => { default => 'make', argname => 'MAKE',
                       types    => {
                          'GNU' => { fetch => \&Get_GNU_Version,
                                     numbers => '[1.0,)', },
                       },
                     },
      'rm'        => { default => 'rm', argname => 'RM' },
      'find'      => { default => 'find', argname => 'FIND',
                       types    => {
                          'Non-GNU' => { fetch => \&Get_NonGNU_Find_Version,
                                     numbers => '[0,)', },
                          'GNU' => { fetch => \&Get_GNU_Version,
                                     numbers => '[1.0,)', },
                       },
                     },
      'ssh'       => { default => 'ssh', argname => 'SSH' },
  );

  %LOCATIONS = Get_Program_Locations(\%info);

  die "Can't create parsers without \"yapp\"\n" 
    unless defined $LOCATIONS{'yapp'}{'path'};

  {
    my @missing_programs;
    foreach my $program qw(chmod perl rsync)
    {
      push @missing_programs, $program
        unless defined $LOCATIONS{$program}{'path'};
    }

    warn "You won't be able to use yapp to generate code without:\n" .
      "@missing_programs\n"
      if @missing_programs;
  }

  {
    my @missing_programs;
    foreach my $program qw(ar cp cpp chmod dirname find grep g++ ld make mkdir rm mv perl)
    {
      push @missing_programs, $program
        unless defined $LOCATIONS{$program}{'path'};
    }

    warn "You won't be able to build the generated code without:\n" .
      "@missing_programs\n"
      if @missing_programs;
  }

  Update_Config('lib/yagg/Config.pm', \%LOCATIONS);

  Update_Makefile('examples/ab/ab_parser/GNUmakefile', \%LOCATIONS);
  Update_Makefile('examples/logical_expressions_constrained/logical_expression_parser/GNUmakefile', \%LOCATIONS);

  Update_Makefile('lib/yagg/input_generator_code/GNUmakefile', \%LOCATIONS);
  Update_Makefile('t/logical_expressions_simple/GNUmakefile', \%LOCATIONS);
}

# --------------------------------------------------------------------------

sub Update_Config
{
  my $filename = shift;
  my %locations = %{ shift @_ };

  my $code = _Read_Code($filename);

  foreach my $program (keys %locations)
  {
    if (defined $locations{$program}{'path'})
    {
      $locations{$program}{'path'} = "\'$locations{$program}{'path'}\'";
    }
    else
    {
      $locations{$program}{'path'} = "undef";
    }
  }

  if ($code =~ /'programs'\s*=>\s*{\s*?\n([^}]+?) *}/s)
  {
    my $original_programs = $1;
    my $new_programs = '';

    foreach my $program (sort keys %locations)
    {
      $new_programs .= "    '$program' => $locations{$program}{'path'},\n";
    }

    $code =~ s/\Q$original_programs\E/$new_programs/;
  }
  else
  {
    die "Couldn't find programs hash in $filename";
  }

  _Write_Code($filename, $code);
}

# --------------------------------------------------------------------------

sub Update_Makefile
{
  my $filename = shift;
  my %locations = %{ shift @_ };

  my $code = _Read_Code($filename);

  $code = _Update_Makefile_Program_Locations($code, \%locations);

  $code = _Update_Makefile_Find_Code($code, $locations{'find'});

  _Write_Code($filename, $code);
}

# --------------------------------------------------------------------------

sub _Update_Makefile_Program_Locations
{
  my $code = shift;
  my %locations = %{ shift @_ };

  foreach my $program (keys %locations)
  {
    $locations{$program}{'path'} = "NONE"
      unless defined $locations{$program}{'path'};
  }

  my %symbol_lookup = (
    'LN' => 'ln',
    'CP' => 'cp',
    'CPP' => 'cpp',
    'RM' => 'rm',
    'MV' => 'mv',
    'GREP' => 'grep',
    'CHMOD' => 'chmod',
    'CXX' => 'g++',
    'LD' => 'ld',
    'AR' => 'ar',
    'MKDIR' => 'mkdir',
    'DATE' => 'date',
    'PERL' => 'perl',
    'DIRNAME' => 'dirname',
    'EXPR' => 'expr',
    'FIND' => 'find',
  );

  while ($code =~ /^([A-Z]+)(\s*=\s*)(.*)$/mg)
  {
    my $symbol = $1;
    my $middle = $2;
    my $value = $3;

    if (exists $locations{ $symbol_lookup{$symbol} })
    {
      my $old_pos = pos $code;

      my $new_value = $locations{ $symbol_lookup{$symbol} }{'path'};
      $new_value = " $new_value" unless $middle =~ / $/;

      substr($code,pos($code) - length($value), length($value)) = $new_value;
      pos($code) = $old_pos - length($value) + length($new_value);

    }
  }

  return $code;
}

# --------------------------------------------------------------------------

sub _Update_Makefile_Find_Code
{
  my $code = shift;
  my %find_info = %{ shift @_ };

  # First add in all the -E flags if we need them.
  while ($code =~ /(\$\(FIND\) +)(-E +)?(\$\(\w+\) -regex)/mg)
  {
    my $prefix = $1;
    my $flag = $2;
    my $suffix = $3;

    my $value = "$prefix$flag$suffix";

    my $old_pos = pos $code;
    my $new_value = "$prefix -E $suffix";

    $new_value = "$prefix $suffix"
      if defined $find_info{'type'} && $find_info{'type'} eq 'GNU';

    substr( $code, pos($code) - length($value), length($value)) = $new_value;
    pos($code) = $old_pos - length($value) + length($new_value);
  }

  if ($code =~ /(make_pattern\s*=\s*)(.*)$/mg)
  {
    my $prefix = $1;
    my $pattern = $2;

    my $value = "$prefix$pattern";

    my $old_pos = pos $code;
    my $new_value = "$prefix(\$(subst \$(SPACE),|,\$(1)))";

    $new_value = "$prefix\\(\$(subst \$(SPACE),\\|,\$(1))\\)"
      if defined $find_info{'type'} && $find_info{'type'} eq 'GNU';

    substr( $code, pos($code) - length($value), length($value)) = $new_value;
    pos($code) = $old_pos - length($value) + length($new_value);

  }
  else
  {
    warn "Couldn't find make_pattern in Makefile to configure it\n";
  }

  return $code;
}

# --------------------------------------------------------------------------

sub _Read_Code
{
  my $filename = shift;

  local $/ = undef;

  open SOURCE, $filename
    or die "Couldn't open file \"$filename\": $!";
  my $code = <SOURCE>;
  close SOURCE;

  return $code;
}

# --------------------------------------------------------------------------

sub _Write_Code
{
  my $filename = shift;
  my $code = shift;

  open SOURCE, ">$filename"
    or die "Couldn't open file \"$filename\": $!";
  print SOURCE $code;
  close SOURCE;
}

# --------------------------------------------------------------------------

sub Get_NonGNU_Find_Version
{
  my $program = shift;
  
  my $command = "$program -E . -regex './(R|L).*E' 2>" . File::Spec->devnull();
  my @results = `$command`;
  
  return undef unless @results;
    
  return 0;
}
