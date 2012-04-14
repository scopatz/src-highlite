#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <string>

#include "srchilite/eventgenerator.h"
#include <sstream>
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

ostringstream buffer;

struct MyEvent {
    string desc;

    MyEvent(const string &_desc) :
        desc(_desc) {
    }
};

struct MyListener {
    string name;

    MyListener(const string &_name) :
        name(_name) {
    }

    void notify(MyEvent e) {
        buffer << "listener: " << name << ", event: " << e.desc << endl;
    }
};

int main() {
    MyListener l1("l1"), l2("l2"), l3("l3");

    EventGenerator<MyListener, MyEvent> eventGenerator;

    assertFalse(eventGenerator.hasListeners());

    eventGenerator.addListener(&l1);
    eventGenerator.addListener(&l2);
    eventGenerator.addListener(&l3);

    assertTrue(eventGenerator.hasListeners());

    eventGenerator.notify(MyEvent("foo"));

    cout << buffer.str() << endl;

    assertEquals(
            "listener: l1, event: foo\nlistener: l2, event: foo\nlistener: l3, event: foo\n",
            buffer.str());

    buffer.str("");

    eventGenerator.removeListener(&l2);

    eventGenerator.notify(MyEvent("bar"));

    cout << buffer.str() << endl;

    assertEquals(
            "listener: l1, event: bar\nlistener: l3, event: bar\n",
            buffer.str());

    cout << "test_events: SUCCESS!" << endl;

    return 0;
}
