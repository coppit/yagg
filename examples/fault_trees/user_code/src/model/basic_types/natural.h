#ifndef NATURAL_H
#define NATURAL_H

#include "model/basic_types/whole.h"

class Natural : public Whole
{
public:
  Natural();
  Natural(const unsigned long int &in_value);
};

inline Natural::Natural() : Whole()
{
}

inline Natural::Natural(const unsigned long int &in_value) : Whole(in_value)
{
}

#endif // NATURAL_H
