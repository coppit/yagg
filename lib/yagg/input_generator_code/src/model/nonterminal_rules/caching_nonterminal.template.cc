#include "model/nonterminal_rules/[[[$nonterminal]]].h"
#include <cassert>

[[[

  my %rules;
  foreach my $production (@productions)
  {
    foreach my $rule (@{$production->{'rules'}})
    {
      $rules{$rule} = 1;
    }
  }

  # Sort so that output files can more easily be compared
  foreach my $rule (sort keys %rules)
  {
    next if $rule eq $nonterminal;

    if (grep { $_ eq $rule } @{$grammar->{'TERMINALS'}})
    {
      $OUT .= qq{#include "model/terminal_rules/$rule.h"\n};
    }
    else
    {
      $OUT .= qq{#include "model/nonterminal_rules/$rule.h"\n};
    }
  }
]]]
#include <list>

using namespace std;

// ---------------------------------------------------------------------------

#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
map<const unsigned int, list< list< string> > > [[[$nonterminal]]]::m_generated_cache;
map<const unsigned int, list< list< string> > > [[[$nonterminal]]]::m_intermediate_cache;
map<const unsigned int, [[[$nonterminal]]]*> [[[$nonterminal]]]::m_intermediate_owner;
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
[[[
foreach my $i (1..$#productions+1)
{
    $OUT .=<<EOF;

// ---------------------------------------------------------------------------

class ${nonterminal}::match_$i : public Rule_List
{
  friend class $nonterminal;
EOF

    $OUT .= "\n  $return_type dollar_dollar;\n"
      if defined $return_type;

    # -----------------------------------------------------------
    # Constructor

    $OUT .=<<EOF;

  match_$i()
  {
EOF

    $OUT .= "    dollar_dollar = new $nonpointer_return_type;\n\n"
      if defined $nonpointer_return_type;

    foreach my $rule (@{$productions[$i-1]{'rules'}})
    {
      $OUT .= "    push_back(new $rule);\n";
    }

    $OUT .=<<EOF;
  }
EOF

    # -----------------------------------------------------------
    # Destructor

    if (defined $nonpointer_return_type)
    {
      $OUT .=<<EOF;

  ~match_$i()
  {
    delete dollar_dollar;
  }
EOF
    }

    # -----------------------------------------------------------
    # Do_Action

    if(defined $productions[$i-1]{'action code'})
    {
      $OUT .=<<EOF;

  void Do_Action()
  {
EOF

      $OUT .= "    $return_type old_dollar_dollar = dollar_dollar;\n"
        if defined $nonpointer_return_type;

      $OUT .= $productions[$i-1]{'action code'} . "\n";

      $OUT .= "\n    if (dollar_dollar != old_dollar_dollar)\n" .
              "      delete old_dollar_dollar;\n"
        if defined $nonpointer_return_type;

      $OUT .=<<EOF;
  }
EOF
    }

    # -----------------------------------------------------------
    # Undo_Action

    if(defined $productions[$i-1]{'unaction code'})
    {
      $OUT .=<<EOF;

  void Undo_Action()
  {
$productions[$i-1]{'unaction code'}
  }
EOF
    }

    # -----------------------------------------------------------
    # Get_Value

    if (defined $return_type)
    {
      $OUT .=<<EOF;

  $return_type Get_Value() const
  {
EOF
      if (defined $nonpointer_return_type)
      {
        $OUT .=<<EOF;
    // We return a copy when dollar_dollar is a pointer, since this function
    // is called multiple times
    return new $nonpointer_return_type(*dollar_dollar);
EOF
      }
      else
      {
        $OUT .=<<EOF;
    return $return_type(dollar_dollar);
EOF
      }

    $OUT .=<<EOF;
  }
EOF

    }
    $OUT .=<<EOF;

};
EOF
}
]]]
// ---------------------------------------------------------------------------

[[[$nonterminal]]]* [[[$nonterminal]]]::Clone() const
{
  return new [[[$nonterminal]]](*this);
}

#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
// ---------------------------------------------------------------------------

[[[$nonterminal]]]::[[[$nonterminal]]]() : Nonterminal_Rule()
{
}

// ---------------------------------------------------------------------------

[[[$nonterminal]]]::[[[$nonterminal]]](const [[[$nonterminal]]] &in_[[[$nonterminal]]]) : Nonterminal_Rule(in_[[[$nonterminal]]])
{
  *this = in_[[[$nonterminal]]];
}

// ---------------------------------------------------------------------------

const [[[$nonterminal]]]& [[[$nonterminal]]]::operator= (const [[[$nonterminal]]] &in_[[[$nonterminal]]])
{
  Nonterminal_Rule::operator=(in_[[[$nonterminal]]]);

  m_first_cache_string = in_[[[$nonterminal]]].m_first_cache_string;
  m_using_cache = in_[[[$nonterminal]]].m_using_cache;

  return *this;
}

#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
// ---------------------------------------------------------------------------

void [[[$nonterminal]]]::Initialize(const unsigned int in_allowed_length, const Rule *in_previous_rule)
{
  list<Rule_List*>::iterator a_rule_list;
  for(a_rule_list = m_rule_lists.begin();
      a_rule_list != m_rule_lists.end();
      a_rule_list++)
    delete *a_rule_list;

  m_rule_lists.clear();
[[[
  foreach my $i (1..$#productions+1)
  {
    my $operator = $productions[$i-1]{'length constraint'} =~ /^=/ ? '==' : '>=';
    my ($number) = $productions[$i-1]{'length constraint'} =~ /(\d+)/;

    $OUT .=<<"EOF";

#ifndef DISABLE_PRODUCTION_LENGTH_OPTIMIZATION
  if (in_allowed_length $operator $number)
#endif // DISABLE_PRODUCTION_LENGTH_OPTIMIZATION
    m_rule_lists.push_back(new match_$i);
EOF
  }

  $OUT .= "\n  Nonterminal_Rule::Initialize(in_allowed_length, in_previous_rule);\n";
  $OUT .= "}\n";

  if (defined $return_type)
  {
    $OUT .=<<EOF;

// ---------------------------------------------------------------------------

$return_type ${nonterminal}::Get_Value() const
EOF
    $OUT .= "{\n";

    foreach my $i (1..$#productions+1)
    {
      $OUT .=<<EOF;
  if (match_$i* the_rule_list = dynamic_cast<match_$i*>(*m_current_rule_list))
    return the_rule_list->Get_Value();

EOF
    }

    $OUT .= "  assert(false);\n\n";

    if (defined $nonpointer_return_type)
    {
      $OUT .= "  return new $nonpointer_return_type();\n";
    }
    else
    {
      $OUT .= "  return $return_type();\n";
    }

    $OUT .= "}\n";
  }

]]]
// ---------------------------------------------------------------------------

void [[[$nonterminal]]]::Reset_String()
{
#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
  if (m_generated_cache.find(m_allowed_length) != m_generated_cache.end())
  {
#ifdef SHORT_RULE_TRACE
    cerr << "RESET: " << Utility::indent << "Nonterminal: " <<
      readable_type_name(typeid(*this)) <<
      "(" << m_allowed_length << ") [Resetting cache pointer]" << endl;
#endif // SHORT_RULE_TRACE

    m_current_string_list = m_generated_cache[m_allowed_length].begin();

    m_using_cache = true;
    m_first_cache_string = true;

    return;
  }

  m_using_cache = false;

  // Since Reset_String will be called for each terminal of this kind, the
  // last one will be the one that will be incremented first. We'll keep
  // assigning ourselves as the owner--the last terminal of this kind will
  // actually be the owner.
  m_intermediate_owner[m_allowed_length] = this;
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION

  Nonterminal_Rule::Reset_String();
}

// ---------------------------------------------------------------------------

const bool [[[$nonterminal]]]::Check_For_String()
{
#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
  // We check m_using_cache in case this terminal was in the middle of
  // generating when a later one finished generating and cached its results.
  if (m_generated_cache.find(m_allowed_length) != m_generated_cache.end() &&
      m_using_cache)
  {
#ifdef SHORT_RULE_TRACE
    cerr << "CHECK: " << Utility::indent << "Nonterminal: " <<
      readable_type_name(typeid(*this)) << "(" << m_allowed_length <<
      ") [Checking cache]" << endl;
#endif // SHORT_RULE_TRACE

    if (!m_first_cache_string)
      m_current_string_list++;

    m_first_cache_string = false;

    if (m_current_string_list != m_generated_cache[m_allowed_length].end())
    {
#ifdef SHORT_RULE_TRACE
      cerr << "CHECK: " << Utility::indent <<
        "--> NONTERMINAL VALID [Using cached string]" << endl;
#endif // SHORT_RULE_TRACE

      return true;
    }
    else
    {
#ifdef SHORT_RULE_TRACE
      cerr << "CHECK: " << Utility::indent <<
        "--> NONTERMINAL NOT VALID [No cached strings]" << endl;
#endif // SHORT_RULE_TRACE

      return false;
    }
  }

  if (m_intermediate_owner[m_allowed_length] == this)
  {
    const bool more_strings = Nonterminal_Rule::Check_For_String();

    if (more_strings)
    {
      m_intermediate_cache[m_allowed_length].push_back(
        Nonterminal_Rule::Get_String());
    }
    else
    {
#ifdef SHORT_RULE_TRACE
      cerr << "CHECK: " << Utility::indent <<
        "--> NONTERMINAL NOT VALID [Caching generated strings]" << endl;
#endif // SHORT_RULE_TRACE

      m_generated_cache[m_allowed_length] =
        m_intermediate_cache[m_allowed_length];

      m_intermediate_cache[m_allowed_length].clear();
      m_intermediate_owner.erase(m_allowed_length);
    }

    return more_strings;
  }
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION

  return Nonterminal_Rule::Check_For_String();
}

// ---------------------------------------------------------------------------

const list<string> [[[$nonterminal]]]::Get_String() const
{
#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
  // We check m_using_cache in case this terminal was in the middle of
  // generating when a later one finished generating and cached its results.
  if (m_generated_cache.find(m_allowed_length) != m_generated_cache.end() &&
      m_using_cache)
    return *m_current_string_list;
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION

  return Nonterminal_Rule::Get_String();
}

// ---------------------------------------------------------------------------

const list<const Rule*> [[[$nonterminal]]]::Get_Terminals() const
{
#ifndef DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION
  if (m_generated_cache.find(m_allowed_length) != m_generated_cache.end())
    assert(false);
#endif // DISABLE_GENERATED_STRING_CACHING_OPTIMIZATION

  return Nonterminal_Rule::Get_Terminals();
}
