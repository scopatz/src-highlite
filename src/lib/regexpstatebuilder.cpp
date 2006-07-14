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
#include "regexpstatebuilder.H"

#include <ctype.h>

#include "langelems.h"
#include "statelangelem.h"
#include "stringlistlangelem.h"
#include "delimitedlangelem.h"
#include "regexpstate.h"
#include "stringdef.h"
#include "tostringcollection.h"
#include "regexpreprocessor.h"
#include "keys.h"
#include "messages.h"

using namespace std;

static const string buildex(const string &s);
static const string buildex_pre(const string &s);

void add_exp(RegExpStatePtr state, const string &orig, const string &exp, ParserInfo *parserInfo, RegExpFormatterPtr f)
{
  try {
    state->add_exp(exp, parserInfo, f);
  } catch (boost::bad_expression &e) {
    exitError("wrong original expression: " + orig);
  }
}


/**
 * Definitely associate the regular expression to this state
 * @param state
 * @return
 */
bool freeze_state(RegExpStatePtr state)
{
  bool ok = true;
  try {
    state->freeze();
  } catch (boost::bad_expression &e) {
    ok = false;
  }

  return ok;
}

RegExpStateBuilder::RegExpStateBuilder()
{
}

RegExpStateBuilder::~RegExpStateBuilder()
{
}

RegExpStatePtr
RegExpStateBuilder::build(LangElems *elems)
{
  if (! elems)
    return RegExpStatePtr();

  RegExpStatePtr state(new RegExpState);
  state->set_default_formatter(RegExpFormatterPtr(new RegExpFormatter(NORMAL)));
  build(elems, state);

  return state;
}

void
RegExpStateBuilder::build(LangElems *elems, RegExpStatePointer state)
{
  if (elems)
    for (LangElems::const_iterator it = elems->begin(); it != elems->end(); ++it)
      build_DB(*it, state);

  bool problems = !freeze_state(state);

  if (!problems)
    return;

  if (elems) {
    // try to find out where the problem is...
    RegExpStatePtr temp_state(new RegExpState());
    for (LangElems::const_iterator it = elems->begin(); it != elems->end(); ++it) {
      build(*it, temp_state);
      try {
        temp_state->freeze();
      } catch (boost::bad_expression &e) {
        exitError("problem in this expression: " + (*it)->toString());
      }
    }
  } else {
    foundBug("bug in expression parsing", __FILE__, __LINE__);
  }
}

void
RegExpStateBuilder::build(LangElem *elem, RegExpStatePointer state)
{
}

/**
 * Build a subexpression starting from s
 * @param s
 * @return
 */
const string buildex(const string &s)
{
  return "(" + s + ")";
}

/**
 * Build a subexpression starting from s, after preprocessing s
 * @param s
 * @return
 */
const string buildex_pre(const string &s)
{
  return buildex(RegexPreProcessor::preprocess(s));
}

/**
 * Build a regular expression that must be matched
 * with a null string before and after (operator \< and \>)
 * @param s
 * @return
 */
const string buildex_isolated(const string &s)
{
  return "\\<" + s + "\\>";
}

/**
 * An expression is isolated basically if it is an alphanumerical
 * string
 * TODO check whether this is actually correct in principle
 * @param s
 * @return
 */
bool is_to_isolate(const string &s) {
  if (s.size()) {
    if ((isalnum(s[0]) || s[0] == '_') && (isalnum(s[s.size()-1]) || s[s.size()-1] == '_'))
      return true;
  }

  return false;
}

int escaped_string_size(const string &s) {
  if (s.size() && s[0] == '\\')
    return s.size() - 1;

  return s.size();
}

/**
 * Case of a list of alternatives
 * @param elem
 * @param state
 */
void
RegExpStateBuilder::build(StringListLangElem *elem, RegExpStatePointer state)
{
  const string &name = elem->getName();

  StringDefs *alternatives = elem->getAlternatives();
  string stringdef = toStringCollection<StringDefs>(alternatives, '|');

  //printMessage("building " + name + " " + stringdef);

  // check this at this point, since, stringdef might be modified
  // e.g., if it must be case insensitive
  bool isToIsolate = is_to_isolate(stringdef);

  if (!elem->isCaseSensitive())
    stringdef = RegexPreProcessor::make_nonsensitive(stringdef);
  string exp_string = buildex_pre(stringdef);
  if (isToIsolate)
    exp_string = buildex_isolated(exp_string);

  RegExpFormatterPtr formatter(new RegExpFormatter(name));

  add_exp(state, exp_string, buildex_pre(exp_string), elem, formatter);
  build(static_cast<StateStartLangElem *>(elem), state);
}

/**
 * Case of a delimited element
 * @param elem
 * @param state
 */
void
RegExpStateBuilder::build(DelimitedLangElem *elem, RegExpStatePointer state)
{
  RegExpStatePtr inner;

  const string &name = elem->getName();

  StringDef *start = elem->getStart();
  StringDef *end = elem->getEnd();
  StringDef *escape = elem->getEscape();

  string start_string;
  if (start)
    start_string = start->toString();

  string exp_string = start_string;

  string end_string;
  if (end)
    end_string = end->toString();
  string escape_string;
  if (escape)
    escape_string = escape->toString();

  //printMessage("building " + name + " " + start_string + " " + end_string);

  if (! elem->getStateLangElem() &&
        ! elem->isMultiline() && escaped_string_size(start_string) == 1 &&
        escaped_string_size(end_string) == 1) {
    /*
    in case the expression is not the start element of a
    State/Environment and it must not spawn multiple lines, and the
    delimiters are only one character, build a regular
    expression of the shape

    <startdelim>(everything but delimiters)<enddelim>

    For instance if delimiters are "<" and ">" the built regular expression is

    "<(?:[^<>])*>"
    */
    if (!escape) {
      exp_string = start_string + "([^" +
          start_string +
          (end_string != start_string ? end_string : "") +
          "])*" + end_string;
    } else {
      /*
      in case of a specified escape character it will use it for the
      (everything but delimiters) part.
      For instace, if in the example above the escape character is the
      backslash, the generated expression is

      <(?:[^\\<\\>]|\\.)*>
      */
      exp_string = start_string + "([^" +
          escape_string +
          start_string +
          (end_string != start_string ? escape_string + end_string : "") +
          "]|"+ escape_string + "." +
          ")*" + end_string;
    }
  } else {
    /*
    Otherwise we cannot simply build a regular expression as above but
    we must build more states of the automaton:
    if we match the start delimiter we enter a new state,
    called here "inner"
    */
    inner = RegExpStatePtr(new RegExpState); // for internal elements
    nested_states.push_back(inner);

    /*
    Since this is a delimited element, everything inside this element,
    that does not match anything else, must be formatted in the same
    way of this element.
    */
    inner->set_default_formatter(RegExpFormatterPtr(new RegExpFormatter(name)));

    /*
    We exit from this state when we match the end delimiter
    (or the end of buffer if no end delimiter was specified).

    For instance, consider this definition
    comment delim "[*" "*]"

    The inner state will contain the regular expression
    \*\]
    and when matched it will exit from the inner state.

    Notice that if this element has been specified with "exit"
    we must increment the synthetized "exit" RegExpFormatter,
    since it must exit the inner state and the state this
    element belongs to.
    */
    RegExpFormatterPtr exit
        (new RegExpFormatter(name, RegExpStatePtr(),
         1 + (elem->doExit() ? 1 : 0),
         elem->exitAll()));
    if (end)
      add_exp(inner, end_string, buildex_pre(end_string), elem, exit);
    else
      inner->add_exp(buildex("\\z"), elem, exit);

    /*
    If an escape character was specified we must match also everything
    that is prefixed with the escape character.
    For instance,
    comment delim "[*" "*]" escape "\\"
    will generate the inner state
    (\*\])|(\\.)
    */
    if (escape) {
      add_exp(inner, escape_string, buildex_pre(escape_string + "."),
              elem,
              RegExpFormatterPtr(new RegExpFormatter(name)));
    }

    /*
    If the delimited element can be nested (e.g., C comments)
    we must deal with counted occurrences of start delimiter and
    end delimiter.
    We thus create a "nested" formatter, that has as the next state the
    inner we saw above.
    We then add to the "inner" state above the start delimiter expression,
    corresponding to the "nested" formatter.
    This will implement the stack of occurrences.

    For instance, consider
    comment delim "[*" "*]" nested

    The inner state will have these expressions
    (\*\])|(\[\*)
    in case it matches the first one it will exit,
    in case it matches the second it will enter the same inner state
    */
    if (elem->isNested()) {
      RegExpFormatterPtr nested(new RegExpFormatter(name, inner));
      nested_formatters.push_back(nested);
      add_exp(inner, start_string, buildex_pre(start_string), elem, nested);
    }
  }

  if (inner) {
    freeze_state(inner);
  }

  RegExpFormatterPtr formatter(new RegExpFormatter(name, inner));
  add_exp(state, exp_string, buildex_pre(exp_string), elem, formatter);
  build(static_cast<StateStartLangElem *>(elem), state);
}

/**
 * (General) case for a lang element that can start a new
 * State/Environment.
 * @param elem
 * @param state
 */
void
RegExpStateBuilder::build(StateStartLangElem *elem, RegExpStatePointer state)
{
  RegExpFormatterPtr formatter = state->getLastFormatter();

  bool exit_all = elem->exitAll();
  bool exit = elem->doExit();

  /*
  only act on the exit state (if any exist statement is defined)
  */
  if (exit_all) {
    formatter->exit_state_level = 1;
    formatter->exit_all = true;
  }

  if (exit)
    formatter->exit_state_level = 1;
}

/**
 * Case of an element that makes a new State/Environment
 * @param elem
 * @param state
 */
void
RegExpStateBuilder::build(StateLangElem *elem, RegExpStatePointer state)
{
  StateStartLangElem *statestart = elem->getStateStart();

  /*
  First act on the element that defines this new State
  */
  build_DB(statestart, state);

  /*
  The last formatter corresponds to the formatter added for
  the element that defines this state, i.e., statestart
  */
  RegExpFormatterPtr last = state->getLastFormatter();

  /*
  We must make sure that this formatter has a next state,
  since we will use it to populate it with the elements of
  this state.

  For instance, a StringListLangElem does not have a next state,
  so we must create one.
  */
  if (!last->getNextState()) {
    last->setNextState(RegExpStatePtr(new RegExpState));
  }

  /*
  Use the last formatter next state to populate it with
  the elements of this State/Environment element
  */
  RegExpStatePtr inner(last->getNextState());

  /*
  If it's a State then the default formatter corresponds to NORMAL,
  otherwise (Environment) the default formatter is the same of
  the element itself.
  */
  if (elem->isState())
    inner->set_default_formatter(RegExpFormatterPtr(new RegExpFormatter(NORMAL)));
  else
    inner->set_default_formatter
        (RegExpFormatterPtr(new RegExpFormatter(last->elem)));

  LangElems *elems = elem->getElems();
  build(elems, inner);
}



