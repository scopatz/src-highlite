//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef	SRCUNTABIFIER_H
#define	SRCUNTABIFIER_H

#include "preformatter.h"

using std::string;

/**
 * PerFormratter to convert tabs to spaces before generation
 * 
 * @author Don Stauffer Revision: June 2003
 * Lorenzo Bettini Revision: November 2004, mostly completely rewritten
 */
class Untabifier : public PreFormatter {
public:

    Untabifier(unsigned int nSpacesPerTab, PreFormatterPtr f = PreFormatterPtr()) :
        PreFormatter(f), nSpacesPerTab_(nSpacesPerTab), n_(0) {
    }

    virtual const string doPreformat(const std::string &text);
    
private:

    /// the number of spaces corresponding to a tab char
    const int nSpacesPerTab_;

    /// the counter of characters
    unsigned int n_;
};

#endif // SRCUNTABIFIER_H
