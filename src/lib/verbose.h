//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef VERBOSE_H_
#define VERBOSE_H_

#include <iostream>

/**
 * A utility class that can be used as the base class for classes
 * that can be verbose.  These classes can then use the macros
 * VERBOSE and VERBOSELN to print messages in case they are set as verbose
 */
struct Verbose {
    bool verbose;

    Verbose(bool _verbose = false) :
        verbose(_verbose) {
    }
    
    void setVerbose(bool v = true) {
        verbose = v;
    }
};

/**
 * A macro that assumes the presence of a variable "verbose" in the context
 * and if true prints the passed string to the stderr.
 * This is an optimization in the sense that the string is not even
 * created if verbose is false
 */
#define VERBOSE(s) if (verbose) std::cerr << s;
#define VERBOSELN(s) if (verbose) std::cerr << s << std::endl;

#endif /*VERBOSE_H_*/
