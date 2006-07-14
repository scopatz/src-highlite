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
#include "langdefloader.h"

#include "fileutil.h"
#include "langdefparserfun.h"
#include "langelems.h"
#include "regexpstatebuilder.H"
#include "messages.h"
#include "regexpstateprinter.h"
#include "langelemsprinter.H"

#include <map>

using namespace std;

RegExpStateBuilder builder;
// moved here so that the nested lists of states and formatters are still alive
// (i.e., the shared_ptr are still reachable)

/*
  In case we process more files of the same language
  we only create the automaton for a language only once.
*/
typedef map<string, RegExpStatePtr> RegExpStateCache;

RegExpStateCache regexpstatecache;

LangDefLoader::LangDefLoader()
{
}


LangDefLoader::~LangDefLoader()
{
}

RegExpStatePtr
LangDefLoader::get_lang_def(const string &path, const string &file)
{
  const string key = (path.size() ? path + "/" : "") + file;
  RegExpStateCache::const_iterator it = regexpstatecache.find(key);
  if (it == regexpstatecache.end()) {
    printMessage("building regex automaton for " + key);
    LangElems *elems = parse_lang_def(path.c_str(), file.c_str());
    RegExpStatePtr state = builder.build(elems);
    delete elems;

    regexpstatecache[key] = state;

    return state;
  } else {
    printMessage("reusing regex automaton for " + key);
    return it->second;
  }
}

bool
LangDefLoader::check_lang_def(const string &path, const string &file)
{
  RegExpStatePtr state = get_lang_def(path, file);
  if (state.get()) {
    return true;
  }

  return false;
}

bool
LangDefLoader::show_lang_elements(const string &path, const string &file)
{
    const LangElems *elems = parse_lang_def(path.c_str(), file.c_str());

    LangElemsPrinter langelemsprinter;
    langelemsprinter.print(elems);

    delete elems;
    return true;
}

bool
LangDefLoader::show_regex(const string &path, const string &file)
{
  RegExpStatePtr state = get_lang_def(path, file);
  if (!state.get()) {
    return false;
  }

  printMessage("regex automaton:");
  RegExpStatePrinter regexpstateprinter;
  regexpstateprinter.printRegExpState(state);

  return true;
}
