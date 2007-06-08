/*
 * Copyright (C) 2007  Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
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
#include <algorithm>

#include "asserttest.h"
#include "regexpreprocessor.h"

using namespace std;

// variable to test results for all the tests
int result = 0;

void testPreprocess(const string &original, const string &expected) {
    cout << "original     : " << original << endl;

    const string &preprocessed = RegexPreProcessor::preprocess(original);

    cout << "preprocessed : " << preprocessed << endl;
    result += assertEquals(expected, preprocessed);
}

void testMakeNonSensitive(const string &original, const string &expected) {
    cout << "original     : " << original << endl;

    const string &preprocessed = RegexPreProcessor::make_nonsensitive(original);

    cout << "preprocessed : " << preprocessed << endl;
    result += assertEquals(expected, preprocessed);
}

void testOnlyNumOfMarkedSubexpressions(const string &original,
        unsigned int expected) {
    cout << "original     : " << original << endl;

    unsigned int found = RegexPreProcessor::num_of_subexpressions(original);

    cout << "found        : " << found << endl;
    result += assertEquals(expected, found);
}

void testNumOfMarkedSubexpressions(const string &original,
        unsigned int expected, const string &error = "") {
    cout << "original     : " << original << endl;

    subexpressions_info
            sexp = RegexPreProcessor::num_of_marked_subexpressions(original);
    unsigned int found = sexp.marked;

    cout << "found        : " << found << endl;
    if (sexp.errors.size())
        cout << "error        : " << sexp.errors << endl;
    result += assertEquals(expected, found);
    result += assertEquals(error, sexp.errors);
}

void testBackReference(const string &original, bool expected) {
    cout << "original     : " << original << endl;

    bool found = RegexPreProcessor::contains_backreferences(original);

    cout << "found        : " << found << endl;
    result += assertEquals(expected, found);
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
    testNumOfMarkedSubexpressions("just (one)", 0,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);
    testNumOfMarkedSubexpressions("(3 of (them)) just (one)", 1,
            subexpressions_info::ERR_NESTED_SUBEXP);

    testNumOfMarkedSubexpressions("none \\(", 0,
            subexpressions_info::ERR_OUTSIDE_SUBEXP);
    testNumOfMarkedSubexpressions("(?: again) none \\(", 0,
            subexpressions_info::ERR_OUTER_UNMARKED);

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
    testSplit("(this)(contains \\( some \\) other parenthesis)(and (?:non marked) ones)", expected);

    testBackReference("this does not contain any", false);
    testBackReference("this does contain \\1 one", true);
    testBackReference("and also this one (?(2)...) does", true);
    testBackReference("while this one (?(foo)...) does NOT does", false);

    return result;
}
