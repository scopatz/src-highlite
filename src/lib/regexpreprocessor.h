//
// C++ Interface: RegexPreProcessor
//
// Description: performs operations or inspections on a string representing
// a valid regular expression
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPREPROCESSOR_H
#define REGEXPREPROCESSOR_H

#include <string>
#include <list>

/**
 * info about subexpressions
 */
struct subexpressions_info {
    /// errors for subexpression checking
    const static std::string ERR_OUTER_UNMARKED;
    const static std::string ERR_NESTED_SUBEXP;
    const static std::string ERR_UNBALANCED_PAREN;
    const static std::string ERR_OUTSIDE_SUBEXP;
    
    /// num of marked subexpressions
    unsigned int marked;
    /// error specifications, if any
    std::string errors;
    
    subexpressions_info() : marked(0) {}
};

/**
 * all the marked subexpressions in a list
 */
typedef std::list<std::string> subexpressions_strings;

/**
 preprocess a regular expression, e.g., transform "()" into "(?:)"

 @author Lorenzo Bettini
 */
class RegexPreProcessor {
public:
    RegexPreProcessor();

    ~RegexPreProcessor();

    /**
     * translates marked subexpressions (...) into non marked subexpressions (?: )
     * @return the translated string
     */
    static const std::string preprocess(const std::string &s);

    /**
     * translates the expression into a case nonsensitive expression, i.e.,
     * foo is translated into [Ff][Oo][Oo]
     * @return the translated string
     */
    static const std::string make_nonsensitive(const std::string &s);

    /**
     * counts the number of marked subexpressions (...)
     * @return the number of marked subexpressions
     */
    static unsigned int num_of_subexpressions(const std::string &s);

    /**
     * check that the expressions is made up of marked subexpressions (...)
     * and no nested subexpressions and no char outside subexpressions
     * 
     * @return the struct containing the number of marked subexpressions
     * and possible errors
     */
    static subexpressions_info num_of_marked_subexpressions(const std::string &s);
    
    /**
     * Splits the marked subexpressions of a regular expression made up of only
     * marked subexpressions and no nested subexpressions and char outside subexpressions
     * (thus, before calling this, you must make sure that num_of_marked_subexpressions
     * did not return an error.
     * 
     * @return the subexpressions in a collection (this is allocated on the heap, so
     * it is up to the caller to delete it)
     */
    static const subexpressions_strings *split_marked_subexpressions(const std::string &s);

    /**
     * Checks whether the passed regular expression string contains
     * a backreference (e.g., either \1 or a conditional with a backreference
     * (?(1)...)
     * 
     * @return true if the passed regular expression string contains
     * a backreference
     */
    static bool contains_backreferences(const std::string &s);
};

#endif
