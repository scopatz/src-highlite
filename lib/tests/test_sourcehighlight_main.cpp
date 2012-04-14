#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/sourcehighlight.h"
#include "srchilite/textstyleformatter.h"
#include <sstream>
#include "asserttestexit.h"
#include "srchilite/ioexception.h"
#include "srchilite/docgenerator.h"
#include "srchilite/parserexception.h"

using namespace std;
using namespace srchilite;

/*
 static void showFormatters(const TextStyleFormatterCollection &collection);

 void showFormatters(const TextStyleFormatterCollection &collection) {
 for (TextStyleFormatterCollection::const_iterator it = collection.begin(); it
 != collection.end(); ++it) {
 cout << (*it)->toString() << endl;
 }
 }
 */

int main() {
    istringstream input;
    ostringstream output;

    SourceHighlight sourcehighlight("html.outlang");

    sourcehighlight.setDataDir(BASEDIR);

    string commentString = "this /* is a comment\nspanning more line */ end";
    input.str(commentString);

    sourcehighlight.highlight(input, output, "c_comment.lang");

    // save start and end of the generated documents for testing
    ostringstream docGeneratorBuffer;
    sourcehighlight.getNoDocGenerator()->generate_start_doc(&docGeneratorBuffer);
    const string startDoc = docGeneratorBuffer.str();
    docGeneratorBuffer.str("");
    sourcehighlight.getNoDocGenerator()->generate_end_doc(&docGeneratorBuffer);
    const string endDoc = docGeneratorBuffer.str();

    // showFormatters(sourcehighlight.getFormatterCollection());

    cout << "formatted: " << output.str() << endl;
    assertEquals(
            startDoc
                    + "this <i><font color=\"#9A1900\">/* is a comment</font></i>\n\
<i><font color=\"#9A1900\">spanning more line */</font></i> end"
                    + endDoc, output.str());

    istringstream input2("this /* is a comment\nspanning more line */ end");
    output.str("");

    // tests for line numbers
    sourcehighlight.setGenerateLineNumbers();

    sourcehighlight.highlight(input2, output, "c_comment.lang");

    cout << "formatted: " << output.str() << endl;
    assertEquals(
            startDoc
                    + "<font color=\"#000000\">00001:</font> this <i><font color=\"#9A1900\">/* is a comment</font></i>\n\
<font color=\"#000000\">00002:</font> <i><font color=\"#9A1900\">spanning more line */</font></i> end"
                    + endDoc, output.str());

    // tests for line numbers with explicit number of digits
    sourcehighlight.setLineNumberDigits(2);

    output.str("");

    istringstream input_ndigits2("this /* is a comment\nspanning more line */ end");

    sourcehighlight.highlight(input_ndigits2, output, "c_comment.lang");

    cout << "formatted: " << output.str() << endl;
    assertEquals(
            startDoc
                    + "<font color=\"#000000\">01:</font> this <i><font color=\"#9A1900\">/* is a comment</font></i>\n\
<font color=\"#000000\">02:</font> <i><font color=\"#9A1900\">spanning more line */</font></i> end"
                    + endDoc, output.str());

    sourcehighlight.setGenerateLineNumbers(false);

    // test HTML char translation
    istringstream input3("this < > & html chars");
    output.str("");

    sourcehighlight.highlight(input3, output, "c_comment.lang");

    cout << "formatted: " << output.str() << endl;

    assertEquals(startDoc + "this &lt; &gt; &amp; html chars" + endDoc,
            output.str());

    // test tab translation translation
    istringstream input4("these\t\tare\ttabs\tchars");
    output.str("");

    SourceHighlight sourcehighlightTabs("html.outlang");
    sourcehighlightTabs.setDataDir(BASEDIR);
    sourcehighlightTabs.setTabSpaces(3);
    sourcehighlightTabs.highlight(input4, output, "c_comment.lang");

    cout << "formatted: " << output.str() << endl;

    assertEquals(startDoc + "these    are   tabs  chars" + endDoc, output.str());

    sourcehighlight.setGenerateLineNumbers();

    // try with files
    sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", "java.lang");

    // try with non existent input file
    try {
        sourcehighlight.highlight("FOO.java", "Hello.java.html", "java.lang");
        assertTrue(false); // must not get here
    } catch (IOException &e) {
        cout << "expected exception: " << e << endl;
        assertEquals("FOO.java: cannot open input file FOO.java.", e.filename + ": " + e.what() + ".");
    }

    // try with entire doc
    sourcehighlight.setGenerateEntireDoc();
    sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "HelloDoc.java.html", "java.lang");

    // test with html tables
    SourceHighlight sourcehighlightTable("htmltable.outlang");

    sourcehighlightTable.setDataDir(BASEDIR);

    sourcehighlightTable.highlight(BASEDIR "../doc/Hello.java", "HelloTable.java.html", "java.lang");

    cout << "test_sourcehighlight: SUCCESS" << endl;

    return 0;
}
