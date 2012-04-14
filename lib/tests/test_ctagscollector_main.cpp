#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/ctagscollector.h"
#include "srchilite/fileutil.h"
#include "srchilite/formatterparams.h"
#include "srchilite/tostringcollection.h"

using namespace std;
using namespace srchilite;

static void printCTagsInfo(const CTagsInfos &infos);
static void expectAnchor(const CTagsInfos &infos, const string &filename,
        const string &line);
static void expectReference(const CTagsInfos &infos, const string &filename,
        const string &line, RefPosition refpos);

namespace srchilite {

static ostream &operator <<(ostream &os, const CTagsInfo &);

ostream &operator <<(ostream &os, const srchilite::CTagsInfo &info) {
    os << (info.isAnchor ? "ANCHOR: " : "REF: ") << ", filename: "
            << strip_file_path(info.fileName) << ", line: " << info.lineNumber
            << ", refposition: " << info.refposition;

    return os;
}
}

void printCTagsInfo(const srchilite::CTagsInfos &infos) {
    cout << "tags infos: " << collectionToString(&infos, '\n') << endl;
}

void expectAnchor(const CTagsInfos &infos, const string &filename,
        const string &line) {
    // only one element for anchors
    assertTrue(infos.size() == 1);

    CTagsInfo info = infos.front();

    assertTrue(info.isAnchor);
    assertEquals(filename, info.fileName);
    assertEquals(line, info.lineNumber);
    assertEquals(NONE, info.refposition);
}

void expectReference(const CTagsInfos &infos, const string &filename,
        const string &line, RefPosition refpos) {
    assertTrue(infos.size() > 0);

    for (CTagsInfos::const_iterator it = infos.begin(); it != infos.end(); ++it) {
        CTagsInfo info = *it;
        if (info.fileName == filename && info.lineNumber == line) {
            assertFalse(info.isAnchor);
            assertEquals(refpos, info.refposition);
            return;
        }
    }

    cout << "reference not found" << endl;

    // if we're here we didn't find it, then fail
    assertTrue(false);
}

int main() {
    CTagsCollector collectorInline("mytags", INLINE);
    CTagsInfos infos;
    string sourceFile = BASEDIR;

    sourceFile += "readtags.h";

    // test tags found in file readtags.h
    FormatterParams fileInfo(sourceFile);
    fileInfo.filename = sourceFile;
    fileInfo.line = 1;

    infos.clear();
    collectorInline.collectTags("READTAGS_H", infos, &fileInfo);
    printCTagsInfo(infos);
    // this should be a reference inline
    expectReference(infos, sourceFile, "22", INLINE);

    infos.clear();
    fileInfo.line = 22;
    // this must be detected as an anchor, since the line number is the same
    collectorInline.collectTags("READTAGS_H", infos, &fileInfo);
    printCTagsInfo(infos);
    expectAnchor(infos, sourceFile, "22");

    infos.clear();
    collectorInline.collectTags("file", infos, &fileInfo);
    printCTagsInfo(infos);
    // there should be two references
    expectReference(infos, sourceFile, "72", POSTLINE);
    expectReference(infos, sourceFile, "112", POSTLINE);

    infos.clear();
    collectorInline.setRefPosition(POSTDOC);
    fileInfo.line = 1;
    collectorInline.collectTags("READTAGS_H", infos, &fileInfo);
    printCTagsInfo(infos);
    // this should be a reference postdoc
    expectReference(infos, sourceFile, "22", POSTDOC);

    infos.clear();
    collectorInline.setRefPosition(POSTLINE);
    collectorInline.collectTags("READTAGS_H", infos, &fileInfo);
    printCTagsInfo(infos);
    // this should be a reference postline even if single
    expectReference(infos, sourceFile, "22", POSTLINE);

    cout << "test_ctagscollector: SUCCESS!" << endl;

    return 0;
}
