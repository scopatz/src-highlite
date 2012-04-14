#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <iterator>

#include "asserttestexit.h"
#include "srchilite/regexranges.h"
#include <iostream>

using namespace std;
using namespace srchilite;

RegexRanges ranges;

void check_range_regex(const string &s, bool expectedTrue = true) {
    cout << "checking " << s << endl;
    if (expectedTrue)
        assertTrue(ranges.addRegexRange(s));
    else
        assertFalse(ranges.addRegexRange(s));
}

void check_match(const string &line, const string &expected = "") {
    cout << "searching inside " << line;
    const boost::regex *matched = 0;
    if (expected != "") {
        matched = ranges.matches(line);
        assertTrue(matched != 0);
        assertEquals(expected, matched->str());
        cout << " found " << *matched << endl;
    } else {
        assertTrue(ranges.matches(line) == 0);
        cout << " not found" << endl;
    }
}

void check_in_range(const string &s, bool expectedTrue = true) {
    cout << "checking " << s << "... ";
    if (expectedTrue) {
        assertTrue(ranges.isInRange(s));
    } else {
        assertFalse(ranges.isInRange(s));
    }
    cout << expectedTrue << endl;
}

int main() {
    cout << boolalpha;

    check_range_regex("simple regex");
    check_range_regex("[[:alpha:]]+");
    // test with a wrong regular expression
    check_range_regex("{notclosed", false);

    // reset regular expressions
    ranges.clear();

    check_range_regex("/// foo");
    check_range_regex("/// bar");

    check_match(" not contains the searched string...", "");
    check_match(" does contain /// foo the searched string...", "/// foo");
    check_match(" does contain /// bar the searched string...", "/// bar");

    check_in_range("not in range", false);
    check_in_range("not in range, /// bar but the range starts", false);
    check_in_range("now in range", true);
    check_in_range("still in range, and /// foo is not considered now", true);
    check_in_range("end of range /// bar", false);
    check_in_range("not in range", false);
    check_in_range("not in range, /// foo but the range starts", false);
    check_in_range("now in range", true);
    check_in_range("now in range", true);
    check_in_range("end of range /// foo", false);
    check_in_range("not in range", false);

    // now try with a more involved regular expression
    check_range_regex("/// [[:digit:]]{2}");
    check_in_range("not in range", false);
    check_in_range("not in range, /// 25 but the range starts", false);
    check_in_range("now in range", true);
    check_in_range("still in range, and /// foo is not considered now", true);
    check_in_range("end of range /// 27", false);
    check_in_range("not in range", false);

    return 0;
}
