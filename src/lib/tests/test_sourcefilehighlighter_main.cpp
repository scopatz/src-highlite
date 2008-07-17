#include <iostream>

#include "sourcehighlighter.h"
#include "sourcefilehighlighter.h"
#include "formattermanager.h"
#include "regexrulefactory.h"
#include "regexhighlightrule.h"
#include "asserttestexit.h"
#include "my_sstream.h"
#include "bufferedoutput.h"
#include "textstyleformatter.h"
#include "chartranslator.h"
#include "linenumgenerator.h"

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

int main() {
    ostringstream os;

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

    SourceFileHighlighter highlighter("test", &sourceHighlighter, &output);

    // now the state has no rules, so we should see only "normal" formatting
    highlighter.highlight("this is a normal\nstring");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals("this is a normal\nstring", os.str());

    // now we add some rules
    os.str("");

    WordList keywords;
    keywords.push_back("class");
    keywords.push_back("public");
    highlightState->addRule(HighlightRulePtr(factory.createWordListRule(
            "keyword", keywords)));

    highlighter.highlight("this is a public class and\nhere's another class\nend");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "this is a <K>public</K> <K>class</K> and\nhere's another <K>class</K>\nend",
            os.str());

    // test comments (environments)
    os.str("");

    HighlightRulePtr multiLineCommentRule =
            HighlightRulePtr(factory.createMultiLineRule("comment", "/\\*",
                    "\\*/", "", false));
    HighlightStatePtr multiLineCommentState =
            multiLineCommentRule->getNextState();

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

    cout << "test_sourcefilehighlighter: SUCCESS" << endl;

    return 0;
}
