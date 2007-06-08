//
// C++ Interface: parsestyles
//
// Description: declaration of function for parsing style files
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef PARSESTYLES_H
#define PARSESTYLES_H

class GeneratorFactory;

/// for style files
void parseStyles(const std::string &path, const std::string &name,
                   GeneratorFactory *generatorFactory,
                   std::string &bodyBgColor) ;
void parseStyleError(const std::string &error, bool exit = true) ;

/// for css style files
void parseCssStyles(const std::string &path, const std::string &name,
                       GeneratorFactory *generatorFactory,
                       std::string &bodyBgColor) ;

#endif
