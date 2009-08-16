package yagg::Config;

use strict;
use yagg::Grammar;

use vars qw( $VERSION %Config );

$VERSION = 0.01;

%yagg::Config = (
  'programs' => {
    'ar' => '/usr/bin/ar',
    'chmod' => '/sw/bin/chmod',
    'cp' => '/sw/bin/cp',
    'cpp' => '/usr/bin/cpp',
    'date' => '/sw/bin/date',
    'dirname' => '/sw/bin/dirname',
    'expr' => '/sw/bin/expr',
    'find' => '/usr/bin/find',
    'g++' => '/usr/bin/g++',
    'grep' => '/usr/bin/grep',
    'ln' => '/sw/bin/ln',
    'make' => '/usr/bin/make',
    'mkdir' => '/sw/bin/mkdir',
    'mv' => '/sw/bin/mv',
    'perl' => '/usr/bin/perl',
    'rm' => '/sw/bin/rm',
    'rsync' => '/usr/bin/rsync',
    'ssh' => '/usr/bin/ssh',
    'yapp' => '/usr/local/bin/yapp',
  },
);

# Same directory as yagg::Grammar.
$yagg::Config{'template_path'} =
  $INC{'yagg/Grammar.pm'};
$yagg::Config{'template_path'} =~ s/\/Grammar.pm//;
$yagg::Config{'template_path'} .= '/input_generator_code';

1;
