//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logformatter.h"
#include "srchilite/formatterparams.h"

using namespace std;
using namespace srchilite;

LogFormatter::LogFormatter(FormatterLog &_log, const std::string &_elem) :
    log(_log), elem(_elem) {
}

LogFormatter::~LogFormatter() {
}

void LogFormatter::format(const std::string &s, const FormatterParams *params) {
    log.push_back(FormatterLogEntry(elem, s, (params ? params->start : -2)));
}

ostream& operator<<(ostream& os, const FormatterLogEntry &entry) {
    os << entry.first << ": \"" << entry.second << "\"" << ", start: " << entry.start;
    return os;
}

void showLog(FormatterLog &log) {
    for (FormatterLog::const_iterator it = log.begin(); it != log.end(); ++it)
        cout << *it << endl;
}

