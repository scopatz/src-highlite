//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef DEBUGLISTENER_H_
#define DEBUGLISTENER_H_

#include <iostream>

#include "highlighteventlistener.h"

class HighlightEvent;

/**
 * Implementation of highlight events that prints debug information
 */
class DebugListener : public HighlightEventListener {
    /// where to output debug info (default stdout)
    std::ostream &os;

    /// whether to act in step mode (wait for the user ENTER after each step)
    bool interactive;
public:
    DebugListener(std::ostream &_os = std::cout);
    virtual ~DebugListener();

    virtual void notify(const HighlightEvent &event);

    void setInteractive(bool i = true) {
        interactive = i;
    }

    /**
     * Waits for the user to press ENTER
     */
    void step();
};

#endif /*DEBUGLISTENER_H_*/
