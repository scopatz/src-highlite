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
#include "srchilite/lineranges.h"
#include "srchilite/regexranges.h"

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

    RegexRuleFactory factory;

    BufferedOutput output(os);

    FormatterPtr normalFormatter = FormatterPtr(new TextStyleFormatter("$text",
            &output));
    FormatterPtr keywordFormatter = FormatterPtr(new TextStyleFormatter(
            "<K>$text</K>", &output));
    FormatterPtr commentFormatter = FormatterPtr(new TextStyleFormatter(
            "<C>$text</C>", &output));
    FormatterPtr contextFormatter = FormatterPtr(new TextStyleFormatter(
            "<CC>$text</CC>", &output));

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

    highlighter.highlight(
            "this is a public class and\nhere's another class\nend");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            "this is a <K>public</K> <K>class</K> and\nhere's another <K>class</K>\nend",
            os.str());

    // test comments (environments)
    os.str("");

    HighlightRulePtr multiLineCommentRule = HighlightRulePtr(
            factory.createMultiLineRule("comment", "/\\*", "\\*/", "", false));
    HighlightStatePtr multiLineCommentState =
            multiLineCommentRule->getNextState();

    assertTrue(multiLineCommentState.get());

    highlightState->addRule(multiLineCommentRule);

    // now we set its default element (to comment)
    multiLineCommentState->setDefaultElement("comment");

    highlighter.highlight(
            "this is /* a comment\nthat spans\nmore lines\n*/\na public class and\nhere's another class\nend");

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

    highlighter.highlight(
            "this is /* a comment\nthat spans\nmore lines\n*/ a public class end");

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

    highlighter.highlight(
            "this is /* a comment\nthat spans\nmore lines\n*/ a public class end");

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

    // test for line ranges
    os.str("");

    LineRanges lineRanges;
    lineRanges.addRange("2-3");

    highlighter.setLineRanges(&lineRanges);
    highlighter.highlight(
            "this is /* a comment\nthat spans more lines\n*/ end\nend2");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    // only line 2 and 3 must be output
    assertEquals(
            " PREFIX <LINE>00002:</LINE> <C>that spans more lines</C><NL>\n\
 PREFIX <LINE>00003:</LINE> <C>*/</C> end<NL>\n",
            os.str());

    // do it again to check that lineRanges was correctly reset
    os.str("");

    highlighter.highlight(
            "this is /* a comment\nthat spans more lines\n*/ end\nend2\nend3\nend4");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    // only line 2 and 3 must be output
    assertEquals(
            " PREFIX <LINE>00002:</LINE> <C>that spans more lines</C><NL>\n\
 PREFIX <LINE>00003:</LINE> <C>*/</C> end<NL>\n",
            os.str());

    // do it again to check context lines
    os.str("");
    highlighter.setContextFormatter(contextFormatter.get());

    lineRanges.setContextLines(2);

    highlighter.highlight(
            "this is /* a comment\nthat spans more lines\n*/ end\nend2\nend3\nend4\nend5");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    // only line 2 and 3 must be output, but line 1 and line 4 and 5 are printed as context
    assertEquals(
            " PREFIX <LINE>00001:</LINE> <CC>this is /* a comment</CC><NL>\n\
 PREFIX <LINE>00002:</LINE> <C>that spans more lines</C><NL>\n\
 PREFIX <LINE>00003:</LINE> <C>*/</C> end<NL>\n\
 PREFIX <LINE>00004:</LINE> <CC>end2</CC><NL>\n\
 PREFIX <LINE>00005:</LINE> <CC>end3</CC><NL>\n",
            os.str());

    // do it again to check range separators
    os.str("");
    highlighter.setContextFormatter(contextFormatter.get());
    highlighter.setRangeSeparator("...");

    lineRanges.addRange("7-8");
    lineRanges.setContextLines(1);

    highlighter.highlight(
            "this is /* a comment\nthat spans more lines\n*/ end\nend2\nend3\nend4\nend5\nend6\nend7\nend8\nend9");

    cout << "HIGHLIGHTED: " << os.str() << endl;

    // only line 2 and 3 must be output, but line 1 and line 4 is printed as context
    // then lines 7 and 8
    // and also the separator is printed
    assertEquals(
            " PREFIX <LINE>00001:</LINE> <CC>this is /* a comment</CC><NL>\n\
 PREFIX <LINE>00002:</LINE> <C>that spans more lines</C><NL>\n\
 PREFIX <LINE>00003:</LINE> <C>*/</C> end<NL>\n\
 PREFIX <LINE>00004:</LINE> <CC>end2</CC><NL>\n\
 PREFIX ...<NL>\n\
 PREFIX <LINE>00006:</LINE> <CC>end4</CC><NL>\n\
 PREFIX <LINE>00007:</LINE> end5<NL>\n\
 PREFIX <LINE>00008:</LINE> end6<NL>\n\
 PREFIX <LINE>00009:</LINE> <CC>end7</CC><NL>\n\
 PREFIX ...<NL>\n",
            os.str());

    // now test the regex ranges
    RegexRanges regexRanges;

    highlighter.setLineRanges(0);
    highlighter.setRangeSeparator("");
    highlighter.setRegexRanges(&regexRanges);

    regexRanges.addRegexRange("/// [[:alpha:]]+");
    regexRanges.addRegexRange("/// [[:digit:]]+");

    os.str("");
    highlighter.highlight(
            "this is /* a comment\nthat spans more lines\n*/ /// range end\nin range\nin range2\nend4 /// range\nend5\n/// 25\nend7\nend8\nend9\n/// 28\nend10");
    cout << "HIGHLIGHTED: " << os.str() << endl;

    assertEquals(
            " PREFIX <NL>\n\
 PREFIX <LINE>00004:</LINE> in range<NL>\n\
 PREFIX <LINE>00005:</LINE> in range2<NL>\n\
 PREFIX <LINE>00009:</LINE> end7<NL>\n\
 PREFIX <LINE>00010:</LINE> end8<NL>\n\
 PREFIX <LINE>00011:</LINE> end9<NL>\n",
            os.str());

    cout << "test_sourcefilehighlighter: SUCCESS" << endl;

    return 0;
}
