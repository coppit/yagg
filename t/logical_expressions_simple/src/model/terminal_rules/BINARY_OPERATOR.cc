#include "model/terminal_rules/BINARY_OPERATOR.h"
#include <sstream>
#include <cassert>
#include <list>

using namespace std;

// ---------------------------------------------------------------------------

BINARY_OPERATOR* BINARY_OPERATOR::Clone() const
{
  return new BINARY_OPERATOR(*this);
}

// ---------------------------------------------------------------------------

const bool BINARY_OPERATOR::Check_For_String()
{
  if (!Is_Valid())
    return false;

  m_string_count++;

  return (m_string_count <= 4);
}

// ---------------------------------------------------------------------------

const list<string> BINARY_OPERATOR::Get_String() const
{
  assert(m_string_count <= 4);

  list<string> strings;

  stringstream temp_stream;
  temp_stream << Get_Value();

  strings.push_back(temp_stream.str());
  return strings;
}

// ---------------------------------------------------------------------------

string BINARY_OPERATOR::Get_Value() const
{
  assert(m_string_count <= 4);

  switch (m_string_count)
  {
    case 1 :
    {
      return string("<=>");
      break;
    }
    case 2 :
    {
      return string("and");
      break;
    }
    case 3 :
    {
      return string("or");
      break;
    }
    case 4 :
    {
      return string("=>");
      break;
    }
  }

  return string();
}
