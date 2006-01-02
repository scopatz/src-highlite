//
// C++ Implementation: regexpengine
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpengine.h"


RegExpEngine::~RegExpEngine()
{
}

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "maingeneratormap.h"
#include "keys.h"
#include "langdefloader.h"
#include "messages.h"
#include "textformatter.h"
#include "parserinfo.h"

// purpose:
// takes the contents of a file and transform to
// syntax highlighted code in html format

using namespace std;

typedef enum { FOUND_EOF=0, FOUND_NL, FOUND_END } load_line_ret;

load_line_ret
load_line(std::string& s, std::istream& is)
{
   s.erase();
   if (is.bad() || is.eof())
     return FOUND_EOF;

   char c;
   while (is.get(c))
   {
     if (c == '\n')
       return FOUND_NL;
     if (c != '\r')
       s.append(1, c);
   }

   return FOUND_END;
}

void
RegExpEngine::process_file(const char *file)
{
  istream *is = 0;

  if (file)
  {
    is = new ifstream(file);
    if (!is || ! (*is))
    {
      cerr << "Error in opening " << file
          << " for input" << endl ;
      exit(1) ;
    }
  }
  else
    is = &cin;

  std::string s;

  std::string::const_iterator start, end;
  boost::match_results<std::string::const_iterator> what;
  boost::match_flag_type flags;

  initial_state = currentstate;

  fileinfo->line = 1;

  load_line_ret ret;
  while ((ret = load_line(s, *is)) != FOUND_EOF)
    {
      bool matched = true;
      bool found_eol = false;
      start = s.begin();
      end = s.end();
      flags = boost::match_default;

      while (matched) {
        if (boost::regex_search(start, end, what, currentstate->reg_exp, flags))
          {
            string prefix = what.prefix();
            if (prefix.size())
              format(-1, prefix);

            for (unsigned int i = 1; i < what.size(); ++i) {
              if (what[i].matched) {
                format(i, string(what[i].first, what[i].second));
                if (currentstate->formatters[i]->getNextState()) {
                  enterState(i);
                } else if (currentstate->formatters[i]->exit_state_level) {
                  if (currentstate->formatters[i]->exit_all) {
                    exitAll();
                  } else {
                    exitState(currentstate->formatters[i]->exit_state_level);
                  }
                }
                start = what[i].second;
                if (!(*start)) {
                  if (found_eol)
                    matched = false; // we had already matched end of line
                  found_eol = true;
                }
                break; // no other match is possible
              }
            }

            if (what[0].first != what[0].second) // matched more than 0
              flags |= boost::match_not_bol;
          }
        else
          {
            format(-1, string(start, end));
            matched = false;
          }
      }

      if (ret == FOUND_NL)
        formatter->format_nl("\n");

      (fileinfo->line)++;
    }
    
    formatter->flush();

  if (file)
    delete is;

  currentstate = initial_state; // reset the initial state
}

void
RegExpEngine::enterState(int index)
{
  states_stack.push(currentstate);
  currentstate = currentstate->formatters[index]->getNextState();
}

void
RegExpEngine::exitState(int level)
{
  // remove additional levels
  for (int l = 1; l < level; ++l)
    states_stack.pop();

  currentstate = states_stack.top();
  states_stack.pop();
}

void
RegExpEngine::exitAll()
{
  currentstate = initial_state;
  states_stack = stack_of_states();
}

void
RegExpEngine::format(int index, const std::string &s)
{
  formatter->format(currentstate->get_elem(index), s, fileinfo);
}

