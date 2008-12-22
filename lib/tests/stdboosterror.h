#ifndef STDBOOSTERROR_H_
#define STDBOOSTERROR_H_

#include <boost/regex/pattern_except.hpp>

static boost::regex_error
        std_boost_exception(boost::regex_error(boost::regex_constants::error_bad_pattern));

/**
 * returns the string representing a standard exception (which
 * can be different from system to system)
 */
const std::string stdBoostExceptionToString() {
    return std_boost_exception.what();
}

const std::string stdBoostCausedBy(const std::string &filename = "",
        const std::string &line = "") {
    return (filename.size() ? filename + ":" + line + ": " : "") + "Caused by: "
            + stdBoostExceptionToString();
}

#endif /*STDBOOSTERROR_H_*/
