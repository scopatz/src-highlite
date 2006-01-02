//
// C++ Interface: textstyle
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _TEXTSTYLE_H_
#define _TEXTSTYLE_H_

#include <string>
#include <vector>
#include <map>
#include <boost/regex.hpp>

#define STYLE_VAR_TEXT "$style" // the text of the style variable
#define TEXT_VAR_TEXT "$text" // the text of the text variable
#define STYLE_VAR "\\" STYLE_VAR_TEXT // the name of the style variable as regexp
#define TEXT_VAR "\\" TEXT_VAR_TEXT // the name of the text variable as regexp

typedef std::map<std::string, std::string> SubstitutionMapping;

class TextStyle
{
private:
  typedef std::vector<std::string> StringVector;
  typedef std::vector<int> IndexVector;
  typedef std::map<std::string, IndexVector> SubstitutionIndexes;
  boost::regex var_exp; // the regular expression to find variable occurrences

    std::string repr;
    StringVector parts; // contains all the string parts of this TextStyle.
    SubstitutionIndexes substitutions;
    // contains the indexes of parts where to substitute $vars.
    bool invalid;
    // whether to rebuild the vectors

    void build_vectors();

public:
    TextStyle(const std::string &s = "", const char **vars = 0);
    ~TextStyle();

    /**
     * substitutes $text with text and $style with style
     */
    std::string output(const std::string &text, const std::string &style = "");
    /**
     * for each i substitutes: subst_map[i].first occurrence with subst_map[i].second
     */
    std::string output(SubstitutionMapping &subst_map);
    /**
     * substitutes $style with style
     */
    std::string subst_style(const std::string &style = "");

    const std::string &toString() const { return repr; }

    /**
     * substitutes $text with the string representation of inner
     * e.g., if this is <b>$text</b> and inner is <i>$text</i>
     * this will return <b><i>$text</i></b>
     */
    TextStyle compose(const TextStyle &inner);

    /**
     * as compose, but acts on this instance
     */
    void update(const TextStyle &inner);
    void update(const std::string &inner);
    void update(const std::string &text, const std::string &style);

    /**
     * Whether this TextStyle contains the $style variable
     */
    bool containsStyleVar() const;

    /**
     * Whether it is only $style or $text
     */
    bool empty() const;
};

#endif /*_TEXTSTYLE_H_*/
