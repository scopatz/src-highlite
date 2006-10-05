//
// C++ Interface: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
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
  boost::regex reg_exp;
  SubExpressions subExpressions;
  format_vector formatters;
  std::ostringstream buffer;

  RegExpState() : id(global_id++), formatters(1) {}

  const std::string &get_elem(int index = -1);
  void add_exp(const std::string &s, ParserInfo *parserInfo, RegExpFormatterPtr f);
  void freeze();
  void set_default_formatter(RegExpFormatterPtr f);
  RegExpFormatterPtr getLastFormatter() const { return formatters[formatters.size()-1];}
};

#endif
