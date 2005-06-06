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
    'date' => '/bin/date',
    'dirname' => '/usr/bin/dirname',
    'expr' => '/bin/expr',
    'find' => '/sw/bin/find',
    'g++' => '/usr/bin/g++',
    'grep' => '/usr/bin/grep',
    'ln' => '/sw/bin/ln',
    'make' => '/sw/bin/make',
    'mkdir' => '/sw/bin/mkdir',
    'mv' => '/sw/bin/mv',
    'perl' => '/usr/bin/perl',
    'rm' => '/bin/rm',
    'rsync' => '/usr/bin/rsync',
    'ssh' => '/sw/bin/ssh',
    'yapp' => '/usr/bin/yapp',
  },
);

# Same directory as yagg::Grammar.
$yagg::Config{'template_path'} =
  $INC{'yagg/Grammar.pm'};
$yagg::Config{'template_path'} =~ s/\/Grammar.pm//;
$yagg::Config{'template_path'} .= '/input_generator_code';

1;
