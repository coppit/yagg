#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

#include "generator/utility/utility.h"
#include "generator/rule_list/rule_list.h"
#include "generator/rule/terminal_rule.h"

// ---------------------------------------------------------------------------

class NATURAL : public Terminal_Rule
{
public:
  virtual NATURAL* Clone() const { return new NATURAL(*this); }

  virtual const bool Check_For_String()
  {
    if (!Is_Valid())
      return false;

    m_string_count++;

    return (m_string_count <= 3);
  }

  virtual const list<string> Get_String() const
  {
    assert(m_string_count <= 3);

    list<string> strings;

    if (m_string_count == 1)
      strings.push_back("1");
    else if (m_string_count == 2)
      strings.push_back("15");
    else
      strings.push_back("20");

    return strings;

  }
};

// ---------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  list< list< string > > results;

  {
    NATURAL start;

    start.Initialize(1);

    while(start.Check_For_String())
    {
      results.push_back( start.Get_String() );
    }
  }

  bool error = false;

  list< list< string > > expected_results;

  {
    list<string> temp_string_list;
    temp_string_list.push_back("1");
    expected_results.push_back(temp_string_list);
  }

  {
    list<string> temp_string_list;
    temp_string_list.push_back("15");
    expected_results.push_back(temp_string_list);
  }

  {
    list<string> temp_string_list;
    temp_string_list.push_back("20");
    expected_results.push_back(temp_string_list);
  }

  if (expected_results != results)
  {
    cout << "Lists do not match" << endl;

    {
      cout << endl << "Expected:" << endl;
      list< list<string> >::const_iterator a_list;
      for(a_list = expected_results.begin();
          a_list != expected_results.end();
          a_list++)
      {
        cout << Utility::to_string((*a_list).begin(), (*a_list).end());
      }
    }

    {
      cout << endl << "Actual:" << endl;
      list< list<string> >::const_iterator a_list;
      for(a_list = results.begin();
          a_list != results.end();
          a_list++)
      {
        cout << Utility::to_string((*a_list).begin(), (*a_list).end());
      }
    }

    error = true;
  }
  else
  {
    cout << "Lists match" << endl;
  }

  if (error)
    return 1;
  else
    return 0;
}
