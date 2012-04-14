#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <iterator>

#include "asserttestexit.h"
#include "srchilite/lineranges.h"
#include <sstream>

using namespace std;
using namespace srchilite;

static std::ostream& operator<<(std::ostream& os,
        const LineRanges::RangeType &entry);

static void check_add_range(LineRanges &lineranges, const string &range);
static void check_wrong_add_range(LineRanges &lineranges, const string &range,
        RangeError error);
static void check_in_range(LineRanges &lineranges,
        const LineRanges::RangeElemType e);
static void check_not_in_range(LineRanges &lineranges,
        const LineRanges::RangeElemType e, bool checkContext = false,
        bool expectedInContext = false);

static void print_line_ranges(ostream &os, const LineRanges &lineranges);

void check_add_range(LineRanges &lineranges, const string &range) {
    RangeError result = lineranges.addRange(range);
    cout << "checking " << range << "..." << endl;
    assertTrue(result == NO_ERROR);
}

void check_wrong_add_range(LineRanges &lineranges, const string &range,
        RangeError error) {
    RangeError result = lineranges.addRange(range);
    cout << "checking " << range << "..." << endl;
    assertEquals(error, result);
}

std::ostream& operator<<(std::ostream& os, const LineRanges::RangeType &entry) {
    if (entry.second == 0) {
        os << entry.first;
    } else if (entry.first < 0) {
        os << "-" << entry.second;
    } else if (entry.second < 0) {
        os << entry.first << "-";
    } else {
        os << entry.first << "-" << entry.second;
    }

    return os;
}

void print_line_ranges(ostream &os, const LineRanges &lineranges) {
    for (LineRanges::LineRangeSet::const_iterator it =
            lineranges.getLineRangeSet().begin(); it
            != lineranges.getLineRangeSet().end(); ++it) {
        os << *it << endl;
    }
}

void check_in_range(LineRanges &lineranges, const LineRanges::RangeElemType e) {
    cout << "is " << e << " in range? ";
    assertTrue(lineranges.isInRange(e) == IN_RANGE);
    cout << "yes" << endl;
}

void check_not_in_range(LineRanges &lineranges,
        const LineRanges::RangeElemType e, bool checkContext,
        bool expectedInContext) {
    cout << "is " << e << " in range (expect no)? ";
    RangeResult result = lineranges.isInRange(e);
    assertFalse(result == IN_RANGE);
    cout << "no" << endl;
    if (checkContext) {
        cout << "is " << e << " in context range"
                << (!expectedInContext ? " (expect no)" : "") << "? ";
        assertEquals(expectedInContext, result == CONTEXT_RANGE);
        cout << (expectedInContext ? "yes" : "no") << endl;
    }
}

int main() {

    LineRanges lineranges;
    ostringstream buffer;

    check_add_range(lineranges, " 20");
    check_add_range(lineranges, "30 ");
    check_add_range(lineranges, "10");

    check_add_range(lineranges, "11-22");
    check_add_range(lineranges, "100 - 200");

    print_line_ranges(cout, lineranges);
    print_line_ranges(buffer, lineranges);

    assertEquals("10\n11-22\n20\n30\n100-200\n", buffer.str());

    check_wrong_add_range(lineranges, "foo", INVALID_RANGE_NUMBER);

    check_add_range(lineranges, "-33");
    check_add_range(lineranges, "-20");
    check_add_range(lineranges, "101 - ");
    check_add_range(lineranges, "5 - ");

    buffer.str("");
    print_line_ranges(cout, lineranges);
    print_line_ranges(buffer, lineranges);

    assertEquals("-20\n-33\n5-\n10\n11-22\n20\n30\n100-200\n101-\n",
            buffer.str());

    lineranges = LineRanges();

    lineranges.addRange("-5");
    lineranges.addRange("7");
    lineranges.addRange("10-20");

    check_in_range(lineranges, 1);
    check_not_in_range(lineranges, 6);
    check_in_range(lineranges, 7);
    check_not_in_range(lineranges, 8);
    check_in_range(lineranges, 10);
    check_in_range(lineranges, 15);
    check_in_range(lineranges, 20);
    check_not_in_range(lineranges, 25);

    // now checking lines which are less the ones already checked should fail
    check_not_in_range(lineranges, 1);
    check_not_in_range(lineranges, 6);

    // but if we reset it, it works again
    lineranges.reset();
    check_in_range(lineranges, 1);
    check_not_in_range(lineranges, 6);
    check_in_range(lineranges, 7);
    check_not_in_range(lineranges, 8);

    lineranges.reset();
    lineranges.addRange("30-");

    check_in_range(lineranges, 20);
    check_not_in_range(lineranges, 25);
    check_in_range(lineranges, 30);
    check_in_range(lineranges, 100);

    // with unspecified context lines, we must always get false context
    lineranges.reset();
    check_not_in_range(lineranges, 6, true, false);
    check_not_in_range(lineranges, 8, true, false);
    check_not_in_range(lineranges, 25, true, false);

    lineranges.reset();
    lineranges.setContextLines(1);
    check_not_in_range(lineranges, 6, true, true);
    check_not_in_range(lineranges, 8, true, true);
    check_not_in_range(lineranges, 9, true, true);
    check_not_in_range(lineranges, 25, true, false);
    check_not_in_range(lineranges, 28, true, false);
    check_not_in_range(lineranges, 29, true, true);

    lineranges.reset();
    lineranges.setContextLines(2);
    check_not_in_range(lineranges, 6, true, true);
    check_not_in_range(lineranges, 8, true, true);
    check_not_in_range(lineranges, 9, true, true);
    check_not_in_range(lineranges, 25, true, false);
    check_not_in_range(lineranges, 28, true, true);
    check_not_in_range(lineranges, 29, true, true);

    lineranges.reset();
    lineranges.setContextLines(5);
    check_not_in_range(lineranges, 6, true, true);
    check_not_in_range(lineranges, 8, true, true);
    check_not_in_range(lineranges, 9, true, true);
    check_not_in_range(lineranges, 25, true, true);
    check_not_in_range(lineranges, 28, true, true);
    check_not_in_range(lineranges, 29, true, true);

    return 0;
}
