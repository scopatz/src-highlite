#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <list>

#include <sstream>
#include "srchilite/bufferedoutput.h"
#include "asserttestexit.h"

using namespace std;
using namespace srchilite;

int main() {
    ostringstream os;

    BufferedOutput bufferedOutput(os);

    bufferedOutput.output("first line");
    bufferedOutput.output(" blah blah");

    bufferedOutput.postLineInsert("post first line\n");
    bufferedOutput.postLineInsert("post first line\n"); // duplicates are not stored
    bufferedOutput.postLineInsert("post first line 2\n");
    bufferedOutput.postLineInsert("post first line 3\n");

    bufferedOutput.postDocInsert("post doc");
    bufferedOutput.postDocInsert("post doc");
    bufferedOutput.postDocInsert("post doc 2");
    bufferedOutput.postDocInsert("post doc 3");

    cout << "line: " << os.str() << endl;

    assertEquals("first line blah blah", os.str());

    os.str("");

    bufferedOutput.writePostLine("PRE ");

    const string &postLine = os.str();

    cout << "post line: " << postLine << endl;

    assertEquals(
            "PRE post first line\nPRE post first line 2\nPRE post first line 3\n",
            postLine);

    os.str("");

    bufferedOutput.writePostDoc("PRE ");

    const string &postDoc = os.str();

    cout << "post doc: " << postDoc << endl;

    assertEquals("PRE post docPRE post doc 2PRE post doc 3", postDoc);

    // now try with collections
    list<string> postline, postdoc;

    postline.push_back("NEW post first line\n");
    postline.push_back("NEW post first line 2\n");
    postline.push_back("NEW post first line\n");

    bufferedOutput.postLineInsertFrom(postline);

    os.str("");

    bufferedOutput.writePostLine("PRE ");

    const string &postLine2 = os.str();

    cout << "post line: " << postLine2 << endl;

    assertEquals("PRE NEW post first line\nPRE NEW post first line 2\n",
            postLine2);

    postdoc.push_back("NEW post doc");
    postdoc.push_back("NEW post doc 2");
    postdoc.push_back("NEW post doc");

    bufferedOutput.postDocInsertFrom(postdoc);

    os.str("");

    bufferedOutput.writePostDoc("PRE ");

    const string &postDoc2 = os.str();

    cout << "post doc: " << postDoc2 << endl;

    assertEquals("PRE NEW post docPRE NEW post doc 2", postDoc2);

    // check that the buffers were flushed
    os.str("");

    bufferedOutput.postLineInsert("foo");
    bufferedOutput.writePostLine("PRE ");
    assertEquals("PRE foo", os.str());

    os.str("");

    bufferedOutput.postDocInsert("foo");
    bufferedOutput.writePostDoc("PRE ");
    assertEquals("PRE foo", os.str());

    cout << "test_buffered_output: SUCCESS!" << endl;

    return 0;
}
