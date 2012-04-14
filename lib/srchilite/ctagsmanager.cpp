//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>

#include "ctagsmanager.h"
#include "ctagscollector.h"
#include "ioexception.h"
#include "ctagscollector.h"
#include "ctagsformatter.h"
#include "verbosity.h"

using namespace std;

namespace srchilite {

CTagsManager::CTagsManager(const std::string &_ctagsFile,
        const std::string &_ctagsCmd, bool _runCTags, RefPosition _refPosition) :
    ctagsFile(_ctagsFile), ctagsCmd(_ctagsCmd), runCTags(_runCTags),
            refPosition(_refPosition), ctagsCollector(0) {
}

CTagsManager::~CTagsManager() {
    if (ctagsCollector)
        delete ctagsCollector;
}

void CTagsManager::runCTagsCmd() {
    VERBOSELN("Running ctags: " + ctagsCmd);

    int res = system(ctagsCmd.c_str());

    if (res != 0) {
        throw IOException("error running ctags command", ctagsCmd);
    }

    // so that the ctags command is run only once
    runCTags = false;
}

CTagsFormatter *CTagsManager::createCTagsFormatter(const TextStyles::RefTextStyle &r) {
    if (runCTags)
        runCTagsCmd();

    // the CTagsCollector will be shared by all the created CTagsFormatters
    if (!ctagsCollector)
        ctagsCollector = new CTagsCollector(ctagsFile, refPosition);

    // the preformatter is set to 0 in the CTagsFormatter: it must be
    // set externally
    return new CTagsFormatter(0, r, ctagsCollector);
}

}
