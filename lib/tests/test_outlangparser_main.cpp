//
// C++ Implementation: test_outlangparser_main
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <cstdlib>

#include "srchilite/outlangdefparserfun.h"
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

int main() {
    TextStylesPtr textstyles =
            parse_outlang_def(BASEDIR, "outlangtest.outlang");

    cout << "DocTemplate start:\n" << textstyles->docTemplate.toStringBegin()
            << endl;

    assertEquals(
            "this is the start of my doc\n\
and this is a line with a backslash \\text\n\
and this contains a {\n\
this is the title: $title\n\
this is the css url: $css\n\
this is the header: $header\n\
and this is some additional stuff: $additional",
            textstyles->docTemplate.toStringBegin());

    cout << "DocTemplate end:\n" << textstyles->docTemplate.toStringEnd()
            << endl;

    assertEquals(
            "this is the end of my doc\n\
this is simply the footer: $footer",
            textstyles->docTemplate.toStringEnd());

    string start = textstyles->docTemplate.output_begin("title", "css",
            "additional", "header", "footer", "", "inputlang");
    cout << "DocTemplate start:\n" << start << endl;

    assertEquals(
            "this is the start of my doc\n\
and this is a line with a backslash \\text\n\
and this contains a {\n\
this is the title: title\n\
this is the css url: css\n\
this is the header: header\n\
and this is some additional stuff: additional",
            start);

    string end = textstyles->docTemplate.output_end("title", "css",
            "additional", "header", "footer", "", "inputlang");
    cout << "DocTemplate end:\n" << end << endl;

    assertEquals(
            "this is the end of my doc\n\
this is simply the footer: footer",
            end);

    cout << "Style template:\n" << textstyles->starting_template << endl;
    cout << "Style separator: " << textstyles->style_separator << endl;

    assertEquals(";", textstyles->style_separator);

    cout << "Bold style: " << textstyles->bold.toString() << endl;

    assertEquals("\\textbf{$text}", textstyles->bold.toString());

    cout << "text formatted in bold style: " << textstyles->bold.output("TEXT")
            << endl;

    cout << "Italics: " << textstyles->italics.toString() << endl;

    assertEquals("<i>$text</i>", textstyles->italics.toString());

    cout << "Underline: " << textstyles->underline.toString() << endl;

    assertEquals("<u>$text</u>", textstyles->underline.toString());

    cout << "Color: " << textstyles->color.toString() << endl;

    assertEquals("<font color=\"$style\">$text</font>",
            textstyles->color.toString());

    cout << "ColorMap:\n" << textstyles->colorMap->toString() << endl;

    assertEquals("[green]=#33CC00\n\
[red]=#FF0000\ndefault=#000000",
            textstyles->colorMap->toString());

    cout << "CharTranslator:\n" << textstyles->charTranslator->toString()
            << endl;

    assertEquals("(&)|(<)|(>) -> (?1&amp;)(?2&lt;)(?3&gt;)",
            textstyles->charTranslator->toString());

    cout << "Onestyle: " << textstyles->onestyle.toString() << endl;

    assertEquals("<span class=\"$style\">$text</span>",
            textstyles->onestyle.toString());

    string i = "0x1b";
    cout << "original: " << i << endl;
    cout << "conversion: " << strtod(i.c_str(), 0) << endl;

    cout << "test_outlangparser: SUCCESS!" << endl;

    return 0;
}
