#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/textstyleformatter.h"
#include "srchilite/bufferedoutput.h"
#include <sstream>
#include "srchilite/srcuntabifier.h"
#include "srchilite/textstyleformatterfactory.h"
#include "srchilite/formattermanager.h"
#include "srchilite/ctagsformatter.h"

using namespace std;
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

int main() {
    ostringstream os;
    bool result;

    BufferedOutput bufferedOutput(os);

    FormatterPtr defaultFormatter(new TextStyleFormatter("$text"));

    MyPreFormatter preformatter;

    TextStylesPtr textStyles(new TextStyles);

    textStyles->bold = TextStyle("<b>$text</b>");
    textStyles->italics = TextStyle("<i>$text</i>");
    textStyles->underline = TextStyle("<u>$text</u>");
    textStyles->color = TextStyle("<c=$style>$text</c>");
    (*(textStyles->colorMap))["red"] = "RED";

    // this is just to test noref, it will be never used
    CTagsFormatter ctagsformatter(0, textStyles->refstyle, 0);
    ctagsformatter.setFileInfo("", "");

    FormatterManager formatterManager(defaultFormatter);

    TextStyleFormatterFactory formatterFactory(textStyles, &preformatter,
            &ctagsformatter, &formatterManager);

    StyleConstantsPtr styleConstants(new StyleConstants);

    styleConstants->push_back(ISBOLD);
    styleConstants->push_back(ISUNDERLINE);

    // test without colors
    result = formatterFactory.createFormatter("foo", "", "", styleConstants);

    assertTrue(result);

    FormatterPtr formatter = formatterManager.getFormatter("foo");

    assertTrue(formatter.get());

    TextStyleFormatter *tformatter = 0;

    tformatter = dynamic_cast<TextStyleFormatter *>(formatter.get());

    assertTrue(tformatter);
    assertEquals(&ctagsformatter, tformatter->getCTagsFormatter());

    // one formatter was created
    assertEquals((size_t)1, formatterFactory.getFormatterCollection().size());

    tformatter->setBufferedOutput(&bufferedOutput);

    tformatter->format("test");

    cout << "formatted: " << os.str() << endl;

    assertEquals("<b><u>test</u></b>", os.str());

    // check that noref does not set the ctagsformatter
    styleConstants->push_back(ISNOREF);

    result = formatterFactory.createFormatter("noref", "", "", styleConstants);

    // another formatter was created
    assertEquals((size_t)2, formatterFactory.getFormatterCollection().size());

    assertTrue(result);

    formatter = formatterManager.getFormatter("noref");

    assertTrue(formatter.get());

    tformatter = dynamic_cast<TextStyleFormatter *>(formatter.get());

    assertTrue(tformatter);
    assertEquals((CTagsFormatter *)0, tformatter->getCTagsFormatter());

    // check that noref does not set the ctagsformatter
    result = formatterFactory.createFormatter("colored", "red", "", styleConstants);

    // another formatter was created
    assertEquals((size_t)3, formatterFactory.getFormatterCollection().size());

    assertTrue(result);

    formatter = formatterManager.getFormatter("colored");

    assertTrue(formatter.get());

    tformatter = dynamic_cast<TextStyleFormatter *>(formatter.get());

    assertTrue(tformatter);

    os.str("");
    tformatter->setBufferedOutput(&bufferedOutput);
    tformatter->format("test");

    cout << "formatted: " << os.str() << endl;

    assertEquals("<b><u><c=RED>test</c></u></b>", os.str());

    // test for createMissingFormatter

    // formatter for foo already exists
    assertFalse(formatterFactory.createMissingFormatter("foo", "bar"));

    // formatter doesn't exist
    assertFalse(formatterFactory.createMissingFormatter("bar", "nonexisting"));

    // formatter for bar is just the same as the formatter for foo
    assertTrue(formatterFactory.createMissingFormatter("bar", "foo"));

    // check that formatting with "bar" is the same as formatting with "foo"
    formatter = formatterManager.hasFormatter("bar");
    assertTrue(formatter.get());

    // no other formatter was created
    assertEquals((size_t)3, formatterFactory.getFormatterCollection().size());

    os.str("");
    formatter->format("test");

    cout << "formatted: " << os.str() << endl;

    assertEquals("<b><u>test</u></b>", os.str());

    cout << "test_textstyleformatterfactory: SUCCESS" << endl;

    return 0;
}
