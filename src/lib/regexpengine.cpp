//
// C++ Implementation: regexpengine
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpengine.h"

#include "regexpreprocessor.h"

RegExpEngine::~RegExpEngine() {
}

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "textformatter.h"
#include "keys.h"
#include "langdefloader.h"
#include "messages.h"
#include "parserinfo.h"

// purpose:
// takes the contents of a file and transform to
// syntax highlighted code in html format

using namespace std;

typedef enum {FOUND_EOF=0, FOUND_NL, FOUND_END} load_line_ret;

load_line_ret load_line(std::string& s, std::istream& is) {
    s.erase();
    if (is.bad()|| is.eof())
        return FOUND_EOF;

    char c;
    while (is.get(c)) {
        if (c == '\n')
            return FOUND_NL;
        if (c != '\r')
            s.append(1, c);
    }

    return FOUND_END;
}

void RegExpEngine::process_file(const char *file) {
    istream *is = 0;

    if (file) {
        is = new ifstream(file);
        if (!is || ! (*is)) {
            cerr << "Error in opening " << file<< " for input" << endl;
            exit(1);
        }
    } else
        is = &cin;

    std::string s;

    std::string::const_iterator start, end;
    boost::smatch match;
    boost::smatch what;
    boost::match_flag_type flags;

    // the regexp state we try at the moment.
    RegExpStatePtr alternative;

    // the regexp state matching best;
    RegExpStatePtr best_alternative;

    initial_state = currentstate;

    fileinfo->line = 1;

    // for selecting the formatter
    int index_of_formatter = 0;
    // for selecting the subexpression (or the whole expression)
    int index_of_subexpression = 0;

    int smallest_prefix = -1;
    int biggest_length = -1;

    string prefix;

    load_line_ret ret;
    while ((ret = load_line(s, *is)) != FOUND_EOF) {
        bool matched = true;
        bool found_eol = false;
        start = s.begin();
        end = s.end();
        // reset the flags
        flags = boost::match_default;

        // always start with the current state
        alternative = currentstate;

        while (matched) {
            matched = false;

            if (alternative->has_alternative()) {
                // this means that the state contains a list of alternative states
                // so we must try to match all the states and use the one that matches best
                // i.e., with the smallest prefix and the biggest match length
                smallest_prefix = -1;
                biggest_length = -1;
                while (alternative.get()) {
                    if (boost::regex_search(start, end, match,
                            alternative->reg_exp, flags)) {
                        const std::string &match_prefix = match.prefix();
                        if (smallest_prefix < 0 || (boost::smatch::size_type)smallest_prefix >= match_prefix.size()) {
                            if ((boost::smatch::size_type)smallest_prefix > match_prefix.size()|| biggest_length < 0 || (boost::smatch::difference_type)biggest_length < match.length()) {
                                prefix = match.prefix();
                                smallest_prefix = match_prefix.size();
                                biggest_length = match.length();
                                best_alternative = alternative;
                                matched = true;
                                // copy it, otherwise the next call will overwrite it
                                what = match;
                            }
                        }
                    }
                    alternative = alternative->alternative;
                }

                if (matched) {
                    // store the one that matched best
                    alternative = best_alternative;
                } else {
                    // reset the original current_state
                    alternative = currentstate;
                }
            } else if (boost::regex_search(start, end, what,
                    alternative->reg_exp, flags)) {
                // otherwise, all the alternatives of the state are stored as
                // a big alternation, where all alternatives are grouped
                prefix = what.prefix();
                matched = true;
            }

            if (matched) {
                // see if what matched has subexpressions, if so, put it into the
                // stack of environments for references
                if (alternative->hasSubExpressions) {
                    reference_env.push(what);
                }
                
                if (alternative->hasMarkedAlternatives) {
                    // we must inspect all the sub_matches
                    // to find the subexpression that matched
                    for (unsigned int i = 1; i < what.size(); ++i) {
                        if (what[i].matched) {
                            index_of_formatter = i;
                            index_of_subexpression = i;
                            break; // no other match is possible
                        }
                    }
                } else {
                    // the alternative state contains only one expression, with
                    // marked subexpressions, so we must format the whole match

                    // the formatter at 0 is the normal formatter
                    index_of_formatter = 1;
                    // we select the whole match
                    index_of_subexpression = 0;

                    // this is OK also in the case when allAlternativesCanMatch:
                    // we consider the whole expression, and all formatters share the
                    // same exit state, so we can use the first one
                }

                // part that possibly did not match
                if (prefix.size())
                    format(-1, alternative, prefix);

                if (alternative->allAlternativesCanMatch) {
                    // we must format each subexpression that matched
                    for (unsigned int i = 1; i < what.size(); ++i) {
                        if (what[i].matched) {
                            format(i, alternative, what[i]);
                        }
                    }
                    
                    // only the last formatter has the correct next state
                    index_of_formatter = what.size() - 1;
                } else {
                    // format the part that matched
                    format(index_of_formatter, alternative,
                            what[index_of_subexpression]);
                }

                if (alternative->formatters[index_of_formatter]->getNextState()) {
                    // we must enter another state
                    enterState(alternative, index_of_formatter);
                } else if (alternative->formatters[index_of_formatter]->exit_state_level) {
                    if (alternative->formatters[index_of_formatter]->exit_all) {
                        // we must go back to the outermost state
                        exitAll();
                    } else {
                        // we must get back to exit_state_level states
                        exitState(alternative->formatters[index_of_formatter]->exit_state_level);
                    }
                }

                // now let's continue with what's left of the original input
                start = what[index_of_subexpression].second;
                if (!(*start)) {
                    if (found_eol)
                        matched = false; // we had already matched end of line

                    // we might need to match the eol itself, so let's perform another loop
                    found_eol = true;
                }

                if (what[0].first != what[0].second) {
                    // we actually consumed something, so the start of the string
                    // must not be interpreted as the beginning of the line
                    flags |= boost::match_not_bol;
                }

                // we always search for the next match by using the original current state
                alternative = currentstate;
            } else {
                // format the non-matching part as normal
                format(-1, alternative, string(start, end));
                matched = false;
            }
        }

        if (ret == FOUND_NL)
            formatter->format_nl("\n");

        (fileinfo->line)++;
    }

    // make sure we flush all the buffered parts
    formatter->flush();

    if (file)
        delete is;

    currentstate = initial_state; // reset the initial state
}

void RegExpEngine::enterState(RegExpStatePtr state, int index) {
    states_stack.push(currentstate);
    RegExpStatePtr next_state = state->formatters[index]->getNextState();
    
    if (next_state->hasReferences) {
        // we must make a copy of the state, since we must change its regexp
        // after performing the substitution
        
        if (!reference_env.size()) {
            foundBug("reference environment empty", __FILE__, __LINE__);
        }

        next_state = RegExpStatePtr(new RegExpState(*next_state));
        
        // perform the reference replacement
        next_state->reg_exp.assign(RegexPreProcessor::replace_references(
                next_state->reg_exp.str(), 
                reference_env.top()));
        
        currentstate = next_state;
    } else {
        currentstate = next_state;
    }
}

void RegExpEngine::exitState(int level) {
    // remove additional levels
    for (int l = 1; l < level; ++l)
        states_stack.pop();

    currentstate = states_stack.top();
    states_stack.pop();
    
    if (currentstate->hasReferences) {
        if (!reference_env.size()) {
            foundBug("reference environment empty", __FILE__, __LINE__);
        }

        // we must restore also the reference env
        reference_env.pop();
    }
}

void RegExpEngine::exitAll() {
    currentstate = initial_state;
    states_stack = stack_of_states();
    reference_env = stack_of_matches();
}

void RegExpEngine::format(int index, RegExpStatePtr state, const std::string &s) {
    formatter->format(state->get_elem(index), s, fileinfo);
}

