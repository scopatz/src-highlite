/**
 * C++ class: textstyles.h
 *
 * Description: container of TextStyle objects.
 *
 * Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef _TEXTSTYLES_H_
#define _TEXTSTYLES_H_

#include "textstyle.h"
#include "colormap.h"
#include "chartranslator.h"
#include "doctemplate.h"

struct TextStyles
{
    TextStyle bold, italics, underline, notfixed, fixed,
    color, bg_color, onestyle;

    struct RefTextStyle
    {
      TextStyle anchor, inline_reference, postline_reference, postdoc_reference;
    } refstyle;
    std::string starting_template, style_separator, file_extension, line_prefix;
    CharTranslatorPtr charTranslator;
    ColorMapPtr colorMap;
    DocTemplate docTemplate;

    TextStyles() : charTranslator(new CharTranslator), colorMap(new ColorMap) {}
};

typedef boost::shared_ptr<TextStyles> TextStylesPtr;

#endif /*_TEXTSTYLES_H_*/
