#include "model/nonterminal_rules/[[[$nonterminal]]].h"
#include <cassert>

[[[

  my %rules;
  foreach my $production (@productions)
  {
    foreach my $rule (@{$production->{'rules'}})
    {
      $rules{$rule} = 1;
    }
  }

  # Sort so that output files can more easily be compared
  foreach my $rule (sort keys %rules)
  {
    next if $rule eq $nonterminal;

    if (grep { $_ eq $rule } @{$grammar->{'TERMINALS'}})
    {
      $OUT .= qq{#include "model/terminal_rules/$rule.h"\n};
    }
    else
    {
      $OUT .= qq{#include "model/nonterminal_rules/$rule.h"\n};
    }
  }
]]]
#include <list>

using namespace std;
[[[
foreach my $i (1..$#productions+1)
{
    $OUT .=<<EOF;

// ---------------------------------------------------------------------------

class ${nonterminal}::match_$i : public Rule_List
{
  friend class $nonterminal;
EOF

    $OUT .= "\n  $return_type dollar_dollar;\n"
      if defined $return_type;

    # -----------------------------------------------------------
    # Constructor

    $OUT .=<<EOF;

  match_$i()
  {
EOF

    $OUT .= "    dollar_dollar = new $nonpointer_return_type;\n\n"
      if defined $nonpointer_return_type;

    foreach my $rule (@{$productions[$i-1]{'rules'}})
    {
      $OUT .= "    push_back(new $rule);\n";
    }

    $OUT .=<<EOF;
  }
EOF

    # -----------------------------------------------------------
    # Destructor

    if (defined $nonpointer_return_type)
    {
      $OUT .=<<EOF;

  ~match_$i()
  {
    delete dollar_dollar;
  }
EOF
    }

    # -----------------------------------------------------------
    # Do_Action

    if(defined $productions[$i-1]{'action code'})
    {
      $OUT .=<<EOF;

  void Do_Action()
  {
EOF

      $OUT .= "    $return_type old_dollar_dollar = dollar_dollar;\n"
        if defined $nonpointer_return_type;

      $OUT .= $productions[$i-1]{'action code'} . "\n";

      $OUT .= "\n    if (dollar_dollar != old_dollar_dollar)\n" .
              "      delete old_dollar_dollar;\n"
        if defined $nonpointer_return_type;

      $OUT .=<<EOF;
  }
EOF
    }

    # -----------------------------------------------------------
    # Undo_Action

    if(defined $productions[$i-1]{'unaction code'})
    {
      $OUT .=<<EOF;

  void Undo_Action()
  {
$productions[$i-1]{'unaction code'}
  }
EOF
    }

    # -----------------------------------------------------------
    # Get_Value

    if (defined $return_type)
    {
      $OUT .=<<EOF;

  $return_type Get_Value() const
  {
EOF
      if (defined $nonpointer_return_type)
      {
        $OUT .=<<EOF;
    // We return a copy when dollar_dollar is a pointer, since this function
    // is called multiple times
    return new $nonpointer_return_type(*dollar_dollar);
EOF
      }
      else
      {
        $OUT .=<<EOF;
    return $return_type(dollar_dollar);
EOF
      }

    $OUT .=<<EOF;
  }
EOF

    }
    $OUT .=<<EOF;

};
EOF
}
]]]
// ---------------------------------------------------------------------------

[[[$nonterminal]]]::[[[$nonterminal]]]() : Nonterminal_Rule()
{
[[[
  foreach my $i (1..$#productions+1)
  {
    $OUT .= "  m_$i = NULL;\n";
  }
]]]}

// ---------------------------------------------------------------------------

[[[$nonterminal]]]::~[[[$nonterminal]]]()
{
[[[
  foreach my $i (1..$#productions+1)
  {
    $OUT .= <<EOF;
  if (m_$i != NULL)
    delete m_$i;
EOF
  }
]]]}

// ---------------------------------------------------------------------------

void [[[$nonterminal]]]::Initialize(const unsigned int in_allowed_length, const Rule *in_previous_rule)
{
  m_rule_lists.clear();
[[[
  foreach my $i (1..$#productions+1)
  {
    my $operator = $productions[$i-1]{'length constraint'} =~ /^=/ ? '==' : '>=';
    my ($number) = $productions[$i-1]{'length constraint'} =~ /(\d+)/;

    $OUT .=<<"EOF";

#ifndef DISABLE_PRODUCTION_LENGTH_OPTIMIZATION
  if (in_allowed_length $operator $number)
#endif // DISABLE_PRODUCTION_LENGTH_OPTIMIZATION
  {
    if (m_$i == NULL)
      m_$i = new match_$i;

    m_rule_lists.push_back(m_$i);
  }
EOF
  }

  $OUT .= "\n  Nonterminal_Rule::Initialize(in_allowed_length, in_previous_rule);\n";
  $OUT .= "}\n";

  if (defined $return_type)
  {
    $OUT .=<<EOF;

// ---------------------------------------------------------------------------

$return_type ${nonterminal}::Get_Value() const
EOF
    $OUT .= "{\n";

    foreach my $i (1..$#productions+1)
    {
      $OUT .=<<EOF;
  if (match_$i* the_rule_list = dynamic_cast<match_$i*>(*m_current_rule_list))
    return the_rule_list->Get_Value();

EOF
    }

    $OUT .= "  assert(false);\n\n";

    if (defined $nonpointer_return_type)
    {
      $OUT .= "  return new $nonpointer_return_type();\n";
    }
    else
    {
      $OUT .= "  return $return_type();\n";
    }

    $OUT .= "}\n";
  }

  chomp $OUT;
]]]
