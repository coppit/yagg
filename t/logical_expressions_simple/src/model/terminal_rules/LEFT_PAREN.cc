#include "model/terminal_rules/LEFT_PAREN.h"
#include <sstream>

using namespace std;

// ---------------------------------------------------------------------------

LEFT_PAREN* LEFT_PAREN::Clone() const
{
  return new LEFT_PAREN(*this);
}

// ---------------------------------------------------------------------------

const list<string> LEFT_PAREN::Get_String() const
{
  list<string> strings;

  stringstream temp_stream;
  temp_stream << Get_Value();

  strings.push_back(temp_stream.str());
  return strings;
}

// ---------------------------------------------------------------------------

string LEFT_PAREN::Get_Value() const
{
  return string("(");
}
