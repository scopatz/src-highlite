//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef SOURCEHIGHLIGHTER_H_
#define SOURCEHIGHLIGHTER_H_

#include <string>
#include <stack>

#include "highlightstate.h"
#include "my_sstream.h"
#include "eventgenerator.h"

class FormatterManager;
class HighlightToken;
class FormatterParams;
class HighlightEventListener;
class HighlightEvent;

typedef std::stack<HighlightStatePtr> HighlightStateStack;

/**
 * The main class performing the highlighting.  It relies on a HighlightState
 * (and its HighlightRule objects)
 */
class SourceHighlighter: public EventGenerator<HighlightEventListener,
        HighlightEvent> {
    /// the main (and initial) highlight state
    HighlightStatePtr mainHighlightState;

    /// the current highlight state
    HighlightStatePtr currentHighlightState;

    /// the stack for the highlight states
    HighlightStateStack stateStack;

    /// the formatter manager, used to format element strings
    const FormatterManager *formatterManager;

    /**
     * Whether to optimize output (e.g., adjacent text parts belonging
     * to the same element will be buffered and generated as a single text part)
     */
    bool optimize;

    /**
     * Whether formatting is currently suspended.  Note that matching for
     * regular expressions is not suspended: only the actual output of formatted
     * code is suspended.
     */
    bool suspended;

    /**
     * Additional parameters for the formatters
     */
    FormatterParams *formatterParams;

    /**
     * The current element being formatted (used for optmization and buffering)
     */
    std::string currentElement;

    /**
     * The buffer for the text for the current element
     */
    std::ostringstream currentElementBuffer;

    /**
     * Enters a new state (using the stack)
     * @param state
     */
    void enterState(HighlightStatePtr state);

    /**
     * Exits level states (-1 means exit all states)
     * @param level
     */
    void exitState(int level);

    /**
     * Exits all states in the stack (and thus go back to the initial main state)
     */
    void exitAll();

    /**
     * Computes the (possible) next state for the given rule (if required, also
     * performs reference replacement)
     * @param token
     */
    HighlightStatePtr getNextState(const HighlightToken &token);

    /**
     * Formats the given string as the specified element
     * @param elem
     * @param s
     */
    void format(const std::string &elem, const std::string &s);

    /**
     * Makes sure to flush the possible buffer of the current element
     * (e.g., during optimizations)
     */
    void flush();

public:
    SourceHighlighter(HighlightStatePtr mainState);
    ~SourceHighlighter();

    /**
     * Highlights a paragraph
     * @param paragraph
     */
    void highlightParagraph(const std::string &paragraph);

    HighlightStatePtr getCurrentState() const {
        return currentHighlightState;
    }

    const FormatterManager *getFormatterManager() const {
        return formatterManager;
    }

    void setFormatterManager(const FormatterManager *_formatterManager) {
        formatterManager = _formatterManager;
    }

    bool getOptimize() const {
        return optimize;
    }

    void setOptimize(bool b = true) {
        optimize = b;
    }

    void setFormatterParams(FormatterParams *p) {
        formatterParams = p;
    }

    bool isSuspended() const {
        return suspended;
    }

    void setSuspended(bool b = true) {
        suspended = b;
    }
};

#endif /*SOURCEHIGHLIGHTER_H_*/
