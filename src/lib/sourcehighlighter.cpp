//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#include "sourcehighlighter.h"
#include "highlighttoken.h"
#include "matchingparameters.h"
#include "highlightrule.h"
#include "formattermanager.h"
#include "highlightevent.h"
#include "highlighteventlistener.h"

using namespace std;

/// represents highlighting as default
static HighlightToken defaultHighlightToken;
static HighlightEvent defaultHighlightEvent(defaultHighlightToken,
        HighlightEvent::FORMATDEFAULT);

/// avoid generate an event if there's no one listening
#define GENERATE_EVENT(token, type) if (hasListeners()) notify(HighlightEvent(token, type));

#define GENERATE_DEFAULT_EVENT(s) \
    if (hasListeners()) { \
        defaultHighlightToken.clearMatched(); \
        defaultHighlightToken.addMatched("default", s); \
        notify(defaultHighlightEvent); \
    }

SourceHighlighter::SourceHighlighter(HighlightStatePtr mainState) :
    mainHighlightState(mainState), currentHighlightState(mainState),
            formatterManager(0), optimize(false), formatterParams(0) {
}

SourceHighlighter::~SourceHighlighter() {
}

void SourceHighlighter::highlightParagraph(const std::string &paragraph) {
    std::string::const_iterator start = paragraph.begin();
    std::string::const_iterator end = paragraph.end();
    bool matched = true;
    HighlightToken token;
    MatchingParameters params;

    // note that we go on even if the string is empty, since it is crucial
    // to try to match also the end of buffer (some rules rely on that)
    while (matched) {
        matched = currentHighlightState->findBestMatch(start, end, token,
                params);

        if (matched) {
            // advance in the string, so that the part not matched
            // can be highlighted in the next loop
            start += (token.prefix.size() + token.matchedSize);

            if (token.prefix.size()) {
                // format non matched part with the current state's default element
                format(currentHighlightState->getDefaultElement(), token.prefix);
                GENERATE_DEFAULT_EVENT(token.prefix);
            }

            // now format the matched strings
            for (MatchedElements::const_iterator it = token.matched.begin(); it
                    != token.matched.end(); ++it) {
                format(it->first, it->second);
                GENERATE_EVENT(token, HighlightEvent::FORMAT);
            }

            // now we're not at the beginning of line anymore, if we matched some chars
            if (token.matchedSize)
                params.beginningOfLine = false;

            // check whether we must enter a new state
            HighlightStatePtr nextState = getNextState(token);

            if (nextState.get()) {
                enterState(nextState);
                GENERATE_EVENT(token, HighlightEvent::ENTERSTATE);
            } else if (token.rule->getExitLevel()) {
                // the rule requires to exit some states
                if (token.rule->getExitLevel() < 0) {
                    exitAll();
                } else {
                    exitState(token.rule->getExitLevel());
                }
                GENERATE_EVENT(token, HighlightEvent::EXITSTATE);
            }
        } else {
            // no rule matched, so we highlight it with the current state's default element
            // provided the string is not empty (if it is empty this is really useless)
            if (start != end) {
                const string s(start, end);
                format(currentHighlightState->getDefaultElement(), s);
                GENERATE_DEFAULT_EVENT(s);
            }
        }
    }

    if (optimize)
        flush(); // flush what we have buffered
}

HighlightStatePtr SourceHighlighter::getNextState(const HighlightToken &token) {
    HighlightStatePtr nextState = token.rule->getNextState();

    if (token.rule->isNested()) {
        // we must enter another instance of the current state
        nextState = currentHighlightState;
    }

    if (nextState.get() && nextState->getNeedsReferenceReplacement()) {
        // perform replacement for the next state
        // in case use the original state
        if (nextState->getOriginalState().get()) {
            // in case we had already performed replacements on the next state
            nextState = nextState->getOriginalState();
        }

        HighlightStatePtr copyState = HighlightStatePtr(new HighlightState(*nextState));
        copyState->setOriginalState(nextState);
        copyState->replaceReferences(token.matchedSubExps);
        return copyState;
    }

    return nextState;
}

void SourceHighlighter::enterState(HighlightStatePtr state) {
    stateStack.push(currentHighlightState);
    currentHighlightState = state;
}

/**
 * Exits level states (-1 means exit all states)
 * @param level
 */
void SourceHighlighter::exitState(int level) {
    // remove additional levels
    for (int l = 1; l < level; ++l)
        stateStack.pop();

    currentHighlightState = stateStack.top();
    stateStack.pop();
}

/**
 * Exits all states in the stack (and thus go back to the initial main state)
 */
void SourceHighlighter::exitAll() {
    currentHighlightState = mainHighlightState;
    stateStack = HighlightStateStack();
}

void SourceHighlighter::format(const std::string &elem, const std::string &s) {
    if (!s.size())
        return;

    // the formatter is allowed to be null
    if (formatterManager) {
        if (!optimize) {
            formatterManager->getFormatter(elem)->format(s, formatterParams);
        } else {
            // otherwise we optmize output generation: delay formatting a specific
            // element until we deal with another element; this way strings that belong
            // to the same element are formatted using only one tag: e.g.,
            // <comment>/* mycomment */</comment>
            // instead of
            // <comment>/*</comment><comment>mycomment</comment><comment>*/</comment>
            if (elem != currentElement) {
                if (currentElement.size())
                    flush();
            }

            currentElement = elem;
            currentElementBuffer << s;
        }
    }
}

void SourceHighlighter::flush() {
    if (formatterManager) {

        // flush the buffer for the current element
        formatterManager->getFormatter(currentElement)->format(currentElementBuffer.str(),
                formatterParams);

        // reset current element information
        currentElement = "";
        currentElementBuffer.str("");
    }
}
