#include "model/terminal_rules/[[[$terminal]]].h"
#include <sstream>

using namespace std;

// ---------------------------------------------------------------------------

[[[$terminal]]]* [[[$terminal]]]::Clone() const
{
  return new [[[$terminal]]](*this);
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
[[[

if (defined $nonpointer_return_type)
{
  $OUT .= "  return new $nonpointer_return_type($strings[0]);";
}
else
{
  $OUT .= "  return $return_type($strings[0]);";
}

]]]
}
