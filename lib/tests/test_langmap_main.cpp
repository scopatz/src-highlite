/**
 * Tests for language inference, class LanguageInfer
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "srchilite/langmap.h"
#include <sstream>
#include <iterator>
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

LangMap langmap(BASEDIR "test.map");

static void testMapFromFileName(const string &input, const string &expected);

void testMapFromFileName(const string &input, const string &expected) {
    string mapped = langmap.getMappedFileNameFromFileName(input);

    cout << input << " mapped to: " << mapped << endl;

    assertEquals(expected, mapped);
}

int main() {
    langmap.open();

    cout << BASEDIR << "test.map contents: " << endl;
    langmap.print();

    testMapFromFileName("foo.C", "cpp.lang");
    testMapFromFileName("foo.c", "c.lang");
    testMapFromFileName("Makefile.am", "makefile.lang");
    testMapFromFileName("Makefile", "Makefile.lang");
    testMapFromFileName("/my/long/path/Makefile", "Makefile.lang");
    testMapFromFileName("makefile", "makefile.lang");
    testMapFromFileName("ChangeLog", "changelog.lang");

    set<string> langs = langmap.getLangNames();
    set<string> langfiles = langmap.getMappedFileNames();

    cout << "lang names: " << endl;
    ostringstream Langs;
    copy(langs.begin(), langs.end(), ostream_iterator<string>(Langs, " "));
    cout << Langs.str() << endl;
    assertEquals("C ChangeLog Makefile am c changelog makefile ", Langs.str());

    cout << "lang def file names: " << endl;
    Langs.str("");
    copy(langfiles.begin(), langfiles.end(), ostream_iterator<string>(Langs, " "));
    cout << Langs.str() << endl;
    assertEquals("Makefile.lang c.lang changelog.lang cpp.lang makefile.lang ", Langs.str());

    cout << "test_langmap: SUCCESS" << endl;

    return 0;
}
