#include "model/terminal_rules/[[[$terminal]]].h"
#include <sstream>
#include <list>
#include <set>

using namespace std;

// ---------------------------------------------------------------------------

[[[$terminal]]]* [[[$terminal]]]::Clone() const
{
  return new [[[$terminal]]](*this);
}

// ---------------------------------------------------------------------------

const bool [[[$terminal]]]::Check_For_String()
{
  if (!Is_Valid())
    return false;

  set<unsigned int> counts;

  for(const Rule *a_rule = m_previous_rule;
      a_rule != NULL; a_rule =
      a_rule->Get_Previous_Rule())
  {
    list<const Rule*> terminal_rules = a_rule->Get_Terminals();

    list<const Rule*>::const_iterator a_terminal_rule;
    for(a_terminal_rule = terminal_rules.begin();
        a_terminal_rule != terminal_rules.end();
        a_terminal_rule++)
    {
      const [[[$terminal]]] *casted_rule =
        dynamic_cast<const [[[$terminal]]]*>(*a_terminal_rule);

      if (casted_rule != NULL)
        counts.insert(casted_rule->m_string_count);
    }
  }

  m_string_count++;

  return (m_string_count <= counts.size() + 1);
}

// ---------------------------------------------------------------------------

const list<string> [[[$terminal]]]::Get_String() const
{
  list<string> strings;

  stringstream temp_stream;
[[[
  if (defined $nonpointer_return_type)
  {
    $OUT .= "  $return_type value = Get_Value();\n";
    $OUT .= "  temp_stream << *value;\n";
    $OUT .= "  delete value;\n";
  }
  else
  {
    $OUT .= "  temp_stream << Get_Value();\n";
  }
]]]
  strings.push_back(temp_stream.str());
  return strings;
}

// ---------------------------------------------------------------------------

[[[$return_type]]] [[[$terminal]]]::Get_Value() const
{
  stringstream temp_stream;
[[[
my ($prefix,$suffix) = $strings[0] =~ /^['"](.*(?<!\\))#(.*)["']$/;
$OUT .= "  temp_stream";
$OUT .= " << \"$prefix\"" if $prefix ne '';
$OUT .= " << m_string_count";
$OUT .= " << \"$suffix\"" if $suffix ne '';
$OUT .= ";\n";

if (defined $nonpointer_return_type)
{
  $OUT .= "  return new $nonpointer_return_type(temp_stream.str());";
}
else
{
  $OUT .= "  return $return_type(temp_stream.str());";
}

]]]
}
