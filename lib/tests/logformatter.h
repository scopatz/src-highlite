//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef LOGFORMATTER_H_
#define LOGFORMATTER_H_

#include <deque>
#include <algorithm>
#include <iostream>

#include "srchilite/formatter.h"

using namespace srchilite;

struct FormatterLogEntry {
    /// the element name
    const std::string first;

    /// the string to format
    const std::string second;

    /// the start of the string in the paragraph
    const int start;

    FormatterLogEntry(const std::string &f, const std::string &s, const int i) :
        first(f), second(s), start(i) {
    }
};

typedef std::deque<FormatterLogEntry> FormatterLog;

/**
 * A simple Formatter implementation that logs the strings to format into
 * a collection (each element is a pair: <element, string>
 */
struct LogFormatter: public Formatter {
    /// the log (shared with other formatters)
    FormatterLog &log;

    /// the element represented by this formatter
    const std::string elem;

    LogFormatter(FormatterLog &_log, const std::string &_elem);
    virtual ~LogFormatter();

    /**
     * Append to the log the information about the passed string
     */
    virtual void format(const std::string &s, const FormatterParams *params);
};

std::ostream& operator<<(std::ostream& os, const FormatterLogEntry &entry);

void showLog(FormatterLog &log);

#endif /*LOGFORMATTER_H_*/
