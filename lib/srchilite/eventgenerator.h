//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef EVENTGENERATOR_H_
#define EVENTGENERATOR_H_

#include <list>

/**
 * A generic event generator, for listeners of type EventListener and events of
 * type EventType.  EventListener must implement the method notify(const EventType &)
 */
template <class EventListener, class EventType> class EventGenerator {
    /// the list of listeners
    std::list<EventListener *> listeners;
public:
    void addListener(EventListener *listener) {
        listeners.push_back(listener);
    }

    void removeListener(EventListener *listener) {
        listeners.remove(listener);
    }

    bool hasListeners() const {
        return listeners.size();
    }

    void notify(const EventType &event) {
        for (typename std::list<EventListener *>::const_iterator it =
                listeners.begin(); it != listeners.end(); ++it) {
            (*it)->notify(event);
        }
    }
};

#endif /*EVENTGENERATOR_H_*/
