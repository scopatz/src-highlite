// tests for RegexHighlightRules

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <boost/regex.hpp>

#include "asserttestexit.h"
#include "srchilite/regexrulefactory.h"
#include "srchilite/highlightrule.h"
#include "srchilite/highlighttoken.h"
#include "srchilite/highlightstateprinter.h"
#include "srchilite/matchingparameters.h"
#include <sstream>
#include "srchilite/tostringcollection.h"

using namespace std;
using namespace srchilite;

HighlightStatePrinter coutPrinter;

static void check_regex(HighlightRule *rule, const MatchingParameters &params,
        const string &s, bool shouldMatch, const string &match,
        const string &prefix, const string &suffix,
        const MatchedSubExps &subexps = MatchedSubExps());

static void check_compound_regex(HighlightRule *rule,
        const MatchingParameters &params, const string &s,
        const MatchedElements &expectedElemList, const string &prefix,
        const string &suffix);

static void check_state(const HighlightState *state,
        const MatchingParameters &params, const string &s, bool shouldMatch,
        const string &match, const string &prefix, const string &suffix,
        const string &expectedMatchingRule = "", const string &expectedElem =
                "");

void check_regex(HighlightRule *rule, const MatchingParameters &params,
        const string &s, bool shouldMatch, const string &match,
        const string &prefix, const string &suffix,
        const MatchedSubExps &subexps) {
    HighlightToken res;

    bool matched = rule->tryToMatch(s, res, params);

    assertEquals(shouldMatch, matched);

    if (matched) {
        cout << "prefix : " << res.prefix << endl;
        cout << "suffix : " << res.suffix << endl;
        cout << "matched: " << res.matched.begin()->second << endl;

        if (res.matchedSubExps.size()) {
            cout << "subexps: " << collectionToString(&(res.matchedSubExps),
                    ',') << endl;
        }

        assertEquals(match, res.matched.begin()->second);
        assertEquals(prefix, res.prefix);
        assertEquals(suffix, res.suffix);
        assertEqualsCollections(subexps, res.matchedSubExps);
    } else {
        cout << "not matched: " << s << endl;
    }
}

void check_compound_regex(HighlightRule *rule,
        const MatchingParameters &params, const string &s,
        const MatchedElements &expectedElemList, const string &prefix,
        const string &suffix) {
    HighlightToken res;

    rule->tryToMatch(s, res, params);

    assertEquals(expectedElemList.size(), res.matched.size());

    coutPrinter.printHighlightToken(&res);

    MatchedElements::const_iterator it, it2;
    for (it2 = res.matched.begin(), it = expectedElemList.begin(); it
            != expectedElemList.end(); ++it, ++it2) {
        assertEquals(it->first, it2->first);
        assertEquals(it->second, it2->second);
    }
    assertEquals(prefix, res.prefix);
    assertEquals(suffix, res.suffix);
}

void check_state(const HighlightState *state, const MatchingParameters &params,
        const string &s, bool shouldMatch, const string &match,
        const string &prefix, const string &suffix,
        const string &expectedMatchingRule, const string &expectedElem) {
    HighlightToken res;

    bool matched = state->findBestMatch(s, res, params);

    assertEquals(shouldMatch, matched);

    if (matched) {
        coutPrinter.printHighlightToken(&res);

        assertEquals(match, res.matched.begin()->second);
        assertEquals(prefix, res.prefix);
        assertEquals(suffix, res.suffix);

        if (expectedMatchingRule.size())
            assertEquals(expectedMatchingRule, res.rule->toString());

        if (expectedElem.size())
            assertEquals(expectedElem, res.matched.begin()->first);
    } else {
        cout << "not matched: " << s << endl;
    }
}

int main() {
    ostringstream printedState;
    HighlightStatePrinter printer(printedState);
    MatchingParameters params;

    cout << "*** test_regexrules" << endl;

    // first of all check the only spaces regular expression
    boost::regex onlySpaces("[[:blank:]]*");

    assertTrue(boost::regex_match(" \t \t ", onlySpaces));
    assertTrue(boost::regex_match("", onlySpaces));
    assertFalse(boost::regex_match(" a\t \t ", onlySpaces));
    assertFalse(boost::regex_match(" a ", onlySpaces));
    assertFalse(boost::regex_match("foo", onlySpaces));

    RegexRuleFactory factory;

    HighlightRulePtr rule = HighlightRulePtr(factory.createSimpleRule("foo",
            "foo|bar"));

    check_regex(rule.get(), params, "before_foo_after", true, "foo", "before_",
            "_after");
    check_regex(rule.get(), params, "before_foo", true, "foo", "before_", "");
    check_regex(rule.get(), params, "bar_after", true, "bar", "", "_after");

    check_regex(rule.get(), params, "before__after", false, "foo", "before_",
            "_after");

    WordList wordList;
    wordList.push_back("foo");
    wordList.push_back("bar");
    wordList.push_back("gogo");

    rule = HighlightRulePtr(factory.createWordListRule("foo", wordList));

    cout << "word list regex: " << rule->toString() << endl;
    assertEquals("\\<(?:foo|bar|gogo)\\>", rule->toString());

    // there's no matching since we required word boundaries
    check_regex(rule.get(), params, "before_foo_after", false, "foo",
            "before_", "_after");
    check_regex(rule.get(), params, "before_foo", false, "foo", "before_", "");
    check_regex(rule.get(), params, "bar_after", false, "bar", "", "_after");

    // now there's match
    check_regex(rule.get(), params, "before foo after", true, "foo", "before ",
            " after");
    check_regex(rule.get(), params, "before foo", true, "foo", "before ", "");
    check_regex(rule.get(), params, "bar after", true, "bar", "", " after");

    check_regex(rule.get(), params, "before__after", false, "foo", "before_",
            "_after");

    // non case sensitive version
    rule = HighlightRulePtr(factory.createWordListRule("foo", wordList, false));

    cout << "word list regex: " << rule->toString() << endl;

    assertEquals("\\<(?:[Ff][Oo][Oo]|[Bb][Aa][Rr]|[Gg][Oo][Gg][Oo])\\>",
            rule->toString());

    check_regex(rule.get(), params, "before FoO", true, "FoO", "before ", "");
    check_regex(rule.get(), params, "bAr after", true, "bAr", "", " after");

    // now the simple list version (i.e., not word list)
    rule = HighlightRulePtr(factory.createListRule("foo", wordList));

    cout << "word list regex: " << rule->toString() << endl;

    assertEquals("(?:foo|bar|gogo)", rule->toString());

    check_regex(rule.get(), params, "before_foo", true, "foo", "before_", "");
    check_regex(rule.get(), params, "bar_after", true, "bar", "", "_after");

    // search for strings delimited by A
    rule = HighlightRulePtr(factory.createLineRule("foo", "A", "A"));

    cout << "line rule: " << rule->toString() << endl;

    assertEquals("A(?:[^A])*A", rule->toString());

    check_regex(rule.get(), params, "before A foo bar A after", true,
            "A foo bar A", "before ", " after");

    // search for strings delimited by A and BC
    rule = HighlightRulePtr(factory.createLineRule("foo", "A", "B"));

    cout << "line rule: " << rule->toString() << endl;

    assertEquals("A(?:[^AB])*B", rule->toString());

    check_regex(rule.get(), params, "before A foo bar A and BC after", true,
            "A and B", "before A foo bar ", "C after");

    // search for strings delimited by < and > and escape char
    rule = HighlightRulePtr(factory.createLineRule("foo", "<", ">", "\\\\"));

    cout << "line rule: " << rule->toString() << endl;

    assertEquals("<(?:[^\\\\<\\\\>]|\\\\.)*>", rule->toString());

    check_regex(rule.get(), params, "before < foo bar \\> and > after", true,
            "< foo bar \\> and >", "before ", " after");

    // test for multiline rule without escape and non nested
    rule = HighlightRulePtr(factory.createMultiLineRule("foo", "<", ">", "",
            false));

    printer.printHighlightRule(rule.get());

    cout << "multi line rule: " << printedState.str() << endl;

    assertEquals("<", rule->toString());

    const HighlightState *nextState = rule->getNextState().get();

    assertTrue(nextState != 0);
    if (nextState) {
        HighlightRulePtr nextRule = nextState->getRuleList()[0];
        assertEquals(">", nextRule->toString());
    }

    // test for multiline rule with escape and non nested
    rule = HighlightRulePtr(factory.createMultiLineRule("foo", "<", ">",
            "\\\\", false));

    printedState.str("");
    printer.printHighlightRule(rule.get());

    cout << "multi line rule: " << printedState.str() << endl;

    assertEquals("<", rule->toString());

    nextState = rule->getNextState().get();

    assertTrue(nextState != 0);
    if (nextState) {
        HighlightRulePtr nextRule = nextState->getRuleList()[1];
        assertEquals("\\\\.", nextRule->toString());
        nextRule = nextState->getRuleList()[0];
        assertEquals(">", nextRule->toString());
        assertEquals(1, nextRule->getExitLevel());
    }

    // check state betterThan
    HighlightToken t1("", "ab", "");
    HighlightToken t2("", "bcd", "a");
    HighlightToken t3("", "bcde", "a");

    // t2 is not better than t1 since although its matching string is longer
    // also its prefix is
    assertFalse(HighlightState::betterThan(t2, t1));
    assertTrue(HighlightState::betterThan(t1, t2));

    // t2 is not better than t3 since since its matching string is smaller
    assertFalse(HighlightState::betterThan(t2, t3));
    assertTrue(HighlightState::betterThan(t3, t2));

    // now test the state matching with the above nextState
    HighlightToken token;

    // should match >
    check_state(nextState, params, "ab >", true, ">", "ab ", "");

    // should match \> since it is escaped
    check_state(nextState, params, "ab \\> bc >", true, "\\>", "ab ", " bc >");

    HighlightState classState;

    assertEquals("normal", classState.getDefaultElement());

    classState.addRule(
            HighlightRulePtr(factory.createSimpleRule("as", "as|at")));

    check_state(&classState, params, "this class foo", true, "as", "this cl",
            "s foo", "", "as");

    HighlightRulePtr keywordRule = HighlightRulePtr(factory.createSimpleRule(
            "keyword", "class"));
    classState.addRule(keywordRule);

    // now we should find a better match "class"
    check_state(&classState, params, "this class foo", true, "class", "this ",
            " foo", "class", "keyword");

    classState.addRule(HighlightRulePtr(factory.createSimpleRule("complex",
            "class[[:blank:]]+[[:word:]]+")));

    // now we should find an even better match "class foo"
    check_state(&classState, params, "this class foo", true, "class foo",
            "this ", "", "class[[:blank:]]+[[:word:]]+", "complex");

    // we don't match "class foo" but only "class" since its prefix
    // contains only spaces
    check_state(&classState, params, "\t \t class foo", true, "class",
            "\t \t ", " foo", "class", "keyword");

    classState.addRule(HighlightRulePtr(factory.createSimpleRule("foo", "bar"))); // (1)
    classState.addRule(HighlightRulePtr(factory.createSimpleRule("foo",
            "[[:word:]]+(?=[[:blank:]]*\\()"))); // (2)

    // although also the second rule matches "bar", however the first one already matched
    check_state(&classState, params, "this bar ( foo", true, "bar", "this ",
            " ( foo", "bar");
    // in this case the second rule matches only
    check_state(&classState, params, "this myfun ( foo", true, "myfun",
            "this ", " ( foo", "[[:word:]]+(?=[[:blank:]]*\\()");

    // test for nested
    HighlightState stateWithNestedRule;
    HighlightRulePtr startRule = HighlightRulePtr(factory.createMultiLineRule(
            "foo", "<", ">", "\\\\", true));

    cout << "multi line rule (nested): ";
    coutPrinter.printHighlightRule(startRule.get());
    cout << endl;

    nextState = startRule->getNextState().get();
    // the 3rd element is expected to be the same start sequence but nested and
    // with empty next state
    assertEquals("<", nextState->getRuleList()[2]->toString());
    assertTrue(nextState->getRuleList()[2]->isNested());
    assertTrue(nextState->getRuleList()[2]->getNextState().get() == 0);

    // single line automatically transformed in multi line (since nested)
    HighlightRulePtr singleNestedToMultiRule = HighlightRulePtr(
            factory.createLineRule("foo", "<", ">", "\\\\", true));

    cout << "single nested line rule (transformed): ";
    coutPrinter.printHighlightRule(singleNestedToMultiRule.get());
    cout << endl;

    nextState = singleNestedToMultiRule->getNextState().get();
    assertEquals(">", nextState->getRuleList()[0]->toString());
    assertEquals(1, nextState->getRuleList()[0]->getExitLevel());
    assertEquals("<", nextState->getRuleList()[2]->toString());
    assertTrue(nextState->getRuleList()[2]->isNested());

    // single line automatically transformed in multi line (since
    // one delimiter has more than one char)
    HighlightRulePtr singleToMultiRule = HighlightRulePtr(
            factory.createLineRule("foo", "<<", ">>", "\\\\"));

    cout << "single line rule (transformed): ";
    coutPrinter.printHighlightRule(singleToMultiRule.get());
    cout << endl;

    nextState = singleToMultiRule->getNextState().get();
    assertEquals(">>", nextState->getRuleList()[0]->toString());
    assertEquals(1, nextState->getRuleList()[0]->getExitLevel());

    // check state copy
    HighlightStatePtr stateCopy = HighlightStatePtr(
            new HighlightState(*nextState));
    // a new id must have been created for the copy
    assertEquals(nextState->getId()+1, stateCopy->getId());
    rule = HighlightRulePtr(factory.createSimpleRule("foo", "foo"));
    // change the second rule of the state
    HighlightRulePtr oldRule = stateCopy->replaceRule(0, rule);
    stateCopy->addRule(HighlightRulePtr(factory.createSimpleRule("foo", "bar")));

    cout << "orig state: ";
    coutPrinter.printHighlightState(nextState);
    cout << endl;

    cout << "copy state: ";
    coutPrinter.printHighlightState(stateCopy.get());
    cout << endl;

    // check that the original state is still the same
    assertEquals(">>", nextState->getRuleList()[0]->toString());
    assertEquals(1, nextState->getRuleList()[0]->getExitLevel());
    assertEquals(">>", oldRule->toString());
    assertEquals(1, oldRule->getExitLevel());

    // and that the new one has changed rules
    assertEquals("foo", stateCopy->getRuleList()[0]->toString());
    assertEquals(0, stateCopy->getRuleList()[0]->getExitLevel());
    assertEquals("bar", stateCopy->getRuleList()[2]->toString());

    // test for MatchingParameters (beginning of line)
    HighlightStatePtr stateWithBOL = HighlightStatePtr(new HighlightState);
    stateWithBOL->addRule(HighlightRulePtr(factory.createSimpleRule("BOL",
            "^[[:word:]]+")));
    stateWithBOL->addRule(HighlightRulePtr(factory.createSimpleRule("NOTBOL",
            "foo")));

    cout << "state with BOL: ";
    coutPrinter.printHighlightState(stateWithBOL.get());
    cout << endl;

    // the first rule matches since we're at the beginning of the line
    check_state(stateWithBOL.get(), params, "foo at the beginning", true,
            "foo", "", " at the beginning", "^[[:word:]]+", "BOL");

    // the second rule matches since we specified that we're not at the beginning of the line
    MatchingParameters paramsNotBOL;
    paramsNotBOL.beginningOfLine = false;
    check_state(stateWithBOL.get(), paramsNotBOL, "foo at the beginning", true,
            "foo", "", " at the beginning", "foo", "NOTBOL");

    // test for compound rules
    ElemNameList nameList;
    nameList.push_back("keyword");
    nameList.push_back("normal");
    nameList.push_back("type");
    HighlightRulePtr compoundRule = HighlightRulePtr(
            factory.createCompoundRule(nameList,
                    "(class)([[:blank:]]+)([[:word:]]+)"));

    cout << "compound rule: ";
    coutPrinter.printHighlightRule(compoundRule.get());
    cout << endl;

    MatchedElements expectedMatchedElements;
    expectedMatchedElements.push_back(make_pair("keyword", "class"));
    expectedMatchedElements.push_back(make_pair("normal", "  "));
    expectedMatchedElements.push_back(make_pair("type", "MyClass"));

    check_compound_regex(compoundRule.get(), params, "class  MyClass",
            expectedMatchedElements, "", "");

    // test for rules with no end (i.e., \z)
    rule = HighlightRulePtr(factory.createLineRule("foo", "#", "", "\\\\"));

    cout << "line rule: ";
    coutPrinter.printHighlightRule(rule.get());
    cout << endl;

    assertEquals("#", rule->toString());
    assertTrue(rule->getNextState().get());
    assertEquals("\\z", rule->getNextState()->getRuleList().front()->toString());

    check_regex(rule.get(), params, "before # after", true, "#", "before ",
            " after");

    // test for replacement
    rule = HighlightRulePtr(factory.createSimpleRule("foo", "@{2} @{1} @{3}"));
    ReplacementList rep(9);
    rep[0] = "first";
    rep[1] = "second";

    rule->replaceReferences(rep);

    cout << "replaced rule: " << rule->toString() << endl;

    assertEquals("second first ", rule->toString());

    // test replacement for states
    HighlightRulePtr origRep1 = HighlightRulePtr(factory.createSimpleRule(
            "foo", "@{2} @{1} @{3}"));
    HighlightRulePtr origNoRep = HighlightRulePtr(factory.createSimpleRule(
            "foo", "no @{1} replacement"));
    HighlightRulePtr origRep2 = HighlightRulePtr(factory.createSimpleRule(
            "foo", "@{3} @{1} @{2}"));

    origRep1->setNeedsReferenceReplacement();
    origRep2->setNeedsReferenceReplacement();

    HighlightStatePtr stateWithRepl = HighlightStatePtr(new HighlightState);

    stateWithRepl->addRule(origRep1);
    stateWithRepl->addRule(origNoRep);
    stateWithRepl->addRule(origRep2);

    stateWithRepl->replaceReferences(rep);

    coutPrinter.printHighlightState(stateWithRepl.get());

    // check that the original rule have not been changed
    assertEquals("@{2} @{1} @{3}", origRep1->toString());
    assertEquals("@{3} @{1} @{2}", origRep2->toString());

    // that the second rule was not changed
    assertEquals("no @{1} replacement",
            stateWithRepl->getRuleList()[1]->toString());

    // that the other two were changed
    assertEquals("second first ", stateWithRepl->getRuleList()[0]->toString());
    assertEquals(" first second", stateWithRepl->getRuleList()[2]->toString());

    // test for subexpressions
    rule = HighlightRulePtr(factory.createSimpleRule("foo",
            "(class) ([[:word:]]+) (\\{)"));
    rule->setHasSubexpressions();

    // the expected subexpressions
    MatchedSubExps subexps;
    subexps.push_back("class");
    subexps.push_back("foo");
    subexps.push_back("{");

    check_regex(rule.get(), params, "my class foo {", true, "class foo {",
            "my ", "", subexps);

    cout << "*** test_regexrules SUCCESS" << endl;

    return 0;
}
