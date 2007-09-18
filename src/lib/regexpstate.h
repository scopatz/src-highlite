//
// C++ Interface: RegExpState
//
// Description: as regular expression state: contains the regular expression to
// match and the formatters for each alternative.
//
//
// Author: Lorenzo Bettini, http://www.lorenzobettini.it, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPSTATE_H
#define REGEXPSTATE_H

#include <boost/regex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <deque>
#include <vector>
#include "my_sstream.h"
#include "parserinfo.h"

struct RegExpState;

typedef boost::shared_ptr<RegExpState> RegExpStatePtr;
typedef boost::weak_ptr<RegExpState> RegExpStatePtrW;

struct RegExpFormatter
{
  const std::string elem; // the element represented
  int exit_state_level; // how many states we must leave
  bool exit_all;

  RegExpFormatter(const std::string &el, RegExpStatePtr r = RegExpStatePtr(), int exit = 0, bool all = false);

  void setNextState(RegExpStatePtr r);
  RegExpStatePtr getNextState() const;

  private:
    RegExpStatePtrW next_state;
    RegExpStatePtr next_state_strong;
    /*
      FIXME
      the next_state is a weak pointer when there's a "nested" situation.
      This allows to avoid cycles, that otherwise would prevent memory from
      being correctly freed.
    */
};

typedef boost::shared_ptr<RegExpFormatter> RegExpFormatterPtr;
typedef std::deque<RegExpFormatterPtr> format_vector;
typedef std::pair<std::string, ParserInfo> SubExpressionInfo;
typedef std::vector<SubExpressionInfo> SubExpressions;

/**
class representing a state for the regular expression engine

@author Lorenzo Bettini
 */
struct RegExpState
{
  static int global_id;
  const int id; // the identifier of the state
  
  /// the regular expression (with all the alternatives) for this state
  boost::regex reg_exp;
  
  /// for each alternative keep the parser info
  SubExpressions subExpressions;
  
  /// the formatters (one for each alternative)
  format_vector formatters;
  
  /// where to buffer the expression strings (added with add_exp)
  /// when freeze is called these will be used to create the reg_exp
  std::ostringstream buffer;
  
  /// if the regular expression is not matched try with this alternative
  /// state (this is used to split regular expressions where an alternative
  /// has a back reference, since back references are limited to 9)
  RegExpStatePtr alternative;
  
  /**
   * Records that the fact that if an add_exp is invoked on this object,
   * then an alternative must be created and the exp should be inserted there
   */
  bool nextAddMustCreateAnAlternative;
  
  /**
   * Means that this state has a regular expression made up of (possible)
   * many marked subexpressions each of one is an alternative, e.g.,
   * (foo)|(#)|...
   * 
   * This is crucial since, when formatting, we need to inspect each sub_match
   * of match_result to find out which one matched (and so, which formatter to use).
   */
  bool hasMarkedAlternatives;
  
  /**
   * Means that this state has a regular expression made up of marked subexpressions
   * where all of them can match, e.g.,
   * (class)([[:blank:]]*)([[:alnum:]]+)
   * 
   * This is crucial since, when formatting, we need to inspect each sub_match of
   * match_result to find out all those that matched.  This is different from the
   * case of hasMarkedAlternatives: in that case only one can match
   */
  bool allAlternativesCanMatch;
  
  /**
   * Whether the regular expression of this state contains marked subexpressions,
   * e.g.,
   * 
   * (foo) and (bar)
   */
  bool hasSubExpressions;
  
  /**
   * Whether the regular expression of this state contains references that must
   * be substituted at run-time, e.g.,
   * 
   * foo @{1} bar
   */
  bool hasReferences;

  RegExpState() : 
      id(global_id++), formatters(1),
      nextAddMustCreateAnAlternative(false),
      hasMarkedAlternatives(false),
      allAlternativesCanMatch(false),
      hasSubExpressions(false),
      hasReferences(false) {}
  
  /**
   * Copy constructor; copy all members
   * 
   * @param state
   */
  RegExpState(const RegExpState &state) : 
        id(state.id), reg_exp(state.reg_exp),
        formatters(state.formatters), alternative(state.alternative),
        nextAddMustCreateAnAlternative(state.nextAddMustCreateAnAlternative),
        hasMarkedAlternatives(state.hasMarkedAlternatives),
        allAlternativesCanMatch(state.allAlternativesCanMatch),
        hasSubExpressions(state.hasSubExpressions),
        hasReferences(state.hasReferences) {}

  const std::string &get_elem(int index = -1);
  
  /**
   * Adds the formatter for the given regular expression (and the file info
   * of the original language definition file).
   * 
   * The expression is only buffered (i.e., the regular expression is not built
   * untile freeze is called)
   * 
   * @param s the regular expression string
   * @param parserInfo
   * @param f
   */
  void add_exp(const std::string &s, ParserInfo *parserInfo, RegExpFormatterPtr f);

  /**
   * Adds the formatters for the given regular expression (and the file info
   * of the original language definition file).  Each formatter of the passed
   * vector is related to the corresponding marked subexpression of the passed 
   * expression.
   * 
   * The expression is only buffered (i.e., the regular expression is not built
   * untile freeze is called)
   * 
   * @param s the regular expression string
   * @param parserInfo
   * @param f
   */
  void add_exp(const std::string &s, ParserInfo *parserInfo, const format_vector &f);

  /**
   * Basically the same as add_exp, but 
   * 1. creates the alternative RegExpState
   * 2. forwards all the operations to it from now on
   */
  void add_alternative(const std::string &s, ParserInfo *parserInfo, RegExpFormatterPtr f);
  
  /**
   * Sets that we added a marked subexpression
   */
  void setHasMarkedAlternatives();
  
  /**
   * Sets that we added a subexpression where all alternatives can match
   */
  void setAllAlternativesCanMatch();
  
  /**
   * Sets that we added a regular expression with marked subexpressions
   */
  void setHasSubExpressions();

  /**
   * Sets that the regexp has references
   */
  void setHasReferences();

  /**
   * Adds the formatter for a (marked) subexpression
   * 
   * @param f
   */
  void add_subexp_formatter(RegExpFormatterPtr f);
  
  /**
   * Actually build the regular expression from the buffered strings
   */
  void freeze() throw(boost::bad_expression);
  
  /**
   * The default formatter in case the regular expression is not matched
   */
  void set_default_formatter(RegExpFormatterPtr f);
  
  /**
   * @return the last formatter
   */
  RegExpFormatterPtr getLastFormatter() const;
  
  /**
   * @return whether this state has an alternative
   */
  bool has_alternative() const;
};

#endif
