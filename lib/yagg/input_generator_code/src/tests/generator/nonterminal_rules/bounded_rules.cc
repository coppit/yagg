#include <iostream>
#include <sstream>

using namespace std;

#include "generator/utility/utility.h"
#include "generator/rule_list/rule_list.h"
#include "generator/rule/nonterminal_rule.h"
#include "generator/rule/terminal_rule.h"

// ---------------------------------------------------------------------------

class IDENTIFIER : public Terminal_Rule
{
public:
  virtual IDENTIFIER* Clone() const { return new IDENTIFIER(*this); }

  virtual const bool Check_For_String()
  {
    if (!Is_Valid())
      return false;

    set<unsigned int> counts;

    for(const Rule *a_rule = m_previous_rule;
        a_rule != NULL;
        a_rule = a_rule->Get_Previous_Rule())
    {
      list<const Rule*> terminal_rules = a_rule->Get_Terminals();

      list<const Rule*>::const_iterator a_terminal_rule;
      for(a_terminal_rule = terminal_rules.begin();
          a_terminal_rule != terminal_rules.end();
          a_terminal_rule++)
      {
        const IDENTIFIER *casted_rule =
          dynamic_cast<const IDENTIFIER*>(*a_terminal_rule);

        if (casted_rule != NULL)
          counts.insert(casted_rule->m_string_count);
      }
    }

    m_string_count++;

    return (m_string_count <= counts.size() + 1);

  }

  virtual const list<string> Get_String() const
  {
    stringstream temp_stream;

    temp_stream << "id_" << m_string_count;

    list<string> strings;
    strings.push_back(temp_stream.str());
    return strings;
  }
};

// ---------------------------------------------------------------------------

class identifier_list : public Nonterminal_Rule
{
public:
  virtual identifier_list* Clone() const { return new identifier_list(*this); }

  virtual void Initialize(const unsigned int in_allowed_length, const Rule *in_previous_rule = NULL)
  {
    list<Rule_List*>::iterator a_rule_list;
    for(a_rule_list = m_rule_lists.begin();
        a_rule_list != m_rule_lists.end();
        a_rule_list++)
      delete *a_rule_list;

    m_rule_lists.clear();

    {
      Rule_List* rule_list = new Rule_List;

      rule_list->push_back(new IDENTIFIER);
      rule_list->push_back(new IDENTIFIER);
      rule_list->push_back(new IDENTIFIER);

      m_rule_lists.push_back(rule_list);
    }

    Nonterminal_Rule::Initialize(in_allowed_length,in_previous_rule);
  }

};

// ---------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  list< list< string > > results;

  {
    identifier_list start;

    start.Initialize(3);

    while(start.Check_For_String())
    {
      results.push_back( start.Get_String() );
    }
  }

  bool error = false;

  list< list< string > > expected_results;

  {
    list<string> temp_string_list;
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_1");
    expected_results.push_back(temp_string_list);
  }

  {
    list<string> temp_string_list;
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_2");
    expected_results.push_back(temp_string_list);
  }

  {
    list<string> temp_string_list;
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_2");
    temp_string_list.push_back("id_1");
    expected_results.push_back(temp_string_list);
  }

  {
    list<string> temp_string_list;
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_2");
    temp_string_list.push_back("id_2");
    expected_results.push_back(temp_string_list);
  }

  {
    list<string> temp_string_list;
    temp_string_list.push_back("id_1");
    temp_string_list.push_back("id_2");
    temp_string_list.push_back("id_3");
    expected_results.push_back(temp_string_list);
  }

  if(results != expected_results)
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
