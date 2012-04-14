/*
 * versions.cpp
 *
 *  Created on: Apr 18, 2009
 *      Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2008
 *  Copyright: See COPYING file that comes with this distribution
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "versions.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

namespace srchilite {

const std::string Versions::getVersion() {
    return VERSION;
}

const std::string Versions::getLibraryVersion() {
    return LIBRARY_VERSION;
}

const std::string Versions::getCompleteVersion() {
    return "GNU Source-highlight " VERSION " (library: " LIBRARY_VERSION ")";
}

}
