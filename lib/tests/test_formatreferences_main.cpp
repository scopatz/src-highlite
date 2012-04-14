// tests for class TextStyle

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/textstyleformatter.h"
#include "srchilite/bufferedoutput.h"
#include <sstream>
#include "srchilite/srcuntabifier.h"
#include "srchilite/ctagsformatter.h"
#include "srchilite/ctagscollector.h"
#include "srchilite/textstyles.h"
#include "srchilite/formatterparams.h"

using namespace srchilite;

class MyPreFormatter : public PreFormatter {
public:
    virtual ~MyPreFormatter() {
    }

protected:
    /**
     * test performatting
     */
    virtual const std::string doPreformat(const std::string &text) {
        return "{" + text + "}";
    }

};

using namespace std;

int main() {
    CTagsCollector collectorInline("mytags", INLINE);
    CTagsFormatterResults results;

    string sourceFile = string( BASEDIR) + "readtags.h";

    TextStyles textStyles;
    const char *vars[] = { "linenum", "infilename", "infile", "outfile", 0 };

    textStyles.refstyle.anchor = TextStyle(
            "<A>$text - $infilename):$linenum<A>", vars);
    textStyles.refstyle.inline_reference = TextStyle(
            "<IN>$text - $infilename):$linenum<IN>", vars);
    textStyles.refstyle.postline_reference = TextStyle(
            "<PL>$text - $infilename):$linenum<PL>", vars);
    textStyles.refstyle.postdoc_reference = TextStyle(
            "<PD>$text - $infilename):$linenum<PD>", vars);

    // pretend the output is readtags.html
    MyPreFormatter preformatter;
    CTagsFormatter ctagsformatter(&preformatter, textStyles.refstyle,
            &collectorInline);
    ctagsformatter.setFileInfo(sourceFile, "readtags.html");

    ostringstream os;

    BufferedOutput bufferedOutput(os);

    // just a foo tag
    string orig = "<F>$text</F>";

    TextStyle textStyle1(orig);
    TextStyleFormatter formatter(textStyle1);
    formatter.setBufferedOutput(&bufferedOutput);
    formatter.setPreFormatter(&preformatter);
    formatter.setCTagsFormatter(&ctagsformatter);

    FormatterParams params(sourceFile);
    params.line = 1;

    formatter.format("there are no references", &params);

    cout << "formatted: " << os.str() << endl;

    assertEquals("<F>{there are no references}</F>", os.str());

    os.str("");

    formatter.format("just one READTAGS_H reference", &params);

    cout << "formatted: " << os.str() << endl;

    assertEquals(
            "<F>{just one }</F><F><IN>{READTAGS_H} - readtags.h):22<IN></F><F>{ reference}</F>",
            os.str());

    // check that there's not post line and post doc references
    os.str("");
    bufferedOutput.writePostLine();
    assertEquals("", os.str());
    os.str("");
    bufferedOutput.writePostDoc();
    assertEquals("", os.str());

    // test anchor
    os.str("");
    params.line = 22;
    formatter.format("just one READTAGS_H anchor", &params);

    cout << "formatted: " << os.str() << endl;

    assertEquals(
            "<F>{just one }</F><F><A>{READTAGS_H} - readtags.h):22<A></F><F>{ anchor}</F>",
            os.str());

    // check that there's not post line and post doc references
    os.str("");
    bufferedOutput.writePostLine();
    assertEquals("", os.str());
    os.str("");
    bufferedOutput.writePostDoc();
    assertEquals("", os.str());

    // test automatic postline
    os.str("");
    params.line = 1;
    formatter.format("this file is a file reference", &params);

    cout << "formatted: " << os.str() << endl;

    // the references do not appear in the paragraph, but in post line
    assertEquals(
            "<F>{this }</F><F>{file}</F><F>{ is a }</F><F>{file}</F><F>{ reference}</F>",
            os.str());

    // check that there's a post line and no post doc references
    os.str("");
    bufferedOutput.writePostLine();
    cout << "postline: " << os.str() << endl;
    assertEquals(
            "<PL>{file} - readtags.h):112<PL>{\n}<PL>{file} - readtags.h):72<PL>{\n}",
            os.str());
    os.str("");
    bufferedOutput.writePostDoc();
    assertEquals("", os.str());

    // test post doc
    collectorInline.setRefPosition(POSTDOC);

    os.str("");
    params.line = 1;
    formatter.format("this file is a file reference", &params);

    cout << "formatted: " << os.str() << endl;

    // the references do not appear in the paragraph, but in post line
    assertEquals(
            "<F>{this }</F><F>{file}</F><F>{ is a }</F><F>{file}</F><F>{ reference}</F>",
            os.str());

    // check that there's a post doc and no post line references
    os.str("");
    bufferedOutput.writePostDoc();
    cout << "postdoc: " << os.str() << endl;
    assertEquals(
            "<PD>{file} - readtags.h):112<PD>{\n}<PD>{file} - readtags.h):72<PD>{\n}",
            os.str());
    os.str("");
    bufferedOutput.writePostLine();
    assertEquals("", os.str());

    cout << "test_formatreferences: SUCCESS" << endl;

    return 0;
}
