####################################################################
#
#    This file was generated using Parse::Yapp version 1.05.
#
#        Don't edit this file, use source file instead.
#
#             ANY CHANGE MADE HERE WILL BE LOST !
#
####################################################################
package yagg::TerminalParser;
use vars qw ( @ISA );
use strict;

@ISA= qw ( Parse::Yapp::Driver );
use Parse::Yapp::Driver;

#line 1 "etc/terminal_parser_grammar.yp"

# (c) Copyright David Coppit 2004, all rights reserved.
# (see COPYRIGHT in yagg documentation for use and
# distribution# rights)
#
# Written by David Coppit <david@coppit.org>
#
# This grammar is based on that of Flex 2.54.
#
# Use: yapp -m 'yagg::TerminalParser' -o lib/yagg/TerminalParser.pm etc/terminal_parser_grammar.yp
#
# to generate the Parser module.
# 
#line 16 "etc/terminal_parser_grammar.yp"

require 5.004;

use Carp;

my($input,$lexlevel,$lineno,$old_lineno,$number_of_errors,$context);

my($token);

my(%TERMINALS,%OPTIONS,@PROLOGUES,$EPILOGUE);


sub new {
        my($class)=shift;
        ref($class)
    and $class=ref($class);

    my($self)=$class->SUPER::new( yyversion => '1.05',
                                  yystates =>
[
	{#State 0
		DEFAULT => -3,
		GOTOS => {
			'declarations' => 1,
			'goal' => 2
		}
	},
	{#State 1
		ACTIONS => {
			"%%" => 3,
			'OPTION_OP' => 6,
			'PROLOGUE' => 7
		},
		GOTOS => {
			'options' => 4,
			'declaration' => 5
		}
	},
	{#State 2
		ACTIONS => {
			'' => 8
		}
	},
	{#State 3
		ACTIONS => {
			'CHAR' => 13,
			'EOF_OP' => 18,
			'STRING' => 17,
			"[" => 12,
			'NUMBER' => 20
		},
		GOTOS => {
			'value' => 14,
			'equivalence_generator' => 9,
			'rules' => 15,
			'equivalence_alternation' => 16,
			'rule' => 10,
			'pattern' => 19,
			'alternation' => 11
		}
	},
	{#State 4
		DEFAULT => -4
	},
	{#State 5
		DEFAULT => -2
	},
	{#State 6
		DEFAULT => -8,
		GOTOS => {
			'optionlist' => 21
		}
	},
	{#State 7
		DEFAULT => -5
	},
	{#State 8
		DEFAULT => 0
	},
	{#State 9
		DEFAULT => -18
	},
	{#State 10
		DEFAULT => -11
	},
	{#State 11
		ACTIONS => {
			"|" => 22
		},
		DEFAULT => -16
	},
	{#State 12
		ACTIONS => {
			'CHAR' => 13,
			'GENERATOR_STRING' => 25,
			'STRING' => 17,
			'NUMBER' => 20
		},
		GOTOS => {
			'value' => 24,
			'alternation' => 23
		}
	},
	{#State 13
		DEFAULT => -24
	},
	{#State 14
		ACTIONS => {
			"|" => 26
		},
		DEFAULT => -15
	},
	{#State 15
		ACTIONS => {
			'CHAR' => 13,
			"%%" => 27,
			'EOF_OP' => 18,
			'STRING' => 17,
			"[" => 12,
			'NUMBER' => 20
		},
		DEFAULT => -26,
		GOTOS => {
			'value' => 14,
			'equivalence_generator' => 9,
			'epilogue_opt' => 29,
			'equivalence_alternation' => 16,
			'rule' => 28,
			'pattern' => 19,
			'alternation' => 11
		}
	},
	{#State 16
		DEFAULT => -17
	},
	{#State 17
		DEFAULT => -23
	},
	{#State 18
		DEFAULT => -14
	},
	{#State 19
		ACTIONS => {
			'RETURN' => 31,
			"{" => 30
		}
	},
	{#State 20
		DEFAULT => -25
	},
	{#State 21
		ACTIONS => {
			'OPT_PREFIX' => 33
		},
		DEFAULT => -6,
		GOTOS => {
			'option' => 32
		}
	},
	{#State 22
		ACTIONS => {
			'CHAR' => 13,
			'STRING' => 17,
			'NUMBER' => 20
		},
		GOTOS => {
			'value' => 34
		}
	},
	{#State 23
		ACTIONS => {
			"|" => 22,
			"]" => 35
		}
	},
	{#State 24
		ACTIONS => {
			"|" => 26
		}
	},
	{#State 25
		ACTIONS => {
			"]" => 36
		}
	},
	{#State 26
		ACTIONS => {
			'CHAR' => 13,
			'STRING' => 17,
			'NUMBER' => 20
		},
		GOTOS => {
			'value' => 37
		}
	},
	{#State 27
		ACTIONS => {
			'EPILOGUE' => 38
		}
	},
	{#State 28
		DEFAULT => -10
	},
	{#State 29
		DEFAULT => -1
	},
	{#State 30
		ACTIONS => {
			'RETURN' => 39
		}
	},
	{#State 31
		ACTIONS => {
			'IDENTIFIER' => 40
		}
	},
	{#State 32
		DEFAULT => -7
	},
	{#State 33
		ACTIONS => {
			"=" => 41
		}
	},
	{#State 34
		DEFAULT => -20
	},
	{#State 35
		DEFAULT => -21
	},
	{#State 36
		DEFAULT => -22
	},
	{#State 37
		DEFAULT => -19
	},
	{#State 38
		DEFAULT => -27
	},
	{#State 39
		ACTIONS => {
			'IDENTIFIER' => 42
		}
	},
	{#State 40
		ACTIONS => {
			";" => 43
		}
	},
	{#State 41
		ACTIONS => {
			'STRING' => 44
		}
	},
	{#State 42
		ACTIONS => {
			";" => 45
		}
	},
	{#State 43
		DEFAULT => -13
	},
	{#State 44
		DEFAULT => -9
	},
	{#State 45
		ACTIONS => {
			"}" => 46
		}
	},
	{#State 46
		DEFAULT => -12
	}
],
                                  yyrules  =>
[
	[#Rule 0
		 '$start', 2, undef
	],
	[#Rule 1
		 'goal', 4, undef
	],
	[#Rule 2
		 'declarations', 2, undef
	],
	[#Rule 3
		 'declarations', 0, undef
	],
	[#Rule 4
		 'declaration', 1, undef
	],
	[#Rule 5
		 'declaration', 1,
sub
#line 41 "etc/terminal_parser_grammar.yp"
{ push @PROLOGUES,$_[1]; undef }
	],
	[#Rule 6
		 'options', 2, undef
	],
	[#Rule 7
		 'optionlist', 2, undef
	],
	[#Rule 8
		 'optionlist', 0, undef
	],
	[#Rule 9
		 'option', 3,
sub
#line 52 "etc/terminal_parser_grammar.yp"
{
                          $_[3][0] =~ /^"(.*)"$/;
                          $OPTIONS{'prefix'} = $1;
                        }
	],
	[#Rule 10
		 'rules', 2, undef
	],
	[#Rule 11
		 'rules', 1, undef
	],
	[#Rule 12
		 'rule', 6,
sub
#line 65 "etc/terminal_parser_grammar.yp"
{
                          if (exists $TERMINALS{$_[4][0]})
                          {
                             _SyntaxError(0, "Terminal $_[4][0] multiply defined. Ignoring this definition.",
                                $_[4][1]);
                             return;
                          }

                          $TERMINALS{$_[4][0]} = $_[1];
			}
	],
	[#Rule 13
		 'rule', 4,
sub
#line 77 "etc/terminal_parser_grammar.yp"
{
                          if (exists $TERMINALS{$_[3][0]})
                          {
                             _SyntaxError(0, "Terminal $_[3][0] multiply defined. Ignoring this definition.",
                                $_[3][1]);
                             return;
                          }

                          $TERMINALS{$_[3][0]} = $_[1];
			}
	],
	[#Rule 14
		 'pattern', 1,
sub
#line 91 "etc/terminal_parser_grammar.yp"
{
                          {data => '""',type => 'simple'};
			}
	],
	[#Rule 15
		 'pattern', 1,
sub
#line 96 "etc/terminal_parser_grammar.yp"
{
                          {data => $_[1][0],type => 'simple'};
			}
	],
	[#Rule 16
		 'pattern', 1,
sub
#line 101 "etc/terminal_parser_grammar.yp"
{
                          $_[1];
			}
	],
	[#Rule 17
		 'pattern', 1,
sub
#line 106 "etc/terminal_parser_grammar.yp"
{
                          $_[1];
			}
	],
	[#Rule 18
		 'pattern', 1,
sub
#line 111 "etc/terminal_parser_grammar.yp"
{
                          $_[1];
			}
	],
	[#Rule 19
		 'alternation', 3,
sub
#line 118 "etc/terminal_parser_grammar.yp"
{
                          { data => [$_[1][0],$_[3][0]],type => 'alternation'};
			}
	],
	[#Rule 20
		 'alternation', 3,
sub
#line 123 "etc/terminal_parser_grammar.yp"
{
                          {data => [@{$_[1]->{'data'}},$_[3][0]],type => 'alternation'};
			}
	],
	[#Rule 21
		 'equivalence_alternation', 3,
sub
#line 130 "etc/terminal_parser_grammar.yp"
{
                          {data => $_[2]->{'data'},type => 'equivalence alternation'};
			}
	],
	[#Rule 22
		 'equivalence_generator', 3,
sub
#line 137 "etc/terminal_parser_grammar.yp"
{
                          {data => $_[2][0],type => 'equivalence generator'};
			}
	],
	[#Rule 23
		 'value', 1, undef
	],
	[#Rule 24
		 'value', 1, undef
	],
	[#Rule 25
		 'value', 1, undef
	],
	[#Rule 26
		 'epilogue_opt', 0, undef
	],
	[#Rule 27
		 'epilogue_opt', 2,
sub
#line 151 "etc/terminal_parser_grammar.yp"
{
      $EPILOGUE=$_[2]
    }
	]
],
                                  @_);
    bless($self,$class);
}

#line 156 "etc/terminal_parser_grammar.yp"


sub _Error {
    my($value)=$_[0]->YYCurval;
  
    my($what)= $$value[0] ? "input: '$$value[0]'" : "end of input";
        
    _SyntaxError(1,"Unexpected $what",$$value[1]);
}             
          
sub _Lexer {  
              
    #At EOF
        pos($$input) >= length($$input)
    and return('',[ undef, -1 ]);

    #In Epilogue section
        $lexlevel eq 'epilogue'
    and do {
        my($pos)=pos($$input);

        $old_lineno=$lineno;
        $lineno=-1;
        pos($$input)=length($$input);
        return('EPILOGUE',[ substr($$input,$pos), $old_lineno ]);
    };

    #Skip blanks
        $$input=~m{\G((?:
                            \s+           # any white space char
                        |   \#[^\n]*\n    # Perl like comments
                        |   /\*.*?\*/     # C like comments
                        |   //[^\n]*\n    # C++ like comments
                        )+)}xsgc
    and do {
        my($blanks)=$1;

        #Maybe At EOF
            pos($$input) >= length($$input)
        and return('',[ undef, -1 ]);

        $lineno+= $blanks=~tr/\n//;
    };

    $old_lineno=$lineno;

        $$input=~/\G(%%)/gc
    and do {
        if ($lexlevel eq 'declarations')
        {
          $lexlevel = 'rules';
        }
        elsif ($lexlevel eq 'rules')
        {
          $lexlevel = 'epilogue';
        }
        return($1, [ $1, $old_lineno ]);
    };

    if ($context ne 'options')
    {
          $$input=~/\Greturn\b/gc
      and return('RETURN',[ undef, $old_lineno ]);

          $$input=~/\G([A-Za-z_.][A-Za-z0-9_.]*)/gc
      and return('IDENTIFIER',[ $1, $old_lineno ]);

          $$input=~/\G("(?:[^"\\]|\\\\|\\"|\\)+?")/gc
      and do {
          my $string = $1;
          if ($string =~ /[^\\]#/)
          {
            return('GENERATOR_STRING',[ $string, $old_lineno ]);
          }
          else
          {
            return('STRING',[ $string, $old_lineno ]);
          }
      };

          ($$input=~/\G('(?:[^'\\]|\\.)')/gc)
      and do {
          return('CHAR',[ $1, $old_lineno ]);
      };

          ($$input=~/\G('(?:[^'\\]|\\.)')/gc)
      and do {
          return('CHAR',[ $1, $old_lineno ]);
      };

          ($$input=~/\G(([+-]?)(?=\d|\.\d)\d*(\.\d*)?([Ee]([+-]?\d+))?)/gc)
      and do {
          return('NUMBER',[ $1, $old_lineno ]);
      };
    }

        $$input=~/\G(%%)/gc
    and do {
        $lexlevel = 'rules';
        return($1, [ $1, $old_lineno ]);
    };

=for comment
        $$input=~/\G{/gc
    and do {
        my $code;

        my $level = 1;
        my $from=pos($$input);
        my $to;


        while($$input =~ /\G(.*?
                               (?:
                                   \#[^\n]*\n    # Perl like comments
                                 | \/\*.*?\*\/     # C like comments
                                 | \/\/[^\n]*\n    # C++ like comments
                                 | (?<!\\)'.*?(?<!\\)'  # Single-quoted strings
                                 | (?<!\\)".*?(?<!\\)"  # Double-quoted strings
                                 | ([{}]|$)         # Our match or EOF
                               )
                            )/xsgc)
        {
          if (defined $2)
          {
            if ($2 eq '}')
            {
              $level--;

              unless($level)
              {
                $to = pos($$input) - 1;
                last;
              }
            }
            elsif ($2 eq '{')
            {
              $level++;
            }
            else
            {
              $to = length $$input;
              print(2,"Unmatched { opened line $old_lineno",-1);
              last;
            }
          }
        }

        $code = substr($$input,$from,$to-$from);

        $lineno+= $code=~tr/\n//;
        return('BRACED_CODE',[ $code, $old_lineno ]);
    };
=cut

    if($lexlevel eq 'declarations') {# In declarations section
            $$input=~/\G%option/gc
        and do {
          $context = 'options';
          return('OPTION_OP',[ undef, $old_lineno ]);
        };
        if ($context eq 'options')
        {
              $$input=~/\Gprefix/gc
          and do {
            $context = '';
            return('OPT_PREFIX',[ undef, $old_lineno ]);
          };
        }

            $$input=~/\G%{/gc
        and do {
            my($code);

            my $from=pos($$input);
            my $to;

            while($$input =~ m{\G(.*?
                                         (?:
                                             \#[^\n]*\n    # Perl like comments
                                           | /\*.*?\*/     # C like comments
                                           | //[^\n]*\n    # C++ like comments
                                           | (%\}|$)         # Our match or EOF
                                         )
                                     )}xsgc)
            {
              if (defined $2)
              {
                if ($2 eq '%}')
                {
                  $to = pos($$input) - 2;
                }
                else
                {
                  $to = length $$input;
                  _SyntaxError(2,"Unmatched \%{ opened line $old_lineno",-1)
                }

                last;
              }
            }

            $code = substr($$input,$from,$to-$from);

            $lineno+= $code=~tr/\n//;
            return('PROLOGUE',[ $code, $old_lineno ]);
        };

    }
    else {# In rule section
    }

        $$input=~/\G<<EOF>>/gc
    and return('EOF_OP',[ undef, $old_lineno ]);

    #Always return something
        $$input=~/\G(.)/sg
    or  die "Parse::Yapp::Grammar::Parse: Match (.) failed: report as a BUG";

        $1 eq "\n"
    and ++$lineno;

    ( $1 ,[ $1, $old_lineno ]);

}

sub _SyntaxError {
    my($level,$message,$error_lineno)=@_;

    $message= "*".
              [ 'Warning', 'Error', 'Fatal' ]->[$level].
              "* $message, at ".
              ($error_lineno < 0 ? "eof" : "line $error_lineno").
              ".\n";

        $level > 1
    and die $message;

    warn $message;

        $level > 0
    and ++$number_of_errors;

        $number_of_errors == 20
    and die "*Fatal* Too many errors detected.\n"
}

sub Parse {
    my($self)=shift;

        @_ > 0
    or  croak("No input grammar\n");

    $input=\$_[0];

    $lexlevel='declarations';
    $lineno=1;
    $old_lineno=1;
    $number_of_errors=0;

    $token={};
    $context = '';
    %OPTIONS = ();
    %TERMINALS = ();
    @PROLOGUES = ();
    $EPILOGUE = undef;

    pos($$input)=0;

    $self->YYParse(yylex => \&_Lexer, yyerror => \&_Error);

        $number_of_errors
    and _SyntaxError(2,"Errors detected: No output",-1);

    my %parsed;

    $parsed{ 'OPTIONS' } = \%OPTIONS;
    $parsed{ 'TERMINALS' } = \%TERMINALS;
    $parsed{ 'HEAD' } = \@PROLOGUES;
    $parsed{ 'TAIL' } = $EPILOGUE;

    return \%parsed;
}


1;
