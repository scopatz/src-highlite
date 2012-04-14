#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/sourcehighlighter.h"
#include "srchilite/sourcefilehighlighter.h"
#include "srchilite/formattermanager.h"
#include "srchilite/regexrulefactory.h"
#include "srchilite/regexhighlightrule.h"
#include "asserttestexit.h"
#include <sstream>
#include "srchilite/bufferedoutput.h"
#include "srchilite/textstyleformatter.h"
#include "srchilite/chartranslator.h"
#include "srchilite/linenumgenerator.h"
#include "srchilite/debuglistener.h"

/*
 static void check_log_entry(const FormatterLogEntry &e,
 const std::string &elem, const std::string &s);

 void check_log_entry(const FormatterLogEntry &e, const std::string &elem,
 const std::string &s) {
 assertEquals(elem, e.first);
 assertEquals(s, e.second);
 }
 */

using namespace std;
using namespace srchilite;

int main() {
    ostringstream os;
    ostringstream osdebug;

    DebugListener debugger(osdebug);

    RegexRuleFactory factory;

    BufferedOutput output(os);

    FormatterPtr normalFormatter = FormatterPtr(new TextStyleFormatter("$text", &output));
    FormatterPtr keywordFormatter = FormatterPtr(new TextStyleFormatter("<K>$text</K>", &output));
    FormatterPtr commentFormatter = FormatterPtr(new TextStyleFormatter("<C>$text</C>", &output));

    FormatterManager formatterManager(normalFormatter);

    formatterManager.addFormatter("keyword", keywordFormatter);
    formatterManager.addFormatter("comment", commentFormatter);

    HighlightStatePtr highlightState = HighlightStatePtr(new HighlightState);

    SourceHighlighter sourceHighlighter(highlightState);
    sourceHighlighter.setFormatterManager(&formatterManager);

    sourceHighlighter.addListener(&debugger);

    SourceFileHighlighter highlighter("test", &sourceHighlighter, &output);

    // now the state has no rules, so we should see only "normal" formatting
    highlighter.highlight("this is a normal\nstring");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals("this is a normal\nstring", os.str());

    assertEquals(
            "formatting \"this is a normal\" as default\nformatting \"string\" as default\n",
            osdebug.str());

    // now we add some rules
    os.str("");
    osdebug.str("");

    WordList keywords;
    keywords.push_back("class");
    keywords.push_back("public");
    highlightState->addRule(HighlightRulePtr(factory.createWordListRule(
            "keyword", keywords)));
    highlightState->getRuleList().back()->setAdditionalInfo("foo.lang:10");

    highlighter.highlight("this is a public class and\nhere's another class\nend");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "this is a <K>public</K> <K>class</K> and\nhere's another <K>class</K>\nend",
            os.str());

    cout << "DEBUG: " << osdebug.str() << endl;

    // test comments (environments)
    os.str("");
    osdebug.str("");

    HighlightRulePtr multiLineCommentRule =
            HighlightRulePtr(factory.createMultiLineRule("comment", "/\\*",
                    "\\*/", "", false));
    multiLineCommentRule->setAdditionalInfo("comment.lang:20");
    HighlightStatePtr multiLineCommentState =
            multiLineCommentRule->getNextState();
    multiLineCommentState->getRuleList().front()->setAdditionalInfo("comment.lang:20");

    assertTrue(multiLineCommentState.get());

    highlightState->addRule(multiLineCommentRule);

    // now we set its default element (to comment)
    multiLineCommentState->setDefaultElement("comment");

    highlighter.highlight("this is /* a comment\nthat spans\nmore lines\n*/\na public class and\nhere's another class\nend");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "this is <C>/*</C><C> a comment</C>\n\
<C>that spans</C>\n\
<C>more lines</C>\n\
<C>*/</C>\n\
a <K>public</K> <K>class</K> and\n\
here's another <K>class</K>\n\
end",
            os.str());

    cout << "DEBUG: " << osdebug.str() << endl;

    // test optimizations (buffer adiacent elements)
    os.str("");

    sourceHighlighter.setOptimize(true);

    highlighter.highlight("this is /* a comment\nthat spans\nmore lines\n*/ a public class end");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "this is <C>/* a comment</C>\n\
<C>that spans</C>\n\
<C>more lines</C>\n\
<C>*/</C> a <K>public</K> <K>class</K> end",
            os.str());

    // test char translator for newlines
    os.str("");

    CharTranslator charTranslator;
    charTranslator.set_translation("\n", "<NL>\n");

    highlighter.setPreformatter(&charTranslator);

    highlighter.highlight("this is /* a comment\nthat spans\nmore lines\n*/ a public class end");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "this is <C>/* a comment</C><NL>\n\
<C>that spans</C><NL>\n\
<C>more lines</C><NL>\n\
<C>*/</C> a <K>public</K> <K>class</K> end",
            os.str());

    // test for line number generation
    os.str("");

    TextStyle lineStyle("<LINE>$text</LINE>");
    LineNumGenerator lineNumGen(lineStyle, 5);

    highlighter.setLineNumGenerator(&lineNumGen);

    highlighter.highlight("this is /* a comment\nthat spans more lines\n*/ end");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "<LINE>00001:</LINE> this is <C>/* a comment</C><NL>\n\
<LINE>00002:</LINE> <C>that spans more lines</C><NL>\n\
<LINE>00003:</LINE> <C>*/</C> end",
            os.str());

    // test for line prefix
    os.str("");

    highlighter.setLinePrefix(" PREFIX ");

    highlighter.highlight("this is /* a comment\nthat spans more lines\n*/ end");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            " PREFIX <LINE>00001:</LINE> this is <C>/* a comment</C><NL>\n\
 PREFIX <LINE>00002:</LINE> <C>that spans more lines</C><NL>\n\
 PREFIX <LINE>00003:</LINE> <C>*/</C> end",
            os.str());

    cout << "test_debuglistener: SUCCESS" << endl;

    return 0;
}
