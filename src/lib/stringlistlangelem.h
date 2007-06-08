//
// C++ Interface: stringlistlangelem
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STRINGLISTLANGELEM_H
#define STRINGLISTLANGELEM_H

#include "statestartlangelem.h"

class StringDefs;

/**
a language element made of a list of strings

@author Lorenzo Bettini
*/
// doublecpp: forward declarations, DO NOT MODIFY
class RegExpStateBuilder; // file: regexpstatebuilder.h
class RegExpStatePointer; // file: regexpstatebuilder.h
// doublecpp: end, DO NOT MODIFY

class StringListLangElem : public StateStartLangElem
{
private:
    StringDefs *alternatives;
    bool nonsensitive;

public:
    StringListLangElem(const std::string &n, StringDefs *defs, bool nons);

    virtual ~StringListLangElem();

    virtual const std::string toString() const;
    
    virtual const std::string toStringOriginal() const;

    StringDefs *getAlternatives() const { return alternatives; }
    bool isCaseSensitive() const { return !nonsensitive; }
// doublecpp: dispatch methods, DO NOT MODIFY
public:
virtual void dispatch_build(RegExpStateBuilder *, RegExpStatePointer state);
// doublecpp: end, DO NOT MODIFY
};

#endif
