#include "model/terminal_rules/UNARY_OPERATOR.h"
#include <sstream>

using namespace std;

// ---------------------------------------------------------------------------

UNARY_OPERATOR* UNARY_OPERATOR::Clone() const
{
  return new UNARY_OPERATOR(*this);
}

// ---------------------------------------------------------------------------

const list<string> UNARY_OPERATOR::Get_String() const
{
  list<string> strings;

  stringstream temp_stream;
  temp_stream << Get_Value();

  strings.push_back(temp_stream.str());
  return strings;
}

// ---------------------------------------------------------------------------

string UNARY_OPERATOR::Get_Value() const
{
  return string("-");
}
