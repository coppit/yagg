#include <iostream>
#include <sstream>
#include "model/[[[$starting_rule_type eq 'TERMINAL' ? 'terminal_rules' : 'nonterminal_rules']]]/[[[$starting_rule]]].h"

using namespace std;

// ---------------------------------------------------------------------------

// Made global so that anyone can call Print_Strings
[[[$starting_rule]]] start;

void Print_Strings(ostream &in_stream)
{
  const list<string> start_string_list = start.Get_String();
  bool need_space = false;

  in_stream << "--" << endl;

  list<string>::const_iterator a_string;
  for (a_string = start_string_list.begin();
       a_string != start_string_list.end();
       a_string++)
  {
    if(need_space)
      in_stream << " ";
    else
      need_space = true;

    in_stream << *a_string;

    if (a_string->size() > 0 && a_string->substr(a_string->size()-1,1) == "\n")
      need_space = false;
  }

  in_stream << endl;
}

// ---------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "You must provide a number greater than or equal to [[[$minimum_length]]]\n";
    return 1;
  }

  istringstream number_string(argv[1]);

  unsigned int allowed_length;

  number_string >> allowed_length;

  if (allowed_length < [[[$minimum_length]]])
  {
    cerr << "You must provide a number greater than or equal to [[[$minimum_length]]]\n";
    return 1;
  }

  cout << "Initializing grammar..." << endl;

  start.Initialize(allowed_length);

  cout << "Generating strings..." << endl;

  while(start.Check_For_String())
  {
#ifdef SHORT_RULE_TRACE
    Print_Strings(cerr);
#endif // SHORT_RULE_TRACE
    Print_Strings(cout);
  }

  return 0;
}
