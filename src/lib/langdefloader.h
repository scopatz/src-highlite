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
#ifndef LANGDEFLOADER_H
#define LANGDEFLOADER_H

#include <string>

#include "regexpstate.h"

/**
load a language definition file and build the RegExpState

@author Lorenzo Bettini
*/
class LangDefLoader
{
  public:
    LangDefLoader();

    ~LangDefLoader();

    static RegExpStatePtr get_lang_def(const std::string &path, const std::string &file);
    static bool check_lang_def(const std::string &path, const std::string &file);
    static bool show_lang_elements(const std::string &path, const std::string &file);
    static bool show_regex(const std::string &path, const std::string &file);
};

#endif
