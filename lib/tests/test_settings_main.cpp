#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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

    // test the static method
    string readDataDir = Settings::retrieveDataDir();
    cout << "retrieved data dir: " << readDataDir << endl;

    // now set the global value
    string globalValue = "global";
    Settings::setGlobalDataDir(globalValue);

    assertEquals(globalValue, Settings::retrieveDataDir());

    // now set the global value as empty, and check that the previous
    // value is returned now
    Settings::setGlobalDataDir("");
    assertEquals(readDataDir, Settings::retrieveDataDir());

    // test global check settings
    Settings::setGlobalDataDir(MAINSRCDIR);
    assertTrue(Settings::checkSettings(), "check setting should succeed");

    cout << "test_settings: SUCCESS!" << endl;

    return 0;
}
