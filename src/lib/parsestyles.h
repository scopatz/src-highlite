//
// C++ Interface: parsestyles
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef PARSESTYLES_H
#define PARSESTYLES_H

#include "styles.h"

Styles *parseStyles(const std::string &path, const std::string &name) ;
void parseStyleError(const std::string &error) ;

#endif
