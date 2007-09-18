//
// C++ Implementation: regexpenginedebug
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpenginedebug.h"

#include <iostream>
#include <assert.h>

using namespace std;

RegExpEngineDebug::RegExpEngineDebug(RegExpStatePtr v, TextFormatter* pre, FileInfo *f): RegExpEngine(v, pre, f), interactive (false)
{
}


RegExpEngineDebug::~RegExpEngineDebug()
{
}

/**
 * Actually prints the state to stdout.
 * @param state
 */
void printRegExpState(RegExpStatePtr state)
{
  cout << state->reg_exp;
  RegExpStatePtr alternative = state->alternative;
  while (alternative.get()) {
    cout << "\n" << "  " << alternative->reg_exp;
    alternative = alternative->alternative;
  }
}

void RegExpEngineDebug::enterState(RegExpStatePtr state, int index)
{
  cout << "entering: ";
  const string &before = state->formatters[index]->getNextState()->reg_exp.str();
  printRegExpState(state->formatters[index]->getNextState());
  cout << endl;
  RegExpEngine::enterState(state, index);
  const string &after_entering = currentstate->reg_exp.str();
  
  // they could be different due to a substitution to a dynamic backreference
  if (before != after_entering) {
      cout << "current state: ";
      printRegExpState(currentstate);
      cout << endl;
  }
  //step();
}

void RegExpEngineDebug::exitAll()
{
    RegExpEngine::exitAll();
    cout << "exitingall: " << endl;
    //step();
}

void RegExpEngineDebug::exitState(int level)
{
  RegExpEngine::exitState(level);

  cout << "exiting " << level << " level(s): ";
  printRegExpState(currentstate);
  cout << endl;
  //step();
}

void printInfo(const SubExpressionInfo &e)
{
    if (!e.second.line)
        return; // it concerns a subexpressions
    
  cout << e.second.filename << ":" << e.second.line << ": "
      << e.first << endl;
}

void RegExpEngineDebug::format(int index, RegExpStatePtr state, const std::string& s)
{
    RegExpEngine::format(index, state, s);

    if(index >= 0) {
      unsigned int i = (unsigned int)index;
      assert(i <= state->subExpressions.size());

      printInfo(state->subExpressions[i-1]);
    }
    cout << "formatting: \"" << s << "\" as " << state->get_elem(index) << endl;
    step();
}

void RegExpEngineDebug::step()
{
  if (!interactive)
    return;

  // this is only a quick solution to perform interaction
  string cmd;
  getline(cin, cmd);
}
