#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "model/basic_types/whole.h"

class Threshold : public Whole
{
public:
  Threshold();
  Threshold(const unsigned long int &in_value);
};

inline Threshold::Threshold() : Whole()
{
}

inline Threshold::Threshold(const unsigned long int &in_value) : Whole(in_value)
{
}

#endif // THRESHOLD_H
