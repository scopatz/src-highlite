/**
 * Tests for language inference, class LanguageInfer
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "srchilite/instances.h"
#include "srchilite/langdefmanager.h"
#include "srchilite/langmap.h"
#include <sstream>
#include <iterator>
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

int main() {
    LangDefManager *langDefManager = srchilite::Instances::getLangDefManager();
    LangMap *langMap = srchilite::Instances::getLangMap();
    LangMap *outlangMap = srchilite::Instances::getOutLangMap();

    assertTrue(langDefManager != 0, "should not be null");
    assertTrue(langMap != 0, "should not be null");
    assertTrue(outlangMap != 0, "should not be null");

    assertEquals(langDefManager, srchilite::Instances::getLangDefManager());
    assertEquals(langMap, srchilite::Instances::getLangMap());
    assertEquals(outlangMap, srchilite::Instances::getOutLangMap());

    Instances::unload();

    cout << "test_instances: SUCCESS" << endl;

    return 0;
}
