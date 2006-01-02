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
class PreFormatter
{
  PreFormatterPtr decorator;

  public:
    PreFormatter(PreFormatterPtr f = PreFormatterPtr());

    virtual ~PreFormatter();

    void setFormatter(PreFormatterPtr f);

    const std::string preformat(const std::string &text);

  protected:
    // to be redefined in the derived classes: actually perform preformatting
    virtual const std::string doPreformat(const std::string &text);

};

#endif
