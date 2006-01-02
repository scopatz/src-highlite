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

RegExpEngineDebug::RegExpEngineDebug(RegExpStatePtr v, TextFormatter* pre, FileInfo *f): RegExpEngine(v, pre, f)
{
}


RegExpEngineDebug::~RegExpEngineDebug()
{
}


void RegExpEngineDebug::enterState(int index)
{
  cout << "entering: " << currentstate->formatters[index]->getNextState()->reg_exp << endl;
  RegExpEngine::enterState(index);
}

void RegExpEngineDebug::exitAll()
{
    RegExpEngine::exitAll();
    cout << "exitingall: " << endl;
}

void RegExpEngineDebug::exitState(int level)
{
  RegExpEngine::exitState(level);

  cout << "exiting " << level << " level(s): " << currentstate->reg_exp << endl;
}

void printInfo(const SubExpressionInfo &e)
{
  cout << e.second.filename << ":" << e.second.line << ": "
      << e.first << endl;
}

void RegExpEngineDebug::format(int index, const std::string& s)
{
    RegExpEngine::format(index, s);

    if(index >= 0) {
      unsigned int i = (unsigned int)index;
      assert(i <= currentstate->subExpressions.size());

      printInfo(currentstate->subExpressions[i-1]);
    }
    cout << "formatting: \"" << s << "\" as " << currentstate->get_elem(index) << endl;
}

