// tests for class TextStyle

#include <iostream>

#include "asserttest.h"
#include "textstyle.h"

using namespace std;

int
main()
{
    int result = 0;
    
    string orig = "<font color=\"$style\">$text</font>";
    string expected = "<font color=\"green\">foo</font>";
    string transformed;
    
    TextStyle textStyle1(orig);
    transformed = textStyle1.output("foo", "green");    
    
    cout << "orig: " << textStyle1.toString() << endl;
    cout << "transformed: " << transformed << endl;
    
    result += assertEquals(true, textStyle1.containsStyleVar());
    
    result += assertEquals(expected, transformed);
    
    orig = "<b>$text</b>";
    expected = "<b>foo</b>";
    textStyle1 = TextStyle(orig);
    transformed = textStyle1.output("foo", "green");
    
    cout << "orig: " << textStyle1.toString() << endl;
    cout << "transformed: " << transformed << endl;
    
    result += assertEquals(false, textStyle1.containsStyleVar());
    
    result += assertEquals(expected, transformed);
    
    TextStyle inner("<i>$text</i>");
    TextStyle composed = textStyle1.compose(inner);
    transformed = composed.output("foo");
    
    cout << "orig:" << composed.toString() << endl;
    cout << "transformed: " << transformed << endl;
    
    result += assertEquals("<b><i>foo</i></b>", transformed);    
    
    expected = "(\\foo)";
    textStyle1 = TextStyle();
    transformed = textStyle1.output("(\\foo)", "green");
    
    cout << "orig: " << textStyle1.toString() << endl;
    cout << "transformed: " << transformed << endl;
    
    result += assertEquals(expected, transformed);    
    
    return result;
}
