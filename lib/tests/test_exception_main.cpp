//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/highlightbuilderexception.h"
#include "srchilite/parserinfo.h"
#include "asserttestexit.h"
#include <sstream>
#include "stdboosterror.h"

using namespace std;
using namespace srchilite;

int main() {
    ostringstream os;

    ParserInfo parserInfo("foo");
    parserInfo.line = 10;

    HighlightBuilderException testException("test exception", &parserInfo);

    // cout << "OUTPUT: " << testException << endl;
    os << testException;

    string causedby = boost::regex_error(boost::regex_constants::error_bad_pattern).what();

    assertEquals("foo:10: test exception\n" + stdBoostCausedBy("foo", "10"), os.str());

    return 0;
}
