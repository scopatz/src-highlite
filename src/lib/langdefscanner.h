//
// C++ Interface: langdefscanner
//
// Description: 
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef LANGDEFSCANNER_H
#define LANGDEFSCANNER_H

#include "parsestruct.h"

extern int langdef_lex() ;
extern FILE *langdef_in;
extern ParseStruct *parsestruct;

void open_file_to_scan(const std::string &path, const std::string &file);

#endif // LANGDEFSCANNER_H
