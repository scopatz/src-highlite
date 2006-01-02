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

#ifndef OUTLANGDEFPARSERFUN_H
#define OUTLANGDEFPARSERFUN_H

#include "textstyles.h"

TextStylesPtr parse_outlang_def();
TextStylesPtr parse_outlang_def(const char *path, const char *name);
TextStylesPtr parse_outlang_def_file(const char *path, const char *name);
// the second version, does not use the path for the very file,
// but only for further possible includes.

#endif
