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
 * This program is part of GNU source-highlight simply to
 * check a regular expression against a given an expression
 */

/*
 * some examples:
 * 

 ./check-regexp "([^[:alnum:]]+)[^[:blank:]]*(\1)[^[:blank:]]*(\1)" "|w|\$|e|d| ^w^w^ ?a?b?"
 trying to match: |w|$|e|d| ^w^w^ ?a?b?
 against        : ([^[:alnum:]]+)[^[:blank:]]*(\1)[^[:blank:]]*(\1)
 what[0]: |w|$|e|d|
 what[1]: |
 what[2]: |
 what[3]: |
 prefix:
 what[0]: ^w^w^
 what[1]: ^
 what[2]: ^
 what[3]: ^
 prefix:
 what[0]: ?a?b?
 what[1]: ?
 what[2]: ?
 what[3]: ?
 total number of matches: 3

 * 
 */

#include <cstdlib>
#include <boost/regex.hpp>
#include <iostream>

#include "check-regexp_cmd.h"

using namespace std;

int main(int argc, char * argv[]) {
    gengetopt_args_info args_info; // command line structure

    if (cmdline_parser(argc, argv, &args_info)!= 0)
        // calls cmdline parser. The user gived bag args if it doesn't return -1
        return EXIT_FAILURE;

    if (args_info.inputs_num < 2) {
        cerr << "Syntax: check-regexp <regular expression> <expressions...>" << endl;
        exit(EXIT_FAILURE);
    }

    boost::regex regex(args_info.inputs[0]);

    for (unsigned int i = 1; i < args_info.inputs_num; ++i) {
        string tomatch = args_info.inputs[i];

        std::string::const_iterator start, end;
        boost::match_results<std::string::const_iterator> what;
        boost::match_flag_type flags;

        start = tomatch.begin();
        end = tomatch.end();
        flags = boost::match_default;

        cout << "\nsearching      : " << tomatch << endl;
        cout << "for the regexp   : " << regex << endl;

        cout << "num of subexps   : " << regex.mark_count() << endl;
        
        int num_of_matches = 0;

        while (boost::regex_search(start, end, what, regex, flags)) {
            string prefix = what.prefix();
            if (prefix.size())
                cout << "prefix: " << prefix << endl;

            cout << "what[0]: " << what[0] << endl;

            for (unsigned int i = 1; i < what.size(); ++i) {
                if (what[i].matched) {
                    cout << "  what[" << i << "]: "<< what[i] << endl;

                    cout << "  length: " << what[i].length()<< endl;
                }
            }

            string suffix = what.suffix();
            if (suffix.size())
                cout << "suffix: " << suffix << endl;

            // update search position:
            start = what[0].second;
            // update flags:
            flags |= boost::match_prev_avail;
            flags |= boost::match_not_bob;

            ++num_of_matches;
        }

        cout << "total number of matches: " << num_of_matches << endl;
    }
}

