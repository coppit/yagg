#ifndef [[[$nonterminal]]]_h
#define [[[$nonterminal]]]_h

#include "generator/rule/nonterminal_rule.h"
#include "model/utility/nonterminal_utility.h"

#include <list>
#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
#include <map>
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION

using namespace std;

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
]]]  virtual void Reset_String();

  virtual const bool Check_For_String();
  virtual const list<string> Get_String() const;

#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
public:
  [[[$nonterminal]]]();

protected:
  [[[$nonterminal]]](const [[[$nonterminal]]] &in_[[[$nonterminal]]]);

  virtual const [[[$nonterminal]]]& operator= (const [[[$nonterminal]]] &in_[[[$nonterminal]]]);

protected:
  // Caching implementation
  static map<const unsigned int, list< list< string> > > m_generated_cache;
  static map<const unsigned int, list< list< string> > > m_intermediate_cache;
  static map<const unsigned int, searchable_list< [[[$nonterminal]]]* > > m_active_terminals;
  list< list< string > >::const_iterator m_current_string_list;
  bool m_first_cache_string;
  bool m_using_cache;
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
};

#endif // [[[$nonterminal]]]_h
