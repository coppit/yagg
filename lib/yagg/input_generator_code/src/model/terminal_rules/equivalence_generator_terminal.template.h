#ifndef [[[$terminal]]]_h
#define [[[$terminal]]]_h

#include "generator/rule/terminal_rule.h"
#include "model/utility/terminal_utility.h"

class [[[$terminal]]] : public Terminal_Rule
{
public:
  virtual const bool Check_For_String();
  virtual const list<string> Get_String() const;
  virtual [[[$return_type]]] Get_Value() const;
};

#endif // [[[$terminal]]]_h
