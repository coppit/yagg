#!/usr/bin/perl

use strict;

use Test::More;
use yagg::Config;
use Cwd;
use File::Spec::Functions qw( :ALL );

mkdir 't/temp', 0700;

plan tests => 3;

my $cwd = getcwd;

chdir 't/logical_expressions_simple';

diag "Running \"make\" on some C++ code. Please be patient...";

my $testname = [splitdir($0)]->[-1];
$testname =~ s#\.t##;

my $test_stdout = catfile($cwd,'t','temp',"${testname}.stdout");
my $test_stderr = catfile($cwd,'t','temp',"${testname}.stderr");

#---------------------------------------------------------------------------

{
  system "$yagg::Config{'programs'}{'make'} clean 1>$test_stdout 2>$test_stderr";

  if ($?)
  {
    ok(0, "Encountered an error cleaning up.\n" .
      "See $test_stdout and\n$test_stderr.\n\n");
  }
  else
  {
    ok(1, "Running make clean (first time)");
  }
}

#---------------------------------------------------------------------------

SKIP:
{
  skip("Make failed earlier",1) if $?;

  system "$yagg::Config{'programs'}{'make'} 1>$test_stdout 2>$test_stderr";

  if ($?)
  {
    ok(0, "Encountered an error building the sample code.\n" .
      "See $test_stdout and\n$test_stderr.\n\n");
  }
  elsif (!-e 'progs/generate')
  {
    ok(0, "Build succeeded, but there is no \"progs/generate\".\n" .
      "See $test_stdout and\n$test_stderr.\n\n");
  }
  else
  {
    ok(1, "Running make");
  }
}

#---------------------------------------------------------------------------

SKIP:
{
  skip("Make failed earlier",1) if $?;

  system "$yagg::Config{'programs'}{'make'} clean 1>$test_stdout 2>$test_stderr";

  if ($?)
  {
    ok(0, "Encountered an error cleaning up.\n" .
      "See $test_stdout and\n$test_stderr.\n\n");
  }
  else
  {
    ok(1, "Running make clean");
  }
}
