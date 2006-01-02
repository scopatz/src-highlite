/**
 * C++ class: doctemplate.h
 *
 * Description: The template for a document containing the output of
 * highlighting
 *
 * Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
 * Copyright: See COPYING file that comes with this distribution
 */

#include "doctemplate.h"
#include "substfun.h"

using namespace std;

DocTemplate::DocTemplate(const string &begin, const string &end) : 
    begin_repr(begin), end_repr(end)
{
}

string
DocTemplate::output_begin(const string &title, const string &cs, const string &add,
    const string &header, const string &footer)
{
    boost::regex title_exp(TITLE_VAR);
    boost::regex css_exp(CSS_VAR);
    boost::regex additional_exp(ADDITIONAL_VAR);
    boost::regex header_exp(HEADER_VAR);
    boost::regex footer_exp(FOOTER_VAR);
    
    string ret = subst(title_exp, begin_repr, title);
    ret = subst(css_exp, ret, cs);
    ret = subst(additional_exp, ret, add);
    ret = subst(header_exp, ret, header);
    ret = subst(footer_exp, ret, footer);
    
    return ret;   
}

string
DocTemplate::output_end(const string &title, const string &cs, const string &add,
    const string &header, const string &footer)
{
    boost::regex title_exp(TITLE_VAR);
    boost::regex css_exp(CSS_VAR);
    boost::regex additional_exp(ADDITIONAL_VAR);
    boost::regex header_exp(HEADER_VAR);
    boost::regex footer_exp(FOOTER_VAR);
    
    string ret = subst(title_exp, end_repr, title);
    ret = subst(css_exp, ret, cs);
    ret = subst(additional_exp, ret, add);
    ret = subst(header_exp, ret, header);
    ret = subst(footer_exp, ret, footer);
    
    return ret;   
}

