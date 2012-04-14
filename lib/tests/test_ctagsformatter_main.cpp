#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/ctagscollector.h"
#include "srchilite/ctagsformatter.h"
#include "srchilite/formatterparams.h"
#include "srchilite/tostringcollection.h"

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
    CTagsCollector collectorInline("mytags", INLINE);
    CTagsFormatterResults results;

    string sourceFile = string(BASEDIR) + "readtags.h";

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
    PreFormatter preformatter;
    CTagsFormatter formatter(&preformatter, textStyles.refstyle,
            &collectorInline);
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

    results.clear();
    collectorInline.setRefPosition(POSTDOC);
    fileInfo.line = 1;
    formatter.formatCTags("READTAGS_H", results, &fileInfo);
    printResults(results);
    // this should be postdoc
    assertEquals("<PD>READTAGS_H - readtags.html - " + sourceFile
            + "(readtags.h):22<PD>\n", collectionRefToString(results.postDocResult, 0));

    cout << "test_ctagsformatter: SUCCESS!" << endl;

    return 0;
}
