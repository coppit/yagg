#include "model/terminal_rules/[[[$terminal]]].h"
[[[
if ($return_type ne 'string' && defined $nonpointer_return_type &&
    $nonpointer_return_type ne 'string' && $nonpointer_return_type ne 'char')
{
  $OUT .= "#include <sstream>";
}
]]]
#include <cassert>
#include <list>

using namespace std;

// ---------------------------------------------------------------------------

const bool [[[$terminal]]]::Check_For_String()
{
  if (!Is_Valid())
    return false;

  m_string_count++;

  if (m_string_count > [[[$size]]])
    return false;

  switch (m_string_count)
  {
[[[
for (my $i = 1; $i-1 < $size; $i++)
{
  $OUT .=<<"EOF";
    case $i :
    {
      return_value = $strings[$i-1];
      break;
    }
EOF
}
]]]
  }

  return true;
}

// ---------------------------------------------------------------------------

const list<string> [[[$terminal]]]::Get_String() const
{
  assert(m_string_count <= [[[$size]]]);

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
  assert(m_string_count <= [[[$size]]]);

[[[
if (defined $nonpointer_return_type)
{
  $OUT .= "  return &return_value;";
}
else
{
  $OUT .= "  return return_value;";
}
]]]
}
