#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/ctagscollector.h"
#include "srchilite/ctagsformatter.h"
#include "srchilite/formatterparams.h"
#include "srchilite/tostringcollection.h"
#include "srchilite/ctagsmanager.h"
#include "srchilite/ioexception.h"
#include "srchilite/verbosity.h"
#include <sstream>

using namespace std;
using namespace srchilite;

#ifndef BASEDIR
#define BASEDIR ""
#endif

void printResults(const CTagsFormatterResults &results) {
    if (results.inlineResult.size()) {
        cout << "INLINE: " << results.inlineResult << endl;
    } else {
        if (results.postLineResult.size()) {
            cout << "POSTLINE: " << collectionRefToString(results.postLineResult, '\n');
        }

        if (results.postDocResult.size()) {
            cout << "POSTDOC: " << collectionRefToString(results.postDocResult, '\n');
        }
    }
}

int main() {
    // no ctags command
    CTagsManager ctagsManager("mytags", "", false, INLINE);
    CTagsFormatterResults results;

    string sourceFile = string(BASEDIR) + "readtags.h";

    cout << "sourceFile: " << sourceFile << endl;

    TextStyles textStyles;
    const char *vars[] = { "linenum", "infilename", "infile", "outfile", 0 };

    textStyles.refstyle.anchor = TextStyle(
            "<A>$text - $outfile - $infile($infilename):$linenum<A>", vars);
    textStyles.refstyle.inline_reference = TextStyle(
            "<IN>$text - $outfile - $infile($infilename):$linenum<IN>", vars);
    textStyles.refstyle.postline_reference = TextStyle(
            "<PL>$text - $outfile - $infile($infilename):$linenum<PL>", vars);
    textStyles.refstyle.postdoc_reference = TextStyle(
            "<PD>$text - $outfile - $infile($infilename):$linenum<PD>", vars);

    // pretend the output is readtags.html
    CTagsFormatter *_formatter =
            ctagsManager.createCTagsFormatter(textStyles.refstyle);
    CTagsFormatter &formatter = *_formatter;
    formatter.setFileInfo(sourceFile, "readtags.html");

    // test tags found in file readtags.h
    FormatterParams fileInfo(sourceFile);
    fileInfo.filename = sourceFile;
    fileInfo.line = 1;

    formatter.formatCTags("READTAGS_H", results, &fileInfo);
    printResults(results);
    assertEquals("<IN>READTAGS_H - readtags.html - " + sourceFile
            + "(readtags.h):22<IN>", results.inlineResult);

    results.clear();
    fileInfo.line = 22;
    // this must be detected as an anchor, since the line number is the same
    formatter.formatCTags("READTAGS_H", results, &fileInfo);
    printResults(results);
    assertEquals("<A>READTAGS_H - readtags.html - " + sourceFile
            + "(readtags.h):22<A>", results.inlineResult);

    results.clear();
    formatter.formatCTags("file", results, &fileInfo);
    printResults(results);
    assertEquals("<PL>file - readtags.html - " + sourceFile
            + "(readtags.h):112<PL>\n<PL>file - readtags.html - " + sourceFile
            + "(readtags.h):72<PL>\n", collectionRefToString(results.postLineResult, 0));

    /*
     results.clear();
     collectorInline.setRefPosition(POSTDOC);
     fileInfo.line = 1;
     formatter.formatCTags("READTAGS_H", results, &fileInfo);
     printResults(results);
     // this should be postdoc
     assertEquals("<PD>READTAGS_H - readtags.html - " + sourceFile
     + "(readtags.h):22<PD>\n", results.postDocResult);
     */

    delete _formatter;

    // try with a non existing file
    try {
        CTagsManager ctagsManager4("mytags4", "", false, INLINE);
        _formatter = ctagsManager4.createCTagsFormatter(textStyles.refstyle);
        assertTrue(false); // must not get here
    } catch (IOException &e) {
        cout << e << endl;
        ostringstream o;
        o << e;
        assertEquals("cannot open tag file mytags4.", o.str());
    }

    Verbosity::setVerbosity(true);

    // try with a wrong command
    try {
        CTagsManager ctagsManager3("mytags3", "foobarcommand", true, INLINE);
        ctagsManager3.runCTagsCmd();
        assertTrue(false); // must not get here
    } catch (IOException &e) {
        cout << e << endl;
        ostringstream o;
        o << e;
        assertEquals("error running ctags command foobarcommand.", o.str());
    }

    // now try running the ctags command
    string
            ctagsCommand =
                    CTAGS " --excmd=n --fields=+n -o mytags2 " BASEDIR "test_readtags_main.cpp " BASEDIR "readtags.h";

    cout << "trying running " << ctagsCommand << endl;

    CTagsManager ctagsManager2("mytags2", ctagsCommand, true, INLINE);

    _formatter = ctagsManager2.createCTagsFormatter(textStyles.refstyle);
    _formatter->setFileInfo(sourceFile, "readtags.html");

    // test tags found in file readtags.h
    fileInfo.filename = sourceFile;
    fileInfo.line = 1;

    _formatter->formatCTags("READTAGS_H", results, &fileInfo);
    printResults(results);
    assertEquals("<IN>READTAGS_H - readtags.html - " + sourceFile
            + "(readtags.h):22<IN>", results.inlineResult);

    results.clear();
    fileInfo.line = 22;
    // this must be detected as an anchor, since the line number is the same
    _formatter->formatCTags("READTAGS_H", results, &fileInfo);
    printResults(results);
    assertEquals("<A>READTAGS_H - readtags.html - " + sourceFile
            + "(readtags.h):22<A>", results.inlineResult);

    results.clear();
    _formatter->formatCTags("file", results, &fileInfo);
    printResults(results);
    assertEquals("<PL>file - readtags.html - " + sourceFile
            + "(readtags.h):112<PL>\n<PL>file - readtags.html - " + sourceFile
            + "(readtags.h):72<PL>\n", collectionRefToString(results.postLineResult, 0));

    delete _formatter;

    cout << "test_ctagsmanager: SUCCESS!" << endl;

    return 0;
}
