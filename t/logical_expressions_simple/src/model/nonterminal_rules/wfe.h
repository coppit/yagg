#ifndef wfe_h
#define wfe_h

#include "generator/rule/nonterminal_rule.h"
#include "model/utility/nonterminal_utility.h"

class wfe : public Nonterminal_Rule
{
  class match_1;
  class match_2;
  class match_3;
  class match_4;

public:
  virtual wfe* Clone() const;

  virtual void Initialize(const unsigned int in_allowed_length, const Rule *in_previous_rule = NULL);
};

#endif // wfe_h
