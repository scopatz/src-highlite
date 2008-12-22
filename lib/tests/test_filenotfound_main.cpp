#include <iostream>

#include "my_sstream.h"
#include "asserttestexit.h"
#include "langdefparserfun.h"
#include "outlangdefparserfun.h"
#include "ioexception.h"
#include "parserexception.h"

using namespace std;

int main() {
    try {
        parse_lang_def("", "foo.bar");
        assertFalse(true); // must not get here
    } catch (ParserException &e) {
        cout << e << endl;
        ostringstream output;
        output << e;
        assertEquals("cannot find input file anywhere foo.bar", output.str());
    }

    try {
        parse_lang_def("", TESTSDIR "wrong_include.lang");
        assertFalse(true); // must not get here
    } catch (ParserException &e) {
        cout << e << endl;
        ostringstream output;
        output << e;
        assertEquals("cannot open include file " TESTSDIR "/nonexistent.lang", output.str());
    }

    try {
        parse_outlang_def("", "foo.bar");
        assertFalse(true); // must not get here
    } catch (ParserException &e) {
        cout << e << endl;
        ostringstream output;
        output << e;
        assertEquals("cannot find input file anywhere foo.bar", output.str());
    }

    try {
        parse_outlang_def("", TESTSDIR "wrong_outlang_include.outlang");
        assertFalse(true); // must not get here
    } catch (ParserException &e) {
        cout << e << endl;
        ostringstream output;
        output << e;
        assertEquals("cannot open include file " TESTSDIR "/nonexistent.outlang", output.str());
    }

    cout << "test_filenotfound: SUCCESS" << endl;

    return 0;
}
