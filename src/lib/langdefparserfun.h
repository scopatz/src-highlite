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

#ifndef LANGDEFPARSERFUN_H
#define LANGDEFPARSERFUN_H

#include "langelems.h"

LangElems *parse_lang_def();
LangElems *parse_lang_def(const char *path, const char *name);
LangElems *parse_lang_def_file(const char *path, const char *name);
// the second version, does not use the path for the very file,
// but only for further possible includes.

#endif
