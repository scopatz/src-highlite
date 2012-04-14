// tests for class TextStyle

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/textstyle.h"

using namespace std;
using namespace srchilite;

int
main()
{
    string orig = "<font color=\"$style\">$text</font>";
    string expected = "<font color=\"green\">foo</font>";
    string transformed;

    TextStyle textStyle1(orig);
    transformed = textStyle1.output("foo", "green");

    cout << "orig: " << textStyle1.toString() << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(true, textStyle1.containsStyleVar());

    assertEquals(expected, transformed);

    orig = "<b>$text</b>";
    expected = "<b>foo</b>";
    textStyle1 = TextStyle(orig);
    transformed = textStyle1.output("foo", "green");

    cout << "orig: " << textStyle1.toString() << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(false, textStyle1.containsStyleVar());

    assertEquals(expected, transformed);

    TextStyle inner("<i>$text</i>");
    TextStyle composed = textStyle1.compose(inner);
    transformed = composed.output("foo");

    cout << "orig:" << composed.toString() << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals("<b><i>foo</i></b>", transformed);

    expected = "(\\foo)";
    textStyle1 = TextStyle();
    transformed = textStyle1.output("(\\foo)", "green");

    cout << "orig: " << textStyle1.toString() << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(expected, transformed);

    cout << "test_textstyle: SUCCESS!" << endl;

    return 0;
}
