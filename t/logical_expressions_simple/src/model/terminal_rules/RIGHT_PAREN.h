#ifndef RIGHT_PAREN_h
#define RIGHT_PAREN_h

#include "generator/rule/terminal_rule.h"
#include "model/utility/terminal_utility.h"

class RIGHT_PAREN : public Terminal_Rule
{
public:
  virtual RIGHT_PAREN* Clone() const;

  virtual const list<string> Get_String() const;
  virtual string Get_Value() const;
};

#endif // RIGHT_PAREN_h
