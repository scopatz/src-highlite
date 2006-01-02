//
// C++ Interface: regexpstateprinter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPSTATEPRINTER_H
#define REGEXPSTATEPRINTER_H

#include <set>

#include "regexpstate.h"

typedef std::set<int> StateIdSet;

/**
Print a RegExpState object (including all the subobjects)

@author Lorenzo Bettini
*/
class RegExpStatePrinter
{
  private:
    int indent;
    StateIdSet stateidset; // to avoid infinite loops

public:
    RegExpStatePrinter();

    ~RegExpStatePrinter();

    void printRegExpState(RegExpStatePtr state);
    void printRegExpFormatter(RegExpFormatterPtr formatter);
};

#endif
