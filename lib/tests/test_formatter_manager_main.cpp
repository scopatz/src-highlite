#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "srchilite/formattermanager.h"
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

class MyFormatter : public Formatter {
    virtual void format(const std::string &s, const FormatterParams *params) {
        cout << "formatting " << s << endl;
    }
};

int main() {
    FormatterPtr defaultFormatter = FormatterPtr(new MyFormatter);
    FormatterManager formatterManager(defaultFormatter);

    FormatterPtr fooFormatter = FormatterPtr(new MyFormatter);
    FormatterPtr barFormatter = FormatterPtr(new MyFormatter);

    formatterManager.addFormatter("foo", fooFormatter);
    formatterManager.addFormatter("bar", barFormatter);

    assertEquals(defaultFormatter.get(), formatterManager.getFormatter("nonexistent").get());
    assertEquals(fooFormatter.get(), formatterManager.getFormatter("foo").get());
    assertEquals(barFormatter.get(), formatterManager.getFormatter("bar").get());

    // hasGenerator returns an invalid pointer if there's no association
    assertTrue(formatterManager.hasFormatter("non existent").get() == 0);
    assertEquals(fooFormatter.get(), formatterManager.hasFormatter("foo").get());

    // check that reset removes all elements in the map
    formatterManager.reset();
    assertTrue(formatterManager.getFormatterMap().size() == 0, "formatter map should be empty");

    cout << "test_formatter_manager: SUCCESS" << endl;

    return 0;
}
