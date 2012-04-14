//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/highlightstatebuilder.hpp"
#include "asserttestexit.h"
#include "srchilite/regexrulefactory.h"
#include "srchilite/stringdef.h"
#include "srchilite/highlightstate.h"
#include "srchilite/highlightrule.h"
#include "srchilite/stringlistlangelem.h"
#include "srchilite/highlightbuilderexception.h"
#include <sstream>
#include "srchilite/highlightstateprinter.h"
#include "srchilite/delimitedlangelem.h"
#include "srchilite/namedsubexpslangelem.h"
#include "srchilite/statelangelem.h"
#include "logformatter.h"
#include "srchilite/sourcehighlighter.h"
#include "srchilite/formattermanager.h"
#include "stdboosterror.h"

using namespace std;
using namespace srchilite;

HighlightStatePrinter coutPrinter;

static StringListLangElem *createFooStringListLangElem();
static LangElems *createFooLangElems();

StringListLangElem *createFooStringListLangElem() {
    StringDefs *defs = new StringDefs;
    defs->push_back(new StringDef("foo"));
    return new StringListLangElem("foo", defs, false);
}

LangElems *createFooLangElems() {
    LangElems *elems = new LangElems;
    elems->add(createFooStringListLangElem());
    return elems;
}

static void check_log_entry(const FormatterLogEntry &e,
        const std::string &elem, const std::string &s);

void check_log_entry(const FormatterLogEntry &e, const std::string &elem,
        const std::string &s) {
    assertEquals(elem, e.first);
    assertEquals(s, e.second);
}

int main() {
    ostringstream os;

    RegexRuleFactory factory;
    HighlightStateBuilder builder(&factory);
    HighlightStatePtr mainState(new HighlightState());

    FormatterLog log;

    FormatterPtr normalFormatter = FormatterPtr(new LogFormatter(log, "normal"));
    FormatterPtr keywordFormatter = FormatterPtr(new LogFormatter(log, "keyword"));
    FormatterPtr commentFormatter = FormatterPtr(new LogFormatter(log, "comment"));

    FormatterManager formatterManager(normalFormatter);
    SourceHighlighter sourceHighlighter(mainState);
    sourceHighlighter.setFormatterManager(&formatterManager);

    formatterManager.addFormatter("keyword", keywordFormatter);
    formatterManager.addFormatter("comment", commentFormatter);

    StringDef *quoted = new StringDef("foo", true);
    StringDef *quoted2 = new StringDef("bar", true);

    StringDef *unquoted = new StringDef("ufoo", false);
    StringDef *unquoted2 = new StringDef("ubar", false);

    StringDefs *mixed = new StringDefs;

    mixed->push_back(quoted);
    mixed->push_back(unquoted);

    StringListLangElem mixedListElem("foo", mixed, false);

    try {
        builder.build_DB(&mixedListElem, mainState.get());

        // must not get here
        assertTrue(false);
    } catch (const HighlightBuilderException &e) {
        cout << e << endl;
        os << e;
        assertEquals("cannot mix double quoted and non double quoted\n" + stdBoostCausedBy(), os.str());
    }

    // now check correct creation (with non mixed strings)
    quoted = new StringDef("foo", true);

    StringDefs *nonMixed = new StringDefs;
    nonMixed->push_back(quoted);
    nonMixed->push_back(quoted2);

    StringListLangElem okListElem("foo", nonMixed, false);

    builder.build_DB(&okListElem, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    assertEquals("\\<(?:foo|bar)\\>", mainState->getRuleList()[0]->toString());
    assertEquals(0, mainState->getRuleList()[0]->getExitLevel());

    unquoted = new StringDef("ufoo", false);

    StringDefs *nonMixed2 = new StringDefs;
    nonMixed2->push_back(unquoted);
    nonMixed2->push_back(unquoted2);

    StringListLangElem okListElem2("foo", nonMixed2, false);
    okListElem2.setExit();

    builder.build_DB(&okListElem2, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    assertEquals("(?:ufoo|ubar)", mainState->getRuleList()[1]->toString());
    assertEquals(1, mainState->getRuleList()[1]->getExitLevel());

    // test for delimited lang
    DelimitedLangElem delim("delim", new StringDef("<"), new StringDef(">"), new StringDef("\\\\"), false, false);

    builder.build_DB(&delim, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    assertEquals("<(?:[^\\\\<\\\\>]|\\\\.)*>", mainState->getRuleList()[2]->toString());

    // test for delimited lang (automatically transformed)
    DelimitedLangElem delim2("delim", new StringDef("<"), new StringDef(">"), new StringDef("\\\\"), true, false);
    delim2.setExit();

    builder.build_DB(&delim2, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    assertEquals("<", mainState->getRuleList().back()->toString());
    assertTrue(mainState->getRuleList().back()->getNextState().get());
    assertEquals(">", mainState->getRuleList().back()->getNextState()->getRuleList().front()->toString());
    // the exit level is 2 since 1 is for exiting the syntethized inner state and 1
    // for the specified exit level
    assertEquals(2, mainState->getRuleList().back()->getNextState()->getRuleList().front()->getExitLevel());

    // test for named subexpressions
    ElementNames *names = new ElementNames;

    names->push_back("foo");
    names->push_back("bar");

    NamedSubExpsLangElem namedSubExpsLangElem(names, new StringDef("(Foo)(Bar)(Gogo)"));

    try {
        builder.build_DB(&namedSubExpsLangElem, mainState.get());
        // must not get here
        assertTrue(false);
    } catch (const HighlightBuilderException &e) {
        // we provided only 2 elements instead of 3
        cout << e << endl;
        os.str("");
        os << e;
        assertEquals("number of marked subexpressions does not match number of elements\n" + stdBoostCausedBy(), os.str());
    }

    // add the missing elem
    names->push_back("gogo");

    // also test exit all
    namedSubExpsLangElem.setExitAll();

    // now it's OK since we added an element
    builder.build_DB(&namedSubExpsLangElem, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    assertEqualsCollections(*names, mainState->getRuleList().back()->getElemList());
    assertEquals(-1, mainState->getRuleList().back()->getExitLevel());

    // tests for state/environment elements
    StringDefs *stateDefs = new StringDefs;
    stateDefs->push_back(new StringDef("foo"));
    stateDefs->push_back(new StringDef("bar"));

    StringListLangElem *stateDefsElem = new StringListLangElem("foobar", stateDefs, false);

    StateLangElem stateLangElem("mystate", stateDefsElem, createFooLangElems());

    builder.build_DB(&stateLangElem, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    HighlightRulePtr lastRule = mainState->getRuleList().back();

    assertTrue(lastRule->getNextState().get() != 0);

    // check that in the inner state we find the foo rule created by createFooLangElems
    assertEquals("foo", lastRule->getNextState()->getRuleList().front()->getElemList().front());
    // and that the default element is "foobar" (it's an environment)
    assertEquals("foobar", lastRule->getNextState()->getDefaultElement());

    // we cannot create an environment with a NamedSubExpsLangElem
    names = new ElementNames;
    names->push_back("foo");
    names->push_back("bar");
    NamedSubExpsLangElem *namedSubExpsLangElem2 = new NamedSubExpsLangElem(names, new StringDef("(Foo)(Bar)"));
    StateLangElem wrongEnvLangElem("myenv", namedSubExpsLangElem2,
            createFooLangElems());

    try {
        builder.build_DB(&wrongEnvLangElem, mainState.get());
        // must not get here
        assertTrue(false);
    } catch (const HighlightBuilderException &e) {
        cout << e << endl;
        os.str("");
        os << e;
        assertEquals("cannot use this element for environments (only for states)\n" + stdBoostCausedBy(), os.str());
    }

    // while it's OK for states (the default element is normal)
    wrongEnvLangElem.set_state();

    builder.build_DB(&wrongEnvLangElem, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    // test for backreferences
    StringDef *backRef = new StringDef("@{1} @{2}");
    backRef->setBackRef(true);

    try {
        DelimitedLangElem delimWrongWBRF("delim", new StringDef("(<)"), backRef, new StringDef("\\\\"), false, false);

        builder.build_DB(&delimWrongWBRF, mainState.get());
        // must not get here
        assertTrue(false);
    } catch (const HighlightBuilderException &e) {
        cout << e << endl;
        os.str("");
        os << e;
        assertEquals("2 subexpressions requested, but only 1 found\n" + stdBoostCausedBy(), os.str());
    }

    backRef = new StringDef("@{2} @{1}");
    backRef->setBackRef(true);

    DelimitedLangElem commentDelim("comment", new StringDef("(<<) (>>)"), backRef, new StringDef("\\\\"), false, false);

    builder.build_DB(&commentDelim, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    lastRule = mainState->getRuleList().back();

    // check that back ref information were set correctly
    assertTrue(lastRule->getHasSubexpressions());
    assertTrue(lastRule->getNextState().get());
    assertTrue(lastRule->getNextState()->getNeedsReferenceReplacement());
    assertTrue(lastRule->getNextState()->getRuleList().front()->getNeedsReferenceReplacement());

    sourceHighlighter.highlightParagraph("check << >> comment inside >> << outside");

    showLog(log);

    // the delimited element has << >> as a starting element, and the end element
    // has backreferences to the start element @{2} @{1}, i.e., >> <<
    check_log_entry(log[0], "normal", "check ");
    check_log_entry(log[1], "comment", "<< >>");
    check_log_entry(log[2], "comment", " comment inside ");
    check_log_entry(log[3], "comment", ">> <<");
    check_log_entry(log[4], "normal", " outside");

    backRef = new StringDef("@{3}@{2}@{1}");
    backRef->setBackRef(true);

    DelimitedLangElem commentComplexDelim("comment", new StringDef("([^[:alnum:]])([^[:alnum:]])(\\1)"), backRef, new StringDef("\\\\"), true, true);

    /*
     mainState = HighlightStatePtr(new HighlightState);
     sourceHighlighter = SourceHighlighter(mainState);
     sourceHighlighter.setFormatterManager(&formatterManager);
     */

    builder.build_DB(&commentComplexDelim, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    lastRule = mainState->getRuleList().back();

    // check that back ref information were set correctly
    assertTrue(lastRule->getHasSubexpressions());
    assertTrue(lastRule->getNextState().get());
    assertTrue(lastRule->getNextState()->getNeedsReferenceReplacement());
    assertTrue(lastRule->getNextState()->getRuleList().front()->getNeedsReferenceReplacement());
    assertTrue(lastRule->getNextState()->getRuleList().back()->getHasSubexpressions());

    log.clear();

    sourceHighlighter.highlightParagraph("check |{| comment inside |{| outside");

    showLog(log);

    check_log_entry(log[0], "normal", "check ");
    check_log_entry(log[1], "comment", "|{|");
    check_log_entry(log[2], "comment", " comment inside ");
    check_log_entry(log[3], "comment", "|{|");
    check_log_entry(log[4], "normal", " outside");

    log.clear();

    sourceHighlighter.highlightParagraph("check [|[ comment <,< inside <,< [|[ outside");

    showLog(log);

    check_log_entry(log[0], "normal", "check ");
    check_log_entry(log[1], "comment", "[|[");
    check_log_entry(log[2], "comment", " comment ");
    check_log_entry(log[3], "comment", "<,<");
    check_log_entry(log[4], "comment", " inside ");
    check_log_entry(log[5], "comment", "<,<");
    check_log_entry(log[6], "comment", " ");
    check_log_entry(log[7], "comment", "[|[");
    check_log_entry(log[8], "normal", " outside");

    // nested elements must have different delimiters
    try {
        DelimitedLangElem wrongNestedDelim("delim", new StringDef("'"), new StringDef("'"), new StringDef("\\\\"), true, true);

        builder.build_DB(&wrongNestedDelim, mainState.get());
        // must not get here
        assertTrue(false);
    } catch (const HighlightBuilderException &e) {
        cout << e << endl;
        os.str("");
        os << e;
        assertEquals("delimiters must be different for nested elements\n" + stdBoostCausedBy(), os.str());
    }

    // tests for word list and non-word list
    StringDefs *nonWordList = new StringDefs;
    nonWordList->push_back(new StringDef("%"));
    nonWordList->push_back(new StringDef("@"));

    mainState = HighlightStatePtr(new HighlightState);
    StringListLangElem nonWordListElem("foo", nonWordList, false);
    builder.build_DB(&nonWordListElem, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    lastRule = mainState->getRuleList().back();

    // the generated expression must not be withing \< and \>
    assertEquals("(?:%|@)", lastRule->toString());

    // even if there are words it still must not be within \< \> because of symbols
    StringDefs *nonWordList2 = new StringDefs;
    nonWordList2->push_back(new StringDef("%"));
    nonWordList2->push_back(new StringDef("@"));
    nonWordList2->push_front(new StringDef("foo"));
    nonWordList2->push_back(new StringDef("bar"));

    mainState = HighlightStatePtr(new HighlightState);
    StringListLangElem nonWordListElem2("foo", nonWordList2, false);
    builder.build_DB(&nonWordListElem2, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    lastRule = mainState->getRuleList().back();

    assertEquals("(?:foo|%|@|bar)", lastRule->toString());

    // test whether delimited elems that start a state are generated correctly
    DelimitedLangElem delimStartingState("delim", new StringDef("<"), new StringDef(">"), new StringDef("\\\\"), false, false);
    StateLangElem fooStateElem("foo", 0, 0, false);
    delimStartingState.setStateLangElem(&fooStateElem);

    mainState = HighlightStatePtr(new HighlightState);
    builder.build_DB(&delimStartingState, mainState.get());

    coutPrinter.printHighlightState(mainState.get());

    assertEquals("<", mainState->getRuleList().back()->toString());
    assertTrue(mainState->getRuleList().back()->getNextState().get());
    assertEquals(">", mainState->getRuleList().back()->getNextState()->getRuleList().front()->toString());
    assertEquals(1, mainState->getRuleList().back()->getNextState()->getRuleList().front()->getExitLevel());

    cout << "test_highlightbuilder: SUCCESS" << endl;

    return 0;
}
