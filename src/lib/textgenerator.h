/**
 * C++ class: textgenerator.h
 *
 * Description: Use a TextStyle to format a string.
 *
 * Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
 * Copyright: See COPYING file that comes with this distribution
 */


#ifndef _TEXTGENERATOR_H_
#define _TEXTGENERATOR_H_

#include "textstyle.h"

class TextGenerator
{
private:
  TextStyle textstyle;

public:
    TextGenerator();
    TextGenerator(const TextStyle &style);
    TextGenerator(const std::string &repr);

    std::string generateEntire( const std::string &s );
    void subst_style(const std::string &s);
};

#endif /*_TEXTGENERATOR_H_*/
