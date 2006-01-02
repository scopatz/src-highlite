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
#ifndef REGEXPREPROCESSOR_H
#define REGEXPREPROCESSOR_H

#include <string>

/**
preprocess a regular expression, e.g., transform "()" into "(?:)"

@author Lorenzo Bettini
*/
class RegexPreProcessor{
public:
    RegexPreProcessor();

    ~RegexPreProcessor();

    static const std::string preprocess(const std::string &s);
    static const std::string make_nonsensitive(const std::string &s);
};

#endif
