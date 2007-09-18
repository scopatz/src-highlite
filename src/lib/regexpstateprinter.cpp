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
#include "regexpreprocessor.h"

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
  do_indent;
  cout << " regexp " << state->reg_exp <<
      (state->has_alternative() ? " (has alternatives)" : "") <<
      (state->hasReferences ? " (has references)" : "") << endl;

  inc_indent;

  unsigned int i = 0;
  if (state->allAlternativesCanMatch) {
      // print the default formatter
      do_indent;
      cout << i << ": " << state->formatters[0]->elem << " ";
      printRegExpFormatter(state->formatters[0]);
      
      // we need to get all the subexpressions
      const subexpressions_strings *split = RegexPreProcessor::split_marked_subexpressions(state->reg_exp.str());
      
      i = 1;
      for (subexpressions_strings::const_iterator it = split->begin(); it != split->end(); ++it) {
          do_indent;
          cout << i << ": " << state->formatters[i]->elem << " "
                  << *it ;
          ++i;
          if (i < state->formatters.size())
              cout << endl;
      }

      // and print only the last state which has all the next state
      // and exit level information
      do_indent;
      printRegExpFormatter(state->formatters[i-1]);

      delete split;
  } else {
      for (format_vector::const_iterator it =  state->formatters.begin();
           it != state->formatters.end(); ++it)
      {
        do_indent;
        cout << i << ": " << (*it)->elem << " "
            << (i > 0 ? state->subExpressions[i-1].first : "");
        printRegExpFormatter(*it);
        ++i;
      }
  }

  dec_indent;

  if (state->alternative.get())
      printRegExpState(state->alternative);
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
