#include "model/terminal_rules/[[[$terminal]]].h"
#include <sstream>

using namespace std;

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
  $OUT .= <<EOF;
  static $nonpointer_return_type return_value;
  return_value = $strings[0];

  return &return_value;
EOF
}
else
{
  $OUT .= "  return $return_type($strings[0]);";
}

]]]
}
