#include "model/terminal_rules/RIGHT_PAREN.h"
#include <sstream>

using namespace std;

// ---------------------------------------------------------------------------

RIGHT_PAREN* RIGHT_PAREN::Clone() const
{
  return new RIGHT_PAREN(*this);
}

// ---------------------------------------------------------------------------

const list<string> RIGHT_PAREN::Get_String() const
{
  list<string> strings;

  stringstream temp_stream;
  temp_stream << Get_Value();

  strings.push_back(temp_stream.str());
  return strings;
}

// ---------------------------------------------------------------------------

string RIGHT_PAREN::Get_Value() const
{
  return string(")");
}
