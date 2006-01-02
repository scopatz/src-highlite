//
// C++ Implementation: langmap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <iostream>
#include <boost/regex.hpp>

#include "langmap.h"
#include "fileutil.h"
#include "messages.h"

using namespace std;

boost::regex assoc_exp("[[:blank:]]*([^[:blank:]]+)[[:blank:]]*=[[:blank:]]*([^[:blank:]\\r]+)[[:blank:]\\r]*|([[:space:]]+)");

LangMap::LangMap(const string &path, const string &filename)
{
  istream *in = open_data_file_istream(path, filename);
  string line;
  unsigned int lineno = 1;

  while (read_line(in, line)) {
    if (line.size()) {
      boost::cmatch what;
      if (! boost::regex_match(line.c_str(), what, assoc_exp))
        printError(filename, lineno, "wrong specification " + line);
      else
        if (!what[3].matched) // not all spaces
          langmap[what[1]] = what[2];
    }
    ++lineno;
  }

  delete in;
}

LangMap::~LangMap()
{
}

void
LangMap::print()
{
  for (Map::const_iterator it = langmap.begin(); it != langmap.end(); ++it)
    cout << it->first << " = " << it->second << endl;
}


