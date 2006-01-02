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
#include "regexpreprocessor.h"
#include <boost/regex.hpp>
#include "my_sstream.h"
#include <ctype.h>

using namespace std;

const boost::regex char_set_exp("\\[([^\\|]*)\\]");

RegexPreProcessor::RegexPreProcessor()
{
}


RegexPreProcessor::~RegexPreProcessor()
{
}

const string
RegexPreProcessor::preprocess(const string &s)
{
  // substitute a "(" with "(?:" if it's not followed by a ? and not preceeded by \\ char
  boost::regex from("(\\\\\\()|(\\((?!\\?))");
  string into = "(?1\\\\\\()(?2\\(\\?\\:)";

  return boost::regex_replace(s, from, into, boost::match_default | boost::format_all);
}

const string
_make_nonsensitive(const string &s)
{
  ostringstream result;

  for (string::const_iterator it = s.begin(); it != s.end(); ++it)
    if (isalpha(*it))
      result << "[" << (char)toupper(*it) << (char)tolower(*it) << "]";
    else
      result << *it;

  return result.str();
}

const string
RegexPreProcessor::make_nonsensitive(const string &s)
{
  boost::sregex_iterator m1(s.begin(), s.end(), char_set_exp);
  boost::sregex_iterator m2;

  if (m1 == m2)
    return _make_nonsensitive(s);

  ostringstream buffer;
  string prefix;
  string suffix;

  for (boost::sregex_iterator it = m1; it != m2; ++it)
  {
    prefix = it->prefix();
    suffix = it->suffix();

    if (prefix.size()) {
      buffer << _make_nonsensitive(prefix);
    }

    buffer << (*it)[0];
  }

  if (suffix.size()) {
    buffer << _make_nonsensitive(suffix);
  }

  return buffer.str();
}


