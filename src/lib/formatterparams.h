//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FORMATTERPARAMS_H_
#define FORMATTERPARAMS_H_

#include "parserinfo.h"
#include "fileutil.h"

/**
 * Additional parameters that can be passed to a formatter
 */
struct FormatterParams : public ParserInfo {
    /// file name without path
    std::string fileNameNoPath;

    FormatterParams() {
    }
    FormatterParams(const std::string &n) :
        ParserInfo(n), fileNameNoPath(strip_file_path(n)) {
    }
};

#endif /*FORMATTERPARAMS_H_*/
