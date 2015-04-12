package Test::Utils;

use strict;
use Exporter;
use Test::More;
use FileHandle;
use File::Slurp;

use vars qw( @EXPORT @ISA );

@ISA = qw( Exporter );
@EXPORT = qw( Do_Diff Module_Installed %PROGRAMS
  Broken_Pipe No_such_file_or_directory $single_quote $command_separator
  $set_env
);

use vars qw( %PROGRAMS $single_quote $command_separator $set_env );

if ($^O eq 'MSWin32')
{
  $set_env = 'set';
  $single_quote = '"';
  $command_separator = '&';
}
else
{
  $set_env = '';
  $single_quote = "'";
  $command_separator = '';
}

%PROGRAMS = (
 'tzip' => undef,
 'gzip' => '/usr/cs/contrib/bin/gzip',
 'compress' => '/usr/cs/contrib/bin/gzip',
 'bzip' => undef,
 'bzip2' => undef,
);

# ---------------------------------------------------------------------------

sub Do_Diff
{
  my $filename = shift;
  my $output_filename = shift;
  my $exclude_pattern = shift;

  local $Test::Builder::Level = 2;

  my @data1 = read_file($filename);
  @data1 = grep { !/$exclude_pattern/ } @data1 if defined $exclude_pattern;

  my @data2 = read_file($output_filename);

  is_deeply(\@data1,\@data2,"$filename compared to $output_filename");
}

# ---------------------------------------------------------------------------

sub Module_Installed
{
  my $module_name = shift;

  $module_name =~ s/::/\//g;
  $module_name .= '.pm';

  foreach my $inc (@INC)
  {
    return 1 if -e "$inc/$module_name";
  }

  return 0;
}

# ---------------------------------------------------------------------------

sub No_such_file_or_directory
{
  my $filename = 0;

  $filename++ while -e $filename;

  local $!;

  my $foo = new FileHandle;
  $foo->open($filename);

  die q{Couldn't determine local text for "No such file or directory"}
    if $! eq '';

  return $!;
}

# ---------------------------------------------------------------------------

# I think this works, but I haven't been able to test it because I can't find
# a system which will report a broken pipe. Also, is there a pure Perl way of
# doing this?
sub Broken_Pipe
{
  mkdir 't/temp', 0700;

  write_file("t/temp/broken_pipe.pl", <<EOF);
unless (open B, '-|')
{
  open(F, "|$^X -pe 'print' 2>/dev/null");
  print F 'x';
  close F;
  exit;
}
EOF

  my $result = `$^X t/temp/broken_pipe.pl 2>&1 1>/dev/null`;

  $result = '' unless defined $result;

  return $result;
}

# ---------------------------------------------------------------------------

1;
