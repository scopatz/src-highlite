//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ctagscollector.h"
#include "formatterparams.h"
#include <sstream>
#include "ioexception.h"

using namespace std;

namespace srchilite {

/**
 * internal struct to store information about references
 */
struct RefEntry {
    string filename;
    unsigned long linenumber;
};

CTagsCollector::CTagsCollector(const std::string &ctags_file_name,
        RefPosition pos) :
    refposition(pos) {
    ctags_file = tagsOpen(ctags_file_name.c_str(), &info);
    if (ctags_file == 0) {
        throw IOException("cannot open tag file", ctags_file_name);
    }
}

CTagsCollector::~CTagsCollector() {
    if (ctags_file)
        tagsClose(ctags_file);
}

bool CTagsCollector::collectTags(const std::string &word, CTagsInfos &infos,
        const FormatterParams *fileinfo) {
    tagEntry entry;
    bool found = false; // whether we found a tag
    bool found_anchor = false; // whether we found an anchor
    string output;
    typedef list<RefEntry> FoundRefList;
    FoundRefList foundreflist;

    if (tagsFind(ctags_file, &entry, word.c_str(), TAG_FULLMATCH)== TagSuccess) {
        found = true;
        do {
            RefEntry refentry;
            refentry.filename = entry.file;

            if ((refentry.filename == fileinfo->filename ||
                    refentry.filename == fileinfo->fileNameNoPath) && entry.address.lineNumber
                    == fileinfo->line) {
                ostringstream gen_info;
                // we just found an entry to this very element (same file and same lineno)
                // so it will be an anchor
                gen_info << entry.address.lineNumber;

                CTagsInfo ctagsInfo(refentry.filename, gen_info.str(), NONE, true);
                infos.push_back(ctagsInfo);

                found_anchor = true;
                break;
            }

            refentry.linenumber = entry.address.lineNumber;
            foundreflist.push_back(refentry);
        } while (tagsFindNext(ctags_file, &entry)== TagSuccess);
    }

    if (found && !found_anchor) {
        RefPosition refpos;

        // in case there's more than one reference we switch to POSTLINE
        if (foundreflist.size()>1 && refposition == INLINE) {
            refpos = POSTLINE;
        } else {
            refpos = refposition;
        }

        for (FoundRefList::const_iterator it = foundreflist.begin(); it
                != foundreflist.end(); ++it) {
            ostringstream gen_info;

            gen_info << it->linenumber;

            CTagsInfo ctagsInfo(it->filename, gen_info.str(), refpos, false);
            infos.push_back(ctagsInfo);
        }
    }

    return found || found_anchor;
}

}
