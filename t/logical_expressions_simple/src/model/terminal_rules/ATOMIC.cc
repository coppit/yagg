#include "model/terminal_rules/ATOMIC.h"
#include <sstream>
#include <cassert>
#include <list>

using namespace std;

// ---------------------------------------------------------------------------

ATOMIC* ATOMIC::Clone() const
{
  return new ATOMIC(*this);
}

// ---------------------------------------------------------------------------

const bool ATOMIC::Check_For_String()
{
  if (!Is_Valid())
    return false;

  m_string_count++;

  return (m_string_count <= 3);
}

// ---------------------------------------------------------------------------

const list<string> ATOMIC::Get_String() const
{
  assert(m_string_count <= 3);

  list<string> strings;

  stringstream temp_stream;
  temp_stream << Get_Value();

  strings.push_back(temp_stream.str());
  return strings;
}

// ---------------------------------------------------------------------------

string ATOMIC::Get_Value() const
{
  assert(m_string_count <= 3);

  switch (m_string_count)
  {
    case 1 :
    {
      return string("p");
      break;
    }
    case 2 :
    {
      return string("q");
      break;
    }
    case 3 :
    {
      return string("r");
      break;
    }
  }

  return string();
}
