#ifndef BINARY_OPERATOR_h
#define BINARY_OPERATOR_h

#include "generator/rule/terminal_rule.h"
#include "model/utility/terminal_utility.h"

class BINARY_OPERATOR : public Terminal_Rule
{
public:
  virtual BINARY_OPERATOR* Clone() const;

  virtual const bool Check_For_String();
  virtual const list<string> Get_String() const;
  virtual string Get_Value() const;
};

#endif // BINARY_OPERATOR_h
