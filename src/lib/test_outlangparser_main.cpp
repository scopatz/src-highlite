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

#include <iostream>
#include <stdlib.h>

#include "outlangdefparserfun.h"

using namespace std;

int
main()
{
  TextStylesPtr textstyles = parse_outlang_def("", "outlangtest.outlang");

  cout << "DocTemplate start:\n" << textstyles->docTemplate.toStringBegin() << endl;
  cout << "DocTemplate end:\n" << textstyles->docTemplate.toStringEnd() << endl;
  cout << "DocTemplate start:\n" << textstyles->docTemplate.output_begin
    ("title", "css", "additional", "header", "footer", "") << endl;
  cout << "DocTemplate end:\n" << textstyles->docTemplate.output_end
    ("title", "css", "additional", "header", "footer", "") << endl;

  cout << "Style template:\n" << textstyles->starting_template << endl;
  cout << "Style separator: " << textstyles->style_separator << endl;

  cout << "Bold style: " << textstyles->bold.toString() << endl;
  cout << "text formatted in bold style: " << textstyles->bold.output("TEXT") << endl;
  cout << "Italics: " << textstyles->italics.toString() << endl;
  cout << "Underline: " << textstyles->underline.toString() << endl;
  cout << "Color: " << textstyles->color.toString() << endl;
  cout << "ColorMap:\n" << textstyles->colorMap->toString() << endl;

  cout << "CharTranslator:\n" << textstyles->charTranslator->toString() << endl;
  cout << "Onestyle: " << textstyles->onestyle.toString() << endl;

  string i = "0x1b";
  cout << "original: " << i << endl;
  cout << "conversion: " << strtod(i.c_str(), 0) << endl;

  return 0;
}
