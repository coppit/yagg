#include "model/terminal_rules/[[[$terminal]]].h"
#include <sstream>
#include <list>
#include <map>

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

  static map<unsigned int, unsigned int> counts;

  if (counts.find(m_string_count) != counts.end())
  {
    if (counts[m_string_count] == 1)
      counts.erase(m_string_count);
    else
      counts[m_string_count]--;
  }

  m_string_count++;

  if (m_string_count <= counts.size() + 1)
  {
    counts[m_string_count]++;
    return true;
  }
  else
    return false;
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
