//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#include "langelem.h"
#include "my_sstream.h"

const std::string LangElem::toStringParserInfo() const {
    std::ostringstream os;

    os << filename;

    if (line > 0)
        os << ":" << line;

    return os.str();
}
