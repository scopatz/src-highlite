//
// C++ Implementation: regexpstateprinter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpstateprinter.h"

#include <iostream>

#define INDENT_INC 2
#define inc_indent (indent += INDENT_INC)
#define dec_indent (indent -= INDENT_INC)
#define do_indent cout << (indent ? string(indent, ' ') : "");

using namespace std;

RegExpStatePrinter::RegExpStatePrinter() : indent(0)
{
}


RegExpStatePrinter::~RegExpStatePrinter()
{
}

void RegExpStatePrinter::printRegExpState(RegExpStatePtr state)
{
  do_indent;
  cout << " STATE " << state->id << endl;

  inc_indent;

  int i = 0;
  for (format_vector::const_iterator it =  state->formatters.begin();
       it != state->formatters.end(); ++it)
  {
    do_indent;
    cout << i << ": " << (*it)->elem << " "
        << (i > 0 ? state->subExpressions[i-1].first : "");
    printRegExpFormatter(*it);
    ++i;
  }

  dec_indent;
}

void RegExpStatePrinter::printRegExpFormatter(RegExpFormatterPtr formatter)
{
  cout << " (exit level: " << formatter->exit_state_level << ", exit_all: " <<
      formatter->exit_all << ", next: ";

  if (formatter->getNextState()) {
    cout << formatter->getNextState()->id;
  } else {
    cout << "none";
  }

  cout << ")" << endl;

  if (formatter->getNextState()) {
    int id = formatter->getNextState()->id;
    if (stateidset.find(id) == stateidset.end()) {
      stateidset.insert(id);
      inc_indent;
      printRegExpState(formatter->getNextState());
      dec_indent;
    }
  }
}
