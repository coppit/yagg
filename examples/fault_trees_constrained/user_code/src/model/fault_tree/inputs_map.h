#ifndef INPUTS_MAP_H
#define INPUTS_MAP_H

#include "model/basic_types/event.h"
#include "model/fault_tree/input_sequence.h"
#include "model/basic_types/function.h"

class Inputs_Map : public function<Event,Input_Sequence>
{
public:
  Inputs_Map();

  // Overload ()
  const Input_Sequence& operator()(const Event& in_event);
};

inline Inputs_Map::Inputs_Map()
{
}

inline const Input_Sequence& Inputs_Map::operator()(const Event& in_event)
{
  return (*this)[in_event];
}

#endif // INPUTS_MAP_H
