#ifndef ATOMIC_h
#define ATOMIC_h

#include "generator/rule/terminal_rule.h"
#include "model/utility/terminal_utility.h"

class ATOMIC : public Terminal_Rule
{
public:
  virtual ATOMIC* Clone() const;

  virtual const bool Check_For_String();
  virtual const list<string> Get_String() const;
  virtual string Get_Value() const;
};

#endif // ATOMIC_h
