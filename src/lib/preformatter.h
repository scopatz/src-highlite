//
// C++ Interface: preformatter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PREFORMATTER_H
#define PREFORMATTER_H

#include <string>
#include <boost/shared_ptr.hpp>

class PreFormatter;
typedef boost::shared_ptr<PreFormatter> PreFormatterPtr;

/**
 preformat text to be generated

 @author Lorenzo Bettini
 */
class PreFormatter {
    /// the possible nested preformatter (Decorator pattern)
    PreFormatterPtr decorator;

public:
    PreFormatter(PreFormatterPtr f = PreFormatterPtr());

    virtual ~PreFormatter();

    void setFormatter(PreFormatterPtr f);

    /**
     * Preformats the passed string (public version)
     * @param text the string to be preformatted
     * @return the preformatted string
     */
    const std::string preformat(const std::string &text);

protected:
    /**
     * Preformats the passed string (protected version).  The subclasses must
     * redefine this method to perform the preformatting.  The default implementation
     * does not perform any preformatting.
     * @param text the string to be preformatted
     * @return the preformatted string
     */
    virtual const std::string doPreformat(const std::string &text);

};

#endif
