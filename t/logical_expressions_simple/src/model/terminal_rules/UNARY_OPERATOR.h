#ifndef UNARY_OPERATOR_h
#define UNARY_OPERATOR_h

#include "generator/rule/terminal_rule.h"
#include "model/utility/terminal_utility.h"

class UNARY_OPERATOR : public Terminal_Rule
{
public:
  virtual UNARY_OPERATOR* Clone() const;

  virtual const list<string> Get_String() const;
  virtual string Get_Value() const;
};

#endif // UNARY_OPERATOR_h
