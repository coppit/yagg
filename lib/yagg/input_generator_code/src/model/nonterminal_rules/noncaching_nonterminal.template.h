#ifndef [[[$nonterminal]]]_h
#define [[[$nonterminal]]]_h

#include "generator/rule/nonterminal_rule.h"
#include "model/utility/nonterminal_utility.h"

class [[[$nonterminal]]] : public Nonterminal_Rule
{
[[[
for (my $i = 1; $i <= @productions; $i++)
{
  $OUT .= "  class match_$i;\n";
}
]]]
public:
  virtual [[[$nonterminal]]]* Clone() const;

  virtual void Initialize(const unsigned int in_allowed_length, const Rule *in_previous_rule = NULL);
[[[
if (defined $return_type)
{
  $OUT .= "\n  virtual $return_type Get_Value() const;\n";
}
]]]};

#endif // [[[$nonterminal]]]_h
