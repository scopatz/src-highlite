//
// C++ Implementation: RegExpState
//
// Description: as regular expression state: contains the regular expression to
// match and the formatters for each alternative.
//
//
// Author: Lorenzo Bettini, http://www.lorenzobettini.it, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "regexpstate.h"

#include "messages.h"

#include <stdlib.h>

using namespace std;

int RegExpState::global_id = 1;

RegExpFormatter::RegExpFormatter(const string &el, RegExpStatePtr r, int exit,
        bool all) :
    elem(el), exit_state_level(exit), exit_all(all), next_state(r) {
}

void RegExpFormatter::setNextState(RegExpStatePtr r) {
    next_state_strong = r;
}

RegExpStatePtr RegExpFormatter::getNextState() const {
    RegExpStatePtr next = next_state.lock();
    if (!next)
        return next_state_strong;

    return next;
}

/**
 * Return the formatter associated to the passed index.
 * If the index is negative, it returns the default formatter.
 * @param index
 * @return
 */
const string &RegExpState::get_elem(int index) {
    return formatters[(index<0 ? 0 : index)]->elem;
}

void RegExpState::add_exp(const std::string &s, ParserInfo *parserInfo,
        RegExpFormatterPtr f) {
    if (alternative.get()) {
        alternative->add_exp(s, parserInfo, f);
        return;
    } else {
        if (nextAddMustCreateAnAlternative) {
            // a previous operation had recorded the fact that the next
            // add_exp should have been performed as a creation of an alternative
            add_alternative(s, parserInfo, f);

            // but further addition on the alternative must not create further alternatives
            alternative->nextAddMustCreateAnAlternative = false;
            return;
        }
    }

    const string &ex = buffer.str();
    if (ex.size())
        buffer << "|";

    buffer << s;

    formatters.push_back(f);
    subExpressions.push_back(make_pair(s, *parserInfo));
}

void RegExpState::add_exp(const std::string &s, ParserInfo *parserInfo,
        const format_vector &f) {
    if (alternative.get()) {
        alternative->add_exp(s, parserInfo, f);
        return;
    }

    RegExpState *myalternative;
    
    if (buffer.str()== "") {
        // we must not add an alternative: this state is the alternative
        myalternative = this;
    } else {
        // we must isolate this regexp in an alternative
        alternative = RegExpStatePtr(new RegExpState);

        myalternative = alternative.get();
    }

    // the default formatter could be already set, and so we must
    // transmit it right now, otherwise the alternative will never have it.
    if (formatters[0].get()) {
        myalternative->set_default_formatter(formatters[0]);
    }

    // another add exp on the alternative must create another alternative
    myalternative->nextAddMustCreateAnAlternative = true;

    myalternative->buffer << s;

    // if the default formatter is not set, reserve space for it
    if (myalternative->formatters[0].get())
        ;

    std::copy(f.begin(), f.end(), back_inserter(myalternative->formatters));

    // add a subexpression for each formatter (just to be consistent with
    // other cases).
    for (format_vector::const_iterator it = f.begin(); it != f.end(); ++it)
        myalternative->subExpressions.push_back(make_pair(s, *parserInfo));
}

void RegExpState::add_alternative(const std::string &s, ParserInfo *parserInfo,
        RegExpFormatterPtr f) {
    if (!alternative.get()) {
        if (buffer.str()== "") {
            // we must not add an alternative: this state is the alternative
            add_exp(s, parserInfo, f);

            // but the next add should be put in an alternative
            nextAddMustCreateAnAlternative = true;
        } else {
            alternative = RegExpStatePtr(new RegExpState);

            // the default formatter could be already set, and so we must
            // transmit it right now, otherwise the alternative will never have it.
            if (formatters[0].get()) {
                alternative->set_default_formatter(formatters[0]);
            }

            // forward to the alternative
            alternative->add_exp(s, parserInfo, f);

            // another add exp on the alternative must create another alternative
            alternative->nextAddMustCreateAnAlternative = true;
        }
    } else {
        alternative->add_alternative(s, parserInfo, f);
    }
}

void RegExpState::setHasMarkedAlternatives() {
    if (alternative.get()) {
        alternative->setHasMarkedAlternatives();
    } else {
        hasMarkedAlternatives = true;
    }
}

void RegExpState::setAllAlternativesCanMatch() {
    if (alternative.get()) {
        alternative->setAllAlternativesCanMatch();
    } else {
        allAlternativesCanMatch = true;
    }
}

void RegExpState::setHasSubExpressions() {
    if (alternative.get()) {
        alternative->setHasSubExpressions();
    } else {
        hasSubExpressions = true;
    }
}

void RegExpState::setHasReferences() {
    if (alternative.get()) {
        alternative->setHasReferences();
    } else {
        hasReferences = true;
    }
}

void RegExpState::add_subexp_formatter(RegExpFormatterPtr f) {
    if (alternative.get()) {
        alternative->add_subexp_formatter(f);
        return;
    }

    formatters.push_back(f);

    // FIXME: insert a bogus subexpression
    subExpressions.push_back(make_pair("", ParserInfo()));
}

void RegExpState::freeze() throw(boost::bad_expression) {
    const string &buffered = buffer.str();
    try {
        reg_exp.assign(buffered);

        // call freeze also on alternative
        if (alternative.get()) {
            alternative->freeze();
        }
    } catch (boost::bad_expression &e) {
        printError("bad expression: " + buffered);
        throw;
    }
}

void RegExpState::set_default_formatter(RegExpFormatterPtr f) {
    formatters[0] = f;

    if (alternative.get())
        alternative->set_default_formatter(f);
}

RegExpFormatterPtr RegExpState::getLastFormatter() const {
    if (alternative.get())
        return alternative->getLastFormatter();

    return formatters[formatters.size()-1];
}

bool RegExpState::has_alternative() const {
    return (alternative.get());
}
