#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/textstyleformatter.h"
#include "srchilite/textstylebuilder.h"
#include "srchilite/doctemplate.h"
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

int main() {
    TextStyle bold("<b>$text</b>");
    TextStyle italics("<i>$text</i>");

    TextStyle keyword = bold;

    string orig = "fookeyword";
    string expected = "<b>" + orig + "</b>";
    string transformed = keyword.output(orig);

    cout << "orig: " << orig << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(expected, transformed);

    TextStyle keyword2 = bold.compose(italics);

    expected = "<b><i>" + orig + "</i></b>";
    transformed = keyword2.output(orig);

    cout << "orig: " << orig << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(expected, transformed);

    TextStyleBuilder textStyleBuilder;

    textStyleBuilder.start();
    textStyleBuilder.add(bold);
    textStyleBuilder.add(italics);
    TextStyle keywordGenerator3 = textStyleBuilder.end();

    expected = "<b><i>" + orig + "</i></b>";
    transformed = keywordGenerator3.output(orig);

    cout << "orig: " << orig << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(expected, transformed);

    TextStyleBuilder
            textStyleBuilder2("start{" STYLE_VAR_TEXT TEXT_VAR_TEXT "}", ";");
    textStyleBuilder2.start();
    textStyleBuilder2.add(TextStyle("bold" STYLE_VAR_TEXT));
    textStyleBuilder2.add(TextStyle("italics " STYLE_VAR_TEXT));
    TextStyle keywordGenerator4 = textStyleBuilder2.end();

    expected = "start{bold;italics " + orig + "}";
    transformed = keywordGenerator4.output(orig);

    cout << "orig: " << orig << endl;
    cout << "transformed: " << transformed << endl;

    assertEquals(expected, transformed);

    string
            start =
                    "$headerthe title: $title\nthe css url: $css\nand some additional text: $additional";
    string end = "$footer";
    string
            expected_start =
                    "HEADER\nthe title: TITLE\nthe css url: CSS\nand some additional text: ADDITIONAL";
    string expected_end = "\nFOOTER";
    DocTemplate docTemplate(start, end);

    string transformed_start = docTemplate.output_begin("TITLE", "CSS",
            "ADDITIONAL", "HEADER\n", "\nFOOTER", "", "INPUTLANG");
    string transformed_end = docTemplate.output_end("TITLE", "CSS",
            "ADDITIONAL", "HEADER\n", "\nFOOTER", "", "INPUTLANG");

    cout << "orig start : " << start << endl;
    cout << "transformed: " << transformed_start << endl;
    assertEquals(expected_start, transformed_start);

    cout << "orig end   : " << end << endl;
    cout << "transformed: " << transformed_end << endl;
    assertEquals(expected_end, transformed_end);

    cout << "test_textgenerator: SUCCESS!" << endl;

    return 0;
}
