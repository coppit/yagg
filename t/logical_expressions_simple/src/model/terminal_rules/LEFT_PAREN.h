#ifndef LEFT_PAREN_h
#define LEFT_PAREN_h

#include "generator/rule/terminal_rule.h"
#include "model/utility/terminal_utility.h"

class LEFT_PAREN : public Terminal_Rule
{
public:
  virtual LEFT_PAREN* Clone() const;

  virtual const list<string> Get_String() const;
  virtual string Get_Value() const;
};

#endif // LEFT_PAREN_h
