/**
 * Tests for SourceHighlightUtils
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "srchilite/sourcehighlightutils.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

static void printStringSet(const StringSet &s, const string &sep = " ");

void printStringSet(const StringSet &s, const string &sep) {
    std::copy(s.begin(), s.end(), std::ostream_iterator<string>(cout,
            sep.c_str()));
}

int main() {
    StringSet strings = SourceHighlightUtils::getFileNames(BASEDIR, "lang");

    printStringSet(strings);
    cout << endl;

    assertTrue(strings.find("java.lang") != strings.end(), "expected java.lang");
    assertTrue(strings.find("symbols.lang") != strings.end(),
            "expected symbols.lang");
    assertTrue(strings.find("foobar.lang") == strings.end(),
            "NON expected foobar.lang");

    strings = SourceHighlightUtils::getStyleFileNames(BASEDIR);

    printStringSet(strings);
    cout << endl;

    assertTrue(strings.find("default.style") != strings.end(),
            "expected default.style");

    strings = SourceHighlightUtils::getCssStyleFileNames(BASEDIR);

    printStringSet(strings);
    cout << endl;

    assertTrue(strings.find("default.css") != strings.end(),
                "expected default.css");

    strings = SourceHighlightUtils::getLangFileNames(BASEDIR);

    printStringSet(strings);
    cout << endl;

    assertTrue(strings.find("java.lang") != strings.end(),
                "expected java.lang");

    strings = SourceHighlightUtils::getOutLangFileNames(BASEDIR);

    printStringSet(strings);
    cout << endl;

    assertTrue(strings.find("html.outlang") != strings.end(),
                "expected html.outlang");

    cout << "test_utils: SUCCESS" << endl;

    return 0;
}
