/**
 * C++ class: textgenerator.cpp
 *
 * Description: Use a TextStyle to format a string.
 *
 * Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
 * Copyright: See COPYING file that comes with this distribution
 */

#include "textgenerator.h"

using namespace std;

TextGenerator::TextGenerator()
{
}

TextGenerator::TextGenerator(const TextStyle &style) : textstyle(style)
{
}

TextGenerator::TextGenerator(const string &repr) :
    textstyle(TextStyle(repr))
{
}

string
TextGenerator::generateEntire( const string &s )
{
  return textstyle.output(s);
}

void
TextGenerator::subst_style(const string &style)
{
    textstyle = TextStyle(textstyle.subst_style(style));
}
