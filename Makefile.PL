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

exit;

# -------------------------------------------------------------------------

sub MakeParsers
{
  die "No \"yapp\" available to create the parsers\n"
    unless defined $LOCATIONS{'yapp'};

  print "Running yapp to create the parsers\n";

  system("$LOCATIONS{'yapp'} -m 'yagg::NonterminalParser' -o 'lib/yagg/NonterminalParser.pm' etc/nonterminal_parser_grammar.yp") == 0
    or die "Could not run yapp to create the NonterminalParser.pm file: $!";
  system("$LOCATIONS{'yapp'} -m 'yagg::TerminalParser' -o 'lib/yagg/TerminalParser.pm' etc/terminal_parser_grammar.yp") == 0
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
                       versions => {
                          'GNU' => { fetch => \&Get_GNU_GPP_Version,
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
                       versions => {
                          'GNU' => { fetch => \&Get_GNU_Make_Version,
                                     numbers => '[1.0,)', },
                       },
                     },
      'rm'        => { default => 'rm', argname => 'RM' },
      'find'      => { default => 'find', argname => 'FIND' },
      'ssh'       => { default => 'ssh', argname => 'SSH' },
  );

  %LOCATIONS = Get_Program_Locations(\%info);

  foreach my $program (keys %LOCATIONS)
  {
    warn "Warning: prerequisite program \"$program\" not found\n"
      unless defined $LOCATIONS{$program};
  }

  Update_Config('lib/yagg/Config.pm', \%LOCATIONS);
  Update_Makefile('examples/logical_expressions_constrained/logical_expression_parser/GNUmakefile', \%LOCATIONS);
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
    if (defined $locations{$program})
    {
      $locations{$program} = "\'$locations{$program}\'";
    }
    else
    {
      $locations{$program} = "undef";
    }
  }

  if ($code =~ /'programs'\s*=>\s*{\s*?\n([^}]+?) *}/s)
  {
    my $original_programs = $1;
    my $new_programs = '';

    foreach my $program (sort keys %locations)
    {
      $new_programs .= "    '$program' => $locations{$program},\n";
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

  foreach my $program (keys %locations)
  {
    $locations{$program} = "NONE" unless defined $locations{$program};
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

      my $new_value = $locations{ $symbol_lookup{$symbol} };
      $new_value = " $new_value" unless $middle =~ / $/;

      substr($code,pos($code) - length($value), length($value)) = $new_value;
      pos($code) = $old_pos - length($value) + length($new_value);

    }
  }

  _Write_Code($filename, $code);
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
