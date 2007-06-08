//
// C++ Implementation: languageinfer
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "languageinfer.h"
#include "fileutil.h"

#include <boost/regex.hpp>

using namespace std;

LanguageInfer::LanguageInfer()
{
}


LanguageInfer::~LanguageInfer()
{
}

const string LanguageInfer::infer( const string &filename )
{
  istream *stream = open_file_istream_or_error(filename);

  string result = infer(*stream);

  delete stream;

  return result;
}

const string LanguageInfer::infer( istream &stream )
{
  // the regular expression for finding the language specification in a script file
  // this such as #! /bin/bash
  boost::regex langRegEx("#[[:blank:]]*![[:blank:]]*(?:[\\./]*)(?:[[:alnum:]]+[\\./]+)*([[:alnum:]]+)");

  // the regular expression for finding the language specification in a script file
  // this such as #! /usr/bin/env perl
  boost::regex langEnvRegEx("#[[:blank:]]*![[:blank:]]*(?:[\\./]*)(?:[[:alnum:]]+[\\./]+)*(?:env)[[:blank:]]+([[:alnum:]]+)");
  
  // the regular expression for finding the language specification in a script file
  // according to Emacs convention: # -*- language -*-
  boost::regex langRegExEmacs("-\\*-[[:blank:]]*([[:alnum:]]+).*-\\*-");

  // the Emacs specification has the precedence in order to correctly infer
  // that scripts of the shape
  // #!/bin/sh
  // #  -*- tcl -*-
  // are Tcl scripts and not shell scripts

  string firstLine;
  string secondLine;

  // read only the first line of the input
  read_line(&stream, firstLine);
  // and the second line
  read_line(&stream, secondLine);

  boost::match_results<std::string::const_iterator> what;
  boost::match_results<std::string::const_iterator> whatEnv;
  boost::match_results<std::string::const_iterator> whatEamcs;

  // first try the emacs specification
  boost::regex_search(secondLine,
                      whatEamcs, langRegExEmacs, boost::match_default);

  if (whatEamcs[1].matched)
    return whatEamcs[1];
  else {
    // try also on the first line
    boost::regex_search(firstLine,
                        whatEamcs, langRegExEmacs, boost::match_default);
    if (whatEamcs[1].matched)
      return whatEamcs[1];
  }

  // try also the env specification
  boost::regex_search(firstLine,
                      whatEnv, langEnvRegEx, boost::match_default);

  if (whatEnv[1].matched)
    return whatEnv[1];
  
  // finally try the sha-bang specification
  boost::regex_search(firstLine,
                      what, langRegEx, boost::match_default);

  if (what[1].matched)
    return what[1];
  
  return "";
}
