//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpstate.h"

#include "keys.h"
#include "messages.h"

#include <stdlib.h>

using namespace std;

int RegExpState::global_id = 1;

RegExpFormatter::RegExpFormatter(const string &el, RegExpStatePtr r, int exit, bool all) :
    elem(el), exit_state_level(exit), exit_all(all), next_state(r)
{
}

void RegExpFormatter::setNextState(RegExpStatePtr r)
{
  next_state_strong = r;
}

RegExpStatePtr RegExpFormatter::getNextState() const
{
  RegExpStatePtr next = next_state.lock();
  if (!next)
    return next_state_strong;

  return next;
}

/**
 * Return the formatter associated to the passed index.
 * If the index is negative, it returns the default formatter.
 * @param index
 * @return
 */
const string &
RegExpState::get_elem(int index)
{
  return formatters[(index<0 ? 0 : index)]->elem;
}

void
RegExpState::add_exp(const std::string &s, ParserInfo *parserInfo, RegExpFormatterPtr f)
{
  const string &ex = buffer.str();
  if (ex.size())
    buffer << "|";

  buffer << s;

  formatters.push_back(f);
  subExpressions.push_back(make_pair(s, *parserInfo));
}

void
RegExpState::freeze() throw(boost::bad_expression)
{
  const string &buffered = buffer.str();
  try {
    reg_exp.assign(buffered);
  } catch (boost::bad_expression &e) {
    printError("bad expression: " + buffered);
    throw e;
  }
}

void
RegExpState::set_default_formatter(RegExpFormatterPtr f)
{
  formatters[0] = f;
}
