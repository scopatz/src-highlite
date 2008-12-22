// tests for class TextStyle

#include <iostream>

#include "asserttestexit.h"
#include "textstyleformatter.h"
#include "bufferedoutput.h"
#include "my_sstream.h"
#include "srcuntabifier.h"

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
    ostringstream os;

    BufferedOutput bufferedOutput(os);

    string orig = "<font color=\"green\">$text</font>";
    string expected = "<font color=\"green\">foo</font>";
    string transformed;

    TextStyle textStyle1(orig);
    TextStyleFormatter formatter(textStyle1);
    formatter.setBufferedOutput(&bufferedOutput);

    formatter.format("foo");

    cout << "formatted: " << os.str() << endl;

    assertEquals(expected, os.str());

    // test the preformatter
    MyPreFormatter preformatter;
    formatter.setPreFormatter(&preformatter);

    os.str("");
    formatter.format("foo");

    cout << "formatted: " << os.str() << endl;

    assertEquals("<font color=\"green\">{foo}</font>", os.str());

    Untabifier untabifier(3);
    formatter.setPreFormatter(&untabifier);

    os.str("");
    formatter.format("\tfoo\t");

    cout << "formatted: " << os.str() << endl;

    assertEquals("<font color=\"green\">   foo   </font>", os.str());

    cout << "test_textstyleformatter: SUCCESS" << endl;

    return 0;
}
