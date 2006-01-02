//
// C++ Interface: outlangdefscanner
//
// Description: 
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef OUTLANGDEFSCANNER_H
#define OUTLANGDEFSCANNER_H

#include "parsestruct.h"

extern int outlangdef_lex() ;
extern FILE *outlangdef_in;
extern ParseStruct *outlang_parsestruct;

void open_outlang_file_to_scan(const std::string &path, const std::string &file);

#endif // OUTLANGDEFSCANNER_H
