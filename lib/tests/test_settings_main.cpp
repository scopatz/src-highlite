#include <iostream>

#include "srchilite/settings.h"
#include "asserttestexit.h"
#include <cstdlib>

using namespace std;
using namespace srchilite;

int main() {
    Settings settings;

    string home;
    const char *_home = getenv("HOME");
    if (_home)
        home = _home;

    cout << "confDir: " << settings.getConfDir() << endl;

    assertEquals(home + "/.source-highlight/", settings.getConfDir());

    // a non existent file
    settings.setTestFileName("foobar.conf");

    assertFalse(settings.checkForTestFile(), "test file must not be found");

    // now check for the file in the current directory
    settings.setDataDir(BASEDIR);
    settings.setTestFileName("testconffile.conf");

    assertTrue(settings.checkForTestFile(), "test file must be found");

    settings.setConfDir(BASEDIR);

    assertTrue(settings.readDataDir(), "datadir must be read from the conf file");
    cout << "read datadir: " << settings.getDataDir() << endl;
    assertEquals("foo", settings.getDataDir());

    cout << "test_settings: SUCCESS!" << endl;

    return 0;
}
