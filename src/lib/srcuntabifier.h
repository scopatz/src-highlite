//****************************************************************************//
//      Untabifier class:
//
//      Derived Pretranslator to convert tabs to spaces before HTML generation
//
//      Don Stauffer Revision: June 2003
//      Lorenzo Bettini Revision: November 2004, mostly completely rewritten
//****************************************************************************//
#ifndef	srcUntabifier_H
#define	srcUntabifier_H

#include "preformatter.h"

using std::string;

class Untabifier : public PreFormatter
{
 public:

  Untabifier (int nSpacesPerTab, PreFormatterPtr f = PreFormatterPtr()) :
    PreFormatter(f), nSpacesPerTab_ (nSpacesPerTab), n_ (0)
    {
    }

  virtual const string doPreformat( const std::string &text );

 private:

  const int nSpacesPerTab_;
  int n_;
};

#endif //      #ifndef srcUntabifier_H
