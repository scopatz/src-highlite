//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef HIGHLIGHTEVENT_H_
#define HIGHLIGHTEVENT_H_

class HighlightToken;

/**
 * Event concerning an highlighting operation (e.g., formatting, entering
 * a new state, exiting a state, etc.)
 */
struct HighlightEvent {
    /// the type of the event
    enum HighlightEventType {FORMAT = 0, FORMATDEFAULT, ENTERSTATE, EXITSTATE};

    /// the token corresponding to the event
    const HighlightToken &token;
    
    HighlightEventType type;

    HighlightEvent(const HighlightToken &_token, HighlightEventType _type = FORMAT) :
        token(_token), type(_type) {
    }
    ~HighlightEvent() {
    }
};

#endif /*HIGHLIGHTEVENT_H_*/
