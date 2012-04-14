#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/sourcehighlight.h"
#include "srchilite/textstyleformatter.h"
#include <sstream>
#include "asserttestexit.h"
#include "srchilite/ioexception.h"
#include "srchilite/docgenerator.h"
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

    SourceHighlight sourcehighlight("html.outlang");

    sourcehighlight.setDataDir(BASEDIR);

    // test with error in the lang file
    try {
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_var.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << e << endl;
        assertEqualsException(BASEDIR "/" TESTSDIR "wrong_var.lang:3: undefined variable UNDEFINED", e);
    }

    try {
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_syntax_simple.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        // cout << "expected exception: " << e << endl;
        assertEqualsException(BASEDIR "/" TESTSDIR "wrong_syntax_simple.lang:1: syntax error", e);
    }

    try {
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_syntax.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        // cout << "expected exception: " << e << endl;
        assertEqualsException(BASEDIR "/" TESTSDIR "wrong_syntax.lang:2: syntax error", e);
    }

    try {
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_syntax_include.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << e << endl;
        // the error is in an included file
        assertEqualsException(TESTSDIR "/wrong_syntax.lang:2: syntax error", e);
    }

    try {
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_backref.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << e << endl;
        // the error is in an included file
        assertEqualsException(BASEDIR "/" TESTSDIR "wrong_backref.lang:2: backreferences are allowed only inside ` `", e);
    }

    try {
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_backref2.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << e << endl;
        // the error is in an included file
        assertEqualsException(BASEDIR "/" TESTSDIR "wrong_backref2.lang:2: backreferences are allowed only inside ` `", e);
    }

    cout << "test_sourcehighlight_errors: SUCCESS" << endl;

    return 0;
}
