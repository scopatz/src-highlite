//
// C++ Implementation: RegexPreProcessor
//
// Description: performs operations or inspections on a string representing
// a valid regular expression
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpreprocessor.h"
#include <boost/regex.hpp>
#include "my_sstream.h"
#include <ctype.h>

using namespace std;

// IMPORTANT: the following regular expressions assume that the
// regular expression they try to match is a valid regular expression

// matches character sets in a regular expression
const boost::regex char_set_exp("\\[([^\\|]*)\\]");

// substitute a "(" with "(?:" if it's not followed by a ? and not preceeded by \\ char
const boost::regex from("(\\\\\\()|(\\((?!\\?))");
const string into = "(?1\\\\\\()(?2\\(\\?\\:)";

// found actual marking parenthesis, i.e., not preceeded by \\ and not followed by ?
const boost::regex paren("(?<!\\\\)\\((?!\\?)");

// regular expression matching a backreference, e.g., \1 or inside a conditional (?(1)...)
const boost::regex backreference("(\\\\[[:digit:]])|(\\(\\?\\([[:digit:]])");

const string
        subexpressions_info::ERR_OUTER_UNMARKED = "unmarked subexpressions are allowed only inside marked subexpressions";
const string
        subexpressions_info::ERR_NESTED_SUBEXP = "subexpressions of subexpressions are not allowed";
const string subexpressions_info::ERR_UNBALANCED_PAREN = "unbalanced parenthesis";
const string
        subexpressions_info::ERR_OUTSIDE_SUBEXP = "parts outside marked subexpressions are not allowed";

RegexPreProcessor::RegexPreProcessor() {
}

RegexPreProcessor::~RegexPreProcessor() {
}

const string RegexPreProcessor::preprocess(const string &s) {
    // substitute a "(" with "(?:" if it's not followed by a ? and not preceeded by \\ char
    return boost::regex_replace(s, from, into,
            boost::match_default | boost::format_all);
}

const string _make_nonsensitive(const string &s) {
    ostringstream result;

    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
        if (isalpha(*it))
            result << "[" << (char)toupper(*it) << (char)tolower(*it) << "]";
        else
            result << *it;

    return result.str();
}

const string RegexPreProcessor::make_nonsensitive(const string &s) {
    boost::sregex_iterator m1(s.begin(), s.end(), char_set_exp);
    boost::sregex_iterator m2;

    if (m1 == m2)
        return _make_nonsensitive(s);

    ostringstream buffer;
    string prefix;
    string suffix;

    for (boost::sregex_iterator it = m1; it != m2; ++it) {
        prefix = it->prefix();
        suffix = it->suffix();

        if (prefix.size()) {
            buffer << _make_nonsensitive(prefix);
        }

        buffer << (*it)[0];
    }

    if (suffix.size()) {
        buffer << _make_nonsensitive(suffix);
    }

    return buffer.str();
}

unsigned int RegexPreProcessor::num_of_subexpressions(const string &s)
{
    boost::sregex_iterator m1(s.begin(), s.end(), paren);
    boost::sregex_iterator m2;

    int counter = 0;
    
    for (boost::sregex_iterator it = m1; it != m2; ++it)
    {
      ++counter;
    }
    
    return counter;
}

const subexpressions_strings *RegexPreProcessor::split_marked_subexpressions(const string &s) {
    boost::sregex_iterator m1(s.begin(), s.end(), paren);
    boost::sregex_iterator m2;

    // we don't need to parse it (we can use the regex) since we assume that
    // the regular expression represented by s is made up of only
    // marked subexpressions and no nested subexpressions and char outside subexpressions
    
    subexpressions_strings *split = new subexpressions_strings;
    
    for (boost::sregex_iterator it = m1; it != m2; )
    {
        string prefix = it->prefix();
        if (prefix.size())
            split->push_back("(" + prefix);
            
        string suffix = it->suffix();
        if (++it == m2)
            split->push_back("(" + suffix);
    }
    
    return split;
}

subexpressions_info RegexPreProcessor::num_of_marked_subexpressions(const string &s) {
    subexpressions_info sexps;

    // number of open parenthesis
    int open_paren_num = 0;
    // whether we're inside a marked subexpressions
    bool found_marked_subexp = false;
    // len of string
    int len = s.size();
    // char we're examining
    char c;

    for (int i = 0; i < len; ++i) {
        c = s[i];
        if (c == '\\' && (i+1) < len && (s[i+1] == '(' || s[i+1] == ')')) {
            // skip the escaped paren
            ++i;
        } else if (c == '(') {
            // we found a subexp
            ++open_paren_num;

            if ((i+1) < len && s[i+1] == '?') {
                if (!found_marked_subexp) {
                    // outer subexpressions must be marked
                    sexps.errors = subexpressions_info::ERR_OUTER_UNMARKED;
                    return sexps;
                }
            } else {
                // it's a marked subexp
                if (found_marked_subexp) {
                    // we don't allow nested subexpressions
                    sexps.errors = subexpressions_info::ERR_NESTED_SUBEXP;
                    return sexps;
                }

                // we found a marked subexp
                found_marked_subexp = true;
                ++(sexps.marked);
            }
        } else if (c == ')') {
            if (!open_paren_num) {
                // unbalanced parenthesis
                sexps.errors = subexpressions_info::ERR_UNBALANCED_PAREN;
                return sexps;
            }

            --open_paren_num;

            // end of marked subexp
            if (!open_paren_num && found_marked_subexp)
                found_marked_subexp = false;
        } else {
            // we don't allow non marked parts
            if (!found_marked_subexp) {
                sexps.errors = subexpressions_info::ERR_OUTSIDE_SUBEXP;
                return sexps;
            }
        }
    }

    // check that all paren are closed
    if (open_paren_num)
        sexps.errors = subexpressions_info::ERR_UNBALANCED_PAREN;

    return sexps;
}

bool RegexPreProcessor::contains_backreferences(const std::string &s) {
    return boost::regex_search(s, backreference);
}
