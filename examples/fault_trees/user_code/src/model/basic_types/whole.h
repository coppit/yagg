#ifndef WHOLE_H
#define WHOLE_H

class Whole
{
public:
  Whole();
  Whole(const unsigned long int &in_value);

  // Automatic cast to unsigned long int
  operator unsigned long int () const;

  const Whole& operator= (const unsigned long int &in_value);
  const Whole& operator++ ();
  const Whole operator++ (int something);
  Whole& operator+=(const Whole& in_whole);

  friend bool operator== (const Whole& in_first, const Whole& in_second);
  friend bool operator< (const Whole& in_first, const Whole& in_second);
  friend bool operator> (const Whole& in_first, const Whole& in_second);

protected:
  // limit: sizeof(unsigned long int)
  unsigned long int value;
};

inline Whole::Whole()
{
  value = 0;
}

inline Whole::Whole(const unsigned long int &in_value)
{
  value = in_value;
}

inline Whole::operator unsigned long int () const
{
  return value;
}

inline const Whole& Whole::operator=(const unsigned long int& in_value)
{
  value = in_value;
  return *this;
}

inline const Whole& Whole::operator++()
{
  value++;
  return *this;
}

inline const Whole Whole::operator++(int something)
{
  Whole temporary = *this;
  value++;
  return temporary;
}

inline Whole& Whole::operator+=(const Whole& in_whole)
{
  value += in_whole.value;
  return *this;
}

inline bool operator==(const Whole& in_first, const Whole& in_second)
{
  return in_first.value == in_second.value;
}

inline bool operator<(const Whole& in_first, const Whole& in_second)
{
  return in_first.value < in_second.value;
}

inline bool operator>(const Whole& in_first, const Whole& in_second)
{
  return in_first.value > in_second.value;
}

#endif // WHOLE_H
