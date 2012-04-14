#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/linenumgenerator.h"
#include "srchilite/textstyle.h"

using namespace std;
using namespace srchilite;

int main() {

    TextStyle lineStyle("<LINE>$text</LINE>");

    LineNumGenerator lineNumGen(lineStyle, 5);

    string result;

    result = lineNumGen.generateLine(10);

    cout << "line: " << result << endl;

    assertEquals("<LINE>00010:</LINE> ", result);

    // test for padding

    lineNumGen = LineNumGenerator(lineStyle, 5, ' ');

    result = lineNumGen.generateLine(10);

    cout << "line: " << result << endl;

    assertEquals("<LINE>   10:</LINE> ", result);

    // test for anchors

    const char *vars[] = { "linenum", 0 };

    TextStyle anchorStyle("<A line$linenum>$text</A>", vars);
    lineNumGen.setAnchorStyle(anchorStyle);

    result = lineNumGen.generateLine(10);

    cout << "line: " << result << endl;

    assertEquals("<A line10><LINE>   10:</LINE></A> ", result);

    lineNumGen.setAnchorPrefix("__");

    result = lineNumGen.generateLine(10);

    cout << "line: " << result << endl;

    assertEquals("<A line__10><LINE>   10:</LINE></A> ", result);

    cout << "test_linenum: SUCCESS" << endl;

    return 0;
}
