//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#include "logformatter.h"

using namespace std;

LogFormatter::LogFormatter(FormatterLog &_log, const std::string &_elem) :
    log(_log), elem(_elem) {
}

LogFormatter::~LogFormatter() {
}

void LogFormatter::format(const std::string &s, const FormatterParams *params) {
    log.push_back(std::make_pair(elem, s));
}

ostream& operator<<(ostream& os, const FormatterLogEntry &entry) {
    os << entry.first << ": \"" << entry.second << "\"";
    return os;
}

void showLog(FormatterLog &log) {
    for (FormatterLog::const_iterator it = log.begin(); it != log.end(); ++it)
        cout << *it << endl;
}

