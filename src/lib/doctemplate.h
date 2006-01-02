/**
 * C++ class: doctemplate.h
 *
 * Description: The template for a document containing the output of
 * highlighting
 *
 * Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef _DOCTEMPLATE_H_
#define _DOCTEMPLATE_H_

#include <string>

#define TITLE_VAR_TEXT "$title" // the text of the title variable
#define CSS_VAR_TEXT "$css" // the text of the css variable
#define ADDITIONAL_VAR_TEXT "$additional" // the text of the additional text variable
#define HEADER_VAR_TEXT "$header" // the text of the header variable
#define FOOTER_VAR_TEXT "$footer" // the text of the footer variable
#define TITLE_VAR "\\" TITLE_VAR_TEXT // the name of the title variable as regexp
#define CSS_VAR "\\" CSS_VAR_TEXT // the name of the css variable as regexp
#define ADDITIONAL_VAR "\\" ADDITIONAL_VAR_TEXT // the text of the additional text variable as regexp
#define HEADER_VAR "\\" HEADER_VAR_TEXT // the text of the header variable as regexp
#define FOOTER_VAR "\\" FOOTER_VAR_TEXT // the text of the footer variable as regexp

class DocTemplate
{
    std::string begin_repr, end_repr;
public:
	DocTemplate(const std::string &begin = "", const std::string &end = "");
    
    std::string output_begin(const std::string &title, const std::string &cs, 
        const std::string &add, const std::string &header, const std::string &footer);
    std::string output_end(const std::string &title, const std::string &cs, 
        const std::string &add, const std::string &header, const std::string &footer);

    const std::string &toStringBegin() const { return begin_repr; }
    const std::string &toStringEnd() const { return end_repr; }
};

#endif /*_DOCTEMPLATE_H_*/
