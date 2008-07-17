#include <iostream>

#include "logformatter.h"
#include "sourcehighlighter.h"
#include "formattermanager.h"
#include "regexrulefactory.h"
#include "regexhighlightrule.h"
#include "asserttestexit.h"

static void check_log_entry(const FormatterLogEntry &e,
        const std::string &elem, const std::string &s);

void check_log_entry(const FormatterLogEntry &e, const std::string &elem,
        const std::string &s) {
    assertEquals(elem, e.first);
    assertEquals(s, e.second);
}

using namespace std;

int main() {
    FormatterLog log;
    RegexRuleFactory factory;

    FormatterPtr normalFormatter = FormatterPtr(new LogFormatter(log, "normal"));
    FormatterPtr keywordFormatter = FormatterPtr(new LogFormatter(log, "keyword"));
    FormatterPtr commentFormatter = FormatterPtr(new LogFormatter(log, "comment"));

    FormatterManager formatterManager(normalFormatter);

    HighlightStatePtr highlightState = HighlightStatePtr(new HighlightState);

    SourceHighlighter sourceHighlighter(highlightState);
    sourceHighlighter.setFormatterManager(&formatterManager);

    // now the state has no rules, so we should see only "normal" formatting
    sourceHighlighter.highlightParagraph("this is normal");

    showLog(log);

    assertEquals((size_t)1, log.size());
    assertEquals("normal", log[0].first);
    assertEquals("this is normal", log[0].second);

    // now we add some rules
    log.clear();

    WordList keywords;
    keywords.push_back("class");
    keywords.push_back("public");
    highlightState->addRule(HighlightRulePtr(factory.createWordListRule(
            "keyword", keywords)));

    sourceHighlighter.highlightParagraph("this class is public and normal");

    // however the formatter for keyword is not set, so we will get
    // tokenized strings all as normal

    showLog(log);

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "normal", "class");
    check_log_entry(log[2], "normal", " is ");
    check_log_entry(log[3], "normal", "public");
    check_log_entry(log[4], "normal", " and normal");

    log.clear();

    // now we add the formatter for keyword

    formatterManager.addFormatter("keyword", keywordFormatter);

    sourceHighlighter.highlightParagraph("this class is public and normal");

    // and this time we will have also keywords logged

    showLog(log);

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "keyword", "class");
    check_log_entry(log[2], "normal", " is ");
    check_log_entry(log[3], "keyword", "public");
    check_log_entry(log[4], "normal", " and normal");

    // test environments

    log.clear();

    HighlightRulePtr multiLineCommentRule =
            HighlightRulePtr(factory.createMultiLineRule("comment", "/\\*",
                    "\\*/", "", false));
    HighlightStatePtr multiLineCommentState =
            multiLineCommentRule->getNextState();

    assertTrue(multiLineCommentState.get());

    highlightState->addRule(multiLineCommentRule);

    formatterManager.addFormatter("comment", commentFormatter);

    sourceHighlighter.highlightParagraph("this /* is a comment */ foo");

    showLog(log);

    // since we didn't set the default element of multiLineCommentState, then
    // the string inside the comment is formatted as normal

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "/*");
    check_log_entry(log[2], "normal", " is a comment ");
    check_log_entry(log[3], "comment", "*/");
    check_log_entry(log[4], "normal", " foo");

    log.clear();

    // now we set its default element (to comment)
    multiLineCommentState->setDefaultElement("comment");

    sourceHighlighter.highlightParagraph("this /* is a comment */ foo");

    showLog(log);

    // since now we set the default element of multiLineCommentState, then
    // the string inside the comment is formatted as a comment

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "/*");
    check_log_entry(log[2], "comment", " is a comment ");
    check_log_entry(log[3], "comment", "*/");
    check_log_entry(log[4], "normal", " foo");

    // test nested environments

    log.clear();

    HighlightRulePtr multiLineNestedCommentRule =
            HighlightRulePtr(factory.createMultiLineRule("comment", "<<", ">>",
                    "", true));
    HighlightStatePtr multiLineNestedCommentState =
            multiLineNestedCommentRule->getNextState();

    assertTrue(multiLineNestedCommentState.get());

    multiLineNestedCommentState->setDefaultElement("comment");
    highlightState->addRule(multiLineNestedCommentRule);

    sourceHighlighter.highlightParagraph("this << is << a << nested >> comment >> >> foo");

    showLog(log);

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "<<");
    check_log_entry(log[2], "comment", " is ");
    check_log_entry(log[3], "comment", "<<");
    check_log_entry(log[4], "comment", " a ");
    check_log_entry(log[5], "comment", "<<");
    check_log_entry(log[6], "comment", " nested ");
    check_log_entry(log[7], "comment", ">>");
    check_log_entry(log[8], "comment", " comment ");
    check_log_entry(log[9], "comment", ">>");
    check_log_entry(log[10], "comment", " ");
    check_log_entry(log[11], "comment", ">>");
    check_log_entry(log[12], "normal", " foo");

    // test for exit all

    log.clear();

    HighlightRulePtr exitAllRule = HighlightRulePtr(factory.createSimpleRule(
            "comment", "!"));
    exitAllRule->setExitLevel(-1);
    multiLineNestedCommentState->addRule(exitAllRule);

    sourceHighlighter.highlightParagraph("this << is << a << ! exit >> comment >> >> foo");

    showLog(log);

    // the ! makes exit all states and go back to the initial state

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "<<");
    check_log_entry(log[2], "comment", " is ");
    check_log_entry(log[3], "comment", "<<");
    check_log_entry(log[4], "comment", " a ");
    check_log_entry(log[5], "comment", "<<");
    check_log_entry(log[6], "comment", " ");
    check_log_entry(log[7], "comment", "!");
    check_log_entry(log[8], "normal", " exit >> comment >> >> foo");

    // test for optmized buffering
    log.clear();

    sourceHighlighter.setOptimize();
    sourceHighlighter.highlightParagraph("this << is << a << ! exit >> comment >> >> foo");

    showLog(log);

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "<< is << a << !");
    check_log_entry(log[2], "normal", " exit >> comment >> >> foo");

    // check for final flush in optimization
    log.clear();

    sourceHighlighter.setOptimize();
    sourceHighlighter.highlightParagraph("this << is << a << !");

    showLog(log);

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "<< is << a << !");
    
    sourceHighlighter.setOptimize(false);

    // check for final current state
    log.clear();

    sourceHighlighter.highlightParagraph("this <<");

    showLog(log);

    check_log_entry(log[0], "normal", "this ");
    check_log_entry(log[1], "comment", "<<");

    assertEquals("comment", sourceHighlighter.getCurrentState()->getDefaultElement());

    log.clear();
    
    // bring it back to the initial state
    sourceHighlighter.highlightParagraph("!");
    
    showLog(log);
    
    check_log_entry(log[0], "comment", "!");
    
    assertEquals("normal", sourceHighlighter.getCurrentState()->getDefaultElement());
    
    // test for rule with \z
    log.clear();

    HighlightRulePtr ruleWithEOL = HighlightRulePtr(factory.createLineRule(
            "comment", "#", "", "\\\\"));
    highlightState->addRule(ruleWithEOL);
    ruleWithEOL->getNextState()->setDefaultElement("comment");

    sourceHighlighter.highlightParagraph("before # this is a comment");
    sourceHighlighter.highlightParagraph("while this is class");

    showLog(log);

    int i = 0;
    check_log_entry(log[i++], "normal", "before ");
    check_log_entry(log[i++], "comment", "#");
    check_log_entry(log[i++], "comment", " this is a comment");
    //check_log_entry(log[i++], "comment", ""); // match the end of line
    check_log_entry(log[i++], "normal", "while this is ");
    check_log_entry(log[i++], "keyword", "class");
    
    cout << "test_highlighter: SUCCESS" << endl;

    return 0;
}
