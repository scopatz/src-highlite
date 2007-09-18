/*
 * Copyright (C) 2007  Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/*
 * This program is part of GNU source-highlight
 * 
 * This tests regex preprocessing
 */

#include <iostream>
#include <boost/regex.hpp>

#include "asserttest.h"
#include "regexpreprocessor.h"
#include "stringdef.h"

using namespace std;

// variable to test results for all the tests
int result = 0;

void testPreprocess(const string &original, const string &expected) {
    cout << "original     : "<< original << endl;

    const string &preprocessed = RegexPreProcessor::preprocess(original);

    cout << "preprocessed : "<< preprocessed << endl;
    result += assertEquals(expected, preprocessed);
}

void testMakeNonSensitive(const string &original, const string &expected) {
    cout << "original     : "<< original << endl;

    const string &preprocessed = RegexPreProcessor::make_nonsensitive(original);

    cout << "preprocessed : "<< preprocessed << endl;
    result += assertEquals(expected, preprocessed);
}

void testOnlyNumOfMarkedSubexpressions(const string &original,
        unsigned int expected) {
    cout << "original     : "<< original << endl;

    unsigned int found = RegexPreProcessor::num_of_subexpressions(original);

    cout << "found        : "<< found << endl;
    result += assertEquals(expected, found);
}

void testNumOfMarkedSubexpressions(const string &original,
        unsigned int expected, const string &error = "",
        bool allow_outer_char = false, bool allow_outer_nonmarked = false) {
    cout << "original     : "<< original << endl;

    subexpressions_info sexp = RegexPreProcessor::num_of_marked_subexpressions(
            original, allow_outer_char, allow_outer_nonmarked);
    unsigned int found = sexp.marked;

    cout << "found        : "<< found << endl;
    if (sexp.errors.size())
        cout << "error        : "<< sexp.errors<< endl;
    result += assertEquals(expected, found);
    result += assertEquals(error, sexp.errors);
}

void testBackReference(const string &original, bool expected) {
    cout << "original     : "<< original << endl;

    bool found = RegexPreProcessor::contains_backreferences(original);

    cout << "found        : "<< found << endl;
    result += assertEquals(expected, found);
}

void testNumOfBackReferences(const string &original, int expected,
        int highest_expected) {
    cout << "original     : "<< original << endl;

    backreference_info
            found = RegexPreProcessor::num_of_backreferences(original);

    cout << "found        : "<< found.first<< endl;
    cout << "max          : "<< found.second<< endl;
    result += assertEquals(expected, found.first);
    result += assertEquals(highest_expected, found.second);
}

void testNumOfReferences(const string &original, int expected,
        int highest_expected) {
    cout << "original     : "<< original << endl;

    backreference_info
            found = RegexPreProcessor::num_of_references(original);

    cout << "found        : "<< found.first<< endl;
    cout << "max          : "<< found.second<< endl;
    result += assertEquals(expected, found.first);
    result += assertEquals(highest_expected, found.second);
}

void testReferenceReplace(const string &original,
        const backreference_replacements &replace, const string &expected) {
    cout << "original     : "<< original << endl;

    const string &repl = RegexPreProcessor::replace_references(original,
            replace);

    cout << "found        : "<< repl << endl;
    result += assertEquals(expected, repl);
}

void testReferenceReplace(const string &original,
        const regex_match_results &results, const string &expected) {
    cout << "original     : "<< original << endl;

    const string &repl = RegexPreProcessor::replace_references(original,
            results);

    cout << "found        : "<< repl << endl;
    result += assertEquals(expected, repl);
}

void testBackReferenceReplace(const string &original,
        const backreference_replacements &replace, const string &expected) {
    cout << "original     : "<< original << endl;

    const string &repl = RegexPreProcessor::replace_backreferences(original,
            replace);

    cout << "found        : "<< repl << endl;
    result += assertEquals(expected, repl);
}

void testBackReferenceReplace(const string &original,
        const regex_match_results &results, const string &expected) {
    cout << "original     : "<< original << endl;

    const string &repl = RegexPreProcessor::replace_backreferences(original,
            results);

    cout << "found        : "<< repl << endl;
    result += assertEquals(expected, repl);
}

void testSplit(const string &original, const subexpressions_strings &expected) {
    const subexpressions_strings *split;
    split = RegexPreProcessor::split_marked_subexpressions(original);
    cout << "split        : ";
    std::copy(split->begin(), split->end(), std::ostream_iterator<string>(cout));
    cout << endl;
    if (!std::equal(split->begin(), split->end(), expected.begin())) {
        ++result;
        cout << "are not equal!" << endl;
        cout << "expected    : ";
        std::copy(expected.begin(), expected.end(),
        std::ostream_iterator<string>(cout));
    }
}

int main() {
    cout << boolalpha;

    testPreprocess("simple", "simple");
    testPreprocess("(inside)", "(?:inside)");
    testPreprocess("(dou(b)le)", "(?:dou(?:b)le)");

    testMakeNonSensitive("foo", "[Ff][Oo][Oo]");

    testOnlyNumOfMarkedSubexpressions("none", 0);
    testOnlyNumOfMarkedSubexpressions("just (one)", 1);
    testOnlyNumOfMarkedSubexpressions("(3 of (them)) just (one)", 3);

    testOnlyNumOfMarkedSubexpressions("none \\(", 0);
    testOnlyNumOfMarkedSubexpressions("(?: again) none \\(", 0);

    testNumOfMarkedSubexpressions("none", 0,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);
    testNumOfMarkedSubexpressions("none", 0, "", true);
    testNumOfMarkedSubexpressions("just (one)", 0,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);
    testNumOfMarkedSubexpressions("just (one)", 1, "", true);
    testNumOfMarkedSubexpressions("(3 of (them)) just (one)", 1,
            subexpressions_info::ERR_NESTED_SUBEXP);
    
    // now some critic cases
    testNumOfMarkedSubexpressions("(\\((?:\\\\\\)|[^)])*\\))", 1);
    testNumOfMarkedSubexpressions("(\\[(?:\\\\\\]|[^\\]])*\\])", 1);
    testNumOfMarkedSubexpressions("(:[^:]+\\:)", 1);

    testNumOfMarkedSubexpressions("none \\(", 0,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);
    testNumOfMarkedSubexpressions("(?: again) none \\(", 0,
            subexpressions_info::ERR_OUTER_UNMARKED);
    testNumOfMarkedSubexpressions("(?: again) none \\(", 0, "", true, true);
    // outer nonmarked are allowed, but outer chars are not
    testNumOfMarkedSubexpressions("(?: again) none \\(", 0,
            subexpressions_info::ERR_OUTSIDE_SUBEXP, false, true);

    testNumOfMarkedSubexpressions("(just one)", 1);
    testNumOfMarkedSubexpressions("(just one (?:some) and unmarked)", 1);
    testNumOfMarkedSubexpressions("(just one \\( and escapes)", 1);
    testNumOfMarkedSubexpressions("(just one \\( and \\) escapes)", 1);
    testNumOfMarkedSubexpressions("(one) ", 1,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);

    testNumOfMarkedSubexpressions("(one", 1,
            subexpressions_info::ERR_UNBALANCED_PAREN);
    testNumOfMarkedSubexpressions("(one))", 1,
            subexpressions_info::ERR_UNBALANCED_PAREN);

    testNumOfMarkedSubexpressions("(one)(two)((?:three)*)", 3);
    testNumOfMarkedSubexpressions("(one) (two)", 1,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);

    subexpressions_strings expected;
    expected.push_back("(this)");
    expected.push_back("(is)");
    expected.push_back("(one)");
    testSplit("(this)(is)(one)", expected);

    expected.clear();
    expected.push_back("(this)");
    expected.push_back("(contains \\( some \\) other parenthesis)");
    expected.push_back("(and (?:non marked) ones)");
    testSplit(
            "(this)(contains \\( some \\) other parenthesis)(and (?:non marked) ones)",
            expected);

    testBackReference("this does not contain any", false);
    testBackReference("this does contain \\1 one", true);
    testBackReference("and also this one (?(2)...) does", true);
    testBackReference("while this one (?(foo)...) does NOT does", false);

    testNumOfBackReferences("this does not contain any", 0, 0);
    testNumOfBackReferences("this does contain \\1 one", 1, 1);
    testNumOfBackReferences("this does \\3 contain \\1 two", 2, 3);
    testNumOfBackReferences("and also this one (?(2)...) does", 1, 2);
    testNumOfBackReferences("and also \\1 this one (?(2)...) does", 2, 2);
    testNumOfBackReferences("and also this one (?(2)...) \\3 does", 2, 3);
    testNumOfBackReferences("while this one (?(foo)...) does NOT does", 0, 0);

    testNumOfReferences("this does not contain any", 0, 0);
    testNumOfReferences("this does contain @{1} one", 1, 1);
    testNumOfReferences("this does @{3} contain @{1} two", 2, 3);
    testNumOfReferences("while this one \\@{2} does NOT does", 0, 0);
    
    backreference_replacements replace(9);

    replace[1] = "SECOND";
    replace[2] = "THIRD";

    testReferenceReplace("this does not contain any", replace,
            "this does not contain any");

    // test for an empty replace string
    testReferenceReplace("this does contain @{1} one", replace,
            "this does contain  one");

    replace[0] = "FIRST";

    testReferenceReplace("this does contain @{1} one", replace,
            "this does contain FIRST one");

    testReferenceReplace("this does contain @{1} one", replace,
            "this does contain FIRST one");

    testReferenceReplace("and also this one (?(@{2})...) @{3} does", replace,
            "and also this one (?(SECOND)...) THIRD does");

    testReferenceReplace(
            "and (@{1}|@{3}@{1}) also this one (?((?(@{2})foo|bar))...) (@{3}) does",
            replace,
            "and (FIRST|THIRDFIRST) also this one (?((?(SECOND)foo|bar))...) (THIRD) does");

    // we test replacement when what we replace might be a special char in regex syntax
    replace[0] = "|";
    replace[1] = "$";
    replace[2] = "{";
    replace[3] = "=";
    
    testReferenceReplace("Here are special chars: @{1} @{2} @{3} @{4}", replace,
                "Here are special chars: \\| \\$ \\{ =");
    
    // now test substitutions using match results
    boost::regex test_regex("--\\[(=*)\\[");
    string to_match = "--[[";
    string to_substitute = "]]"; // between the ] ]
    regex_match_results what;

    result += assertEquals(true,
            boost::regex_search(to_match, what, test_regex));
    // no substitution must take place
    testReferenceReplace(to_substitute, what, "]]");

    // skip one char and replace with the first subexp
    to_substitute = "]@{1}]"; // between the ] ]

    what = regex_match_results();
    to_match = "--[=[";

    result += assertEquals(true,
            boost::regex_search(to_match, what, test_regex));
    testReferenceReplace(to_substitute, what, "]=]");

    test_regex = boost::regex("--\\[(=*)\\[(-*)\\[");
    what = regex_match_results();
    to_substitute = "]@{1}]@{2}]";
    to_match = "--[=[-[";

    result += assertEquals(true,
            boost::regex_search(to_match, what, test_regex));
    testReferenceReplace(to_substitute, what, "]=]-]");

    what = regex_match_results();
    to_match = "--[=[-[";

    to_substitute = "](?(@{1})@{1}|@{2})]@{2}]";
    result += assertEquals(true,
            boost::regex_search(to_match, what, test_regex));
    testReferenceReplace(to_substitute, what, "](?(=)=|-)]-]");

    what = regex_match_results();

    to_match = "--[=[[";

    result += assertEquals(true,
            boost::regex_search(to_match, what, test_regex));
    testReferenceReplace(to_substitute, what, "](?(=)=|)]]");
    
    // check StringDef for backreferences
    
    StringDef s1("foo");
    StringDef s2("bar");
    
    result += assertTrue(!s1.isBackRef());
    
    s1 = StringDef("");
    s1.setBackRef(true);
    
    result += assertTrue(s1.isBackRef());
    result += assertTrue(!s2.isBackRef());

    StringDef *conc = StringDef::concat(&s1, &s2);
    
    result += assertTrue(conc->isBackRef());
    
    return result;
}
