#include "model/terminal_rules/[[[$terminal]]].h"
[[[
if ($return_type ne 'string' && defined $nonpointer_return_type &&
    $nonpointer_return_type ne 'string' && $nonpointer_return_type ne 'char')
{
  $OUT .= "#include <sstream>";
}
]]]
#include <list>

using namespace std;

// ---------------------------------------------------------------------------

const bool [[[$terminal]]]::Check_For_String()
{

  return_value = [[[ $strings[0] ]]];

  if (!Is_Valid())
    return false;

  m_string_count++;

  if (m_string_count > 1)
    return false;

  return_value = [[[ $strings[0] ]]];

  return true;
}

// ---------------------------------------------------------------------------

const list<string> [[[$terminal]]]::Get_String() const
{
  list<string> strings;

[[[
if ($return_type ne 'string' && defined $nonpointer_return_type &&
    $nonpointer_return_type ne 'string' && $nonpointer_return_type ne 'char')
{
  $OUT .= <<EOF;
  stringstream temp_stream;
  temp_stream << return_value;

  strings.push_back(temp_stream.str());
EOF
}
else
{
  $OUT .= <<EOF;
  strings.push_back(return_value);
EOF
}
]]]
  return strings;
}

// ---------------------------------------------------------------------------

const [[[$return_type]]] [[[$terminal]]]::Get_Value() const
{
[[[
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
