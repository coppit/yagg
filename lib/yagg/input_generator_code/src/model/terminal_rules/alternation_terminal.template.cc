#include "model/terminal_rules/[[[$terminal]]].h"
#include <sstream>
#include <cassert>
#include <list>

using namespace std;

// ---------------------------------------------------------------------------

const bool [[[$terminal]]]::Check_For_String()
{
  if (!Is_Valid())
    return false;

  m_string_count++;

  return (m_string_count <= [[[$size]]]);
}

// ---------------------------------------------------------------------------

const list<string> [[[$terminal]]]::Get_String() const
{
  assert(m_string_count <= [[[$size]]]);

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
  assert(m_string_count <= [[[$size]]]);
[[[
  if (defined $nonpointer_return_type)
  {
    $OUT .=<<"EOF";

  static $nonpointer_return_type return_value;
EOF
  }
]]]
  switch (m_string_count)
  {
[[[
for (my $i = 1; $i-1 < $size; $i++)
{
  if (defined $nonpointer_return_type)
  {
    $OUT .=<<"EOF";
    case $i :
    {
      return_value = $strings[$i-1];
      return &return_value;
      break;
    }
EOF
  }
  else
  {
    $OUT .=<<"EOF";
    case $i :
    {
      return $return_type($strings[$i-1]);
      break;
    }
EOF
  }
}

$OUT .=<<EOF;
  }

EOF

if (defined $nonpointer_return_type)
{
  $OUT .= "  return &return_value;";
}
else
{
  $OUT .= "  return $return_type();";
}
]]]
}
