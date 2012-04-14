#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/sourcehighlight.h"
#include "srchilite/textstyleformatter.h"
#include <sstream>
#include "asserttestexit.h"
#include "srchilite/outlangdefparserfun.h"
#include "srchilite/parserexception.h"

using namespace std;
using namespace srchilite;

/*
 static void showFormatters(const TextStyleFormatterCollection &collection);

 void showFormatters(const TextStyleFormatterCollection &collection) {
 for (TextStyleFormatterCollection::const_iterator it = collection.begin(); it
 != collection.end(); ++it) {
 cout << (*it)->toString() << endl;
 }
 }
 */

int main() {
    istringstream input;
    ostringstream output;

    SourceHighlight sourcehighlight(TESTSDIR "wrong_trans.outlang");

    sourcehighlight.setDataDir(BASEDIR);

    // test with error in the lang file
    try {
        sourcehighlight.initialize();
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << e << endl;
        assertEqualsException(BASEDIR "/" TESTSDIR "wrong_trans.outlang:4: syntax error", e);
    }

    cout << "test_outlang_errors: SUCCESS" << endl;

    return 0;
}
