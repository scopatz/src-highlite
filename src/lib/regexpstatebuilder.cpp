//
// C++ Implementation: regexpstatebuilder.cpp
//
// Description: Builds the regexp automaton
//
//
// Author: Lorenzo Bettini, 2007, http://www.lorenzobettini.it
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
#include "namedsubexpslangelem.h"
#include "regexpstate.h"
#include "stringdef.h"
#include "tostringcollection.h"
#include "regexpreprocessor.h"
#include "keys.h"
#include "messages.h"

using namespace std;

static const string buildex(const string &s);

void add_exp(RegExpStatePtr state, const string &exp, ParserInfo *parserInfo, RegExpFormatterPtr f)
{
    unsigned int numOfSubexpressions = RegexPreProcessor::num_of_subexpressions(exp);

    if (numOfSubexpressions) {
        // for marked subexpressions we must not use buildex, otherwise we might change
        // the subexpressions indexes (e.g., for backreferences)
        state->add_alternative(exp, parserInfo, f);

        // record that we (manually) added an expression with subexpressions
        state->setHasSubExpressions();
    } else {
        state->add_exp(buildex(exp), parserInfo, f);
        
        // record that we (manually) added an explicit marked subexpression
        state->setHasMarkedAlternatives();
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

void setFormatterExitLevel(StateStartLangElem *elem, RegExpFormatterPtr formatter) {
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
  if (elems) {
    for (LangElems::const_iterator it = elems->begin(); 
        it != elems->end(); ++it) {
        try {
            build_DB(*it, state);
        } catch (boost::bad_expression &e) {
            exitError("problem in this expression: " + (*it)->toStringOriginal(), *it);
        }
    }
  }

  bool problems = !freeze_state(state);

  if (!problems)
    return;

  if (elems) {
    // try to find out where the problem is...
    RegExpStatePtr temp_state(new RegExpState());
    for (LangElems::const_iterator it = elems->begin(); it != elems->end(); ++it) {
      build_DB(*it, temp_state);
      try {
        temp_state->freeze();
      } catch (boost::bad_expression &e) {
        exitError("problem in this expression: " + (*it)->toStringOriginal(), *it);
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
 * Build a non-marking group (i.e., (? ... ) starting from s
 * @param s
 * @return
 */
const string non_marking_group(const string &s)
{
  return "(?:" + s + ")";
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
 * string.
 * 
 * Notice that this should be called only on strings specified in double quotes,
 * since other expressions are intended as regular expressions and should not
 * be isolated.  This is checked in the code that calls this function.
 * 
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
  string stringdef;
  
  for (StringDefs::const_iterator it = alternatives->begin(); it != alternatives->end();) {
      const string &rep = (*it)->toString();
      
      // check whether the regular expression string must be made non case sensitive
      const string &nonsensitive_processed = 
          (elem->isCaseSensitive() ? rep : 
              RegexPreProcessor::make_nonsensitive(rep));

      // this must be checked on the original string (not the one already made
      // non sensistive); however, we will use the already made nonsensitive
      if ((*it)->isDoubleQuoted() && is_to_isolate(rep)) {
          // we must make a non-marking group since the string can contain
          // alternative symbols. For instance,
          // \<(?:class|for|else)\>
          // correctly detects 'for' only in isolation, while
          // (?:\<class|for|else\>)
          // will not
          stringdef += 
              buildex_isolated(non_marking_group(nonsensitive_processed));
      } else {
          stringdef += nonsensitive_processed;
      }
      
      if (++it != alternatives->end())
          stringdef += '|'; // the alternatives separator
  }

  RegExpFormatterPtr formatter(new RegExpFormatter(name));

  // the final regexp is enclosed in (?: ) i.e., non marking group
  add_exp(state, non_marking_group(stringdef), elem, formatter);
  build(static_cast<StateStartLangElem *>(elem), state);
}

/**
 * Case of a list of language elements, each representing a 
 * marked subexpression
 * @param elem
 * @param state
 */
void
RegExpStateBuilder::build(NamedSubExpsLangElem *elem, RegExpStatePointer state)
{
    const ElementNames *elems = elem->getElementNames();
    const StringDef *regexp = elem->getRegexpDef();
    format_vector formatters;
    const string &regexp_string = regexp->toString();
    
    // first check that the number of marked subexpressions is the same of
    // the specified element names
    subexpressions_info sexps = RegexPreProcessor::num_of_marked_subexpressions(regexp_string);
    
    if (sexps.errors.size()) {
        exitError(sexps.errors, elem);
    }
    
    if (sexps.marked != elems->size()) {
        exitError("number of marked subexpressions does not match number of elements", elem);
    }
    
    // for each named group build a formatter, that corresponds to that element
    for (ElementNames::const_iterator it = elems->begin(); it != elems->end(); ++it) {
        RegExpFormatterPtr formatter = RegExpFormatterPtr(new RegExpFormatter(*it));
        // each formatter will share the same exit level, since it represents the
        // same matched regexp
        setFormatterExitLevel(elem, formatter);
        formatters.push_back(formatter);
    }
    
    // now add all the formatters for this element
    state->add_exp(regexp_string, elem, formatters);
    
    // record that all the subexpressions can match
    state->setAllAlternativesCanMatch();
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
  
  bool end_string_has_references = false;
  
  // check possible back reference markers and their correctness
  if (end && end->isBackRef() && end_string.size()) {
      backreference_info ref_info = 
          RegexPreProcessor::num_of_references(end_string);
      subexpressions_info info = 
          RegexPreProcessor::num_of_marked_subexpressions(start_string, true, true);
      
      // possible errors, e.g., unbalanced parenthesis
      if (info.errors.size()) {
          exitError(info.errors, elem);
      }
      
      // check that there are enough subexpressions as requested by the maximal
      // back reference number
      int max = ref_info.second;
      if (max > info.marked) {
          ostringstream error;
          error << max << " subexpressions requested, but only " <<
              info.marked << " found ";
          exitError(error.str(), elem);
      }
      
      end_string_has_references = true;
  }

  //printMessage("building " + name + " " + start_string + " " + end_string);

  if (! elem->getStateLangElem() &&
        ! elem->isMultiline() && escaped_string_size(start_string) == 1 &&
        escaped_string_size(end_string) == 1 &&
        ! end_string_has_references) {
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
      exp_string = start_string + non_marking_group("[^" +
          start_string +
          (end_string != start_string ? end_string : "") +
          "]") + "*" + end_string;
    } else {
      /*
      in case of a specified escape character it will use it for the
      (everything but delimiters) part.
      For instace, if in the example above the escape character is the
      backslash, the generated expression is

      <(?:[^\\<\\>]|\\.)*>
      */
      exp_string = start_string + non_marking_group("[^" +
          escape_string +
          start_string +
          (end_string != start_string ? escape_string + end_string : "") +
          "]|"+ escape_string + ".") +
          "*" + end_string;
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

    // record where the inner state has reference to replace at run-time
    if (end_string_has_references)
        inner->setHasReferences();
    
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
      add_exp(inner, end_string, elem, exit);
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
      add_exp(inner, escape_string + ".",
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
      add_exp(inner, start_string, elem, nested);
    }
  }

  if (inner) {
    inner->freeze();
  }

  RegExpFormatterPtr formatter(new RegExpFormatter(name, inner));
  add_exp(state, exp_string, elem, formatter);
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

  setFormatterExitLevel(elem, formatter);
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



