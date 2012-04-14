#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/langdefmanager.h"
#include "srchilite/regexrulefactory.h"
#include "srchilite/highlightstateprinter.h"
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

HighlightStatePrinter coutPrinter;

int main() {
    RegexRuleFactory ruleFactory;
    LangDefManager langdefManager(&ruleFactory);

    HighlightStatePtr highlightState;
    HighlightStatePtr highlightState2;

    highlightState
            = langdefManager.getHighlightState(BASEDIR, "c_comment.lang");
    highlightState2
            = langdefManager.getHighlightState(BASEDIR, "c_comment.lang");

    cout << "c_comment.lang: " << endl;
    coutPrinter.printHighlightState(highlightState.get());
    cout << endl;

    // the second one must be the same of the previous one (using the cache)
    assertEquals(highlightState->getId(), highlightState2->getId());

    highlightState2
            = langdefManager.buildHighlightState(BASEDIR, "c_comment.lang");

    // the second one must be different from the previous one (not using the cache)
    assertFalse(highlightState->getId() == highlightState2->getId());

    // check for a more complex language definition file
    highlightState = langdefManager.getHighlightState(BASEDIR, "java.lang");

    cout << "java.lang: " << endl;
    coutPrinter.printHighlightState(highlightState.get());
    cout << endl;

    cout << "test_langdefmanager: SUCCESS" << endl;

    return 0;
}
