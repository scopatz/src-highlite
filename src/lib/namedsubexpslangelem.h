//
// C++ Interface: NamedSubExpsLangElem
//
// Description: represents a regular expression made by many marked groups
// and each marked group represents a different language element
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef NAMEDSUBEXPSLANGELEM_H_
#define NAMEDSUBEXPSLANGELEM_H_

#include "statestartlangelem.h"

#include <list>

class StringDef;

typedef std::list<std::string> ElementNames;

// doublecpp: forward declarations, DO NOT MODIFY
class RegExpStateBuilder; // file: regexpstatebuilder.h
class RegExpStatePointer; // file: regexpstatebuilder.h
// doublecpp: end, DO NOT MODIFY

class NamedSubExpsLangElem : public StateStartLangElem
{
    const ElementNames *elementNames;
    StringDef *regexpDef;
public:
	NamedSubExpsLangElem(const ElementNames *names, StringDef *def, bool exit = false, bool all = false);
	virtual ~NamedSubExpsLangElem();
	
    virtual const std::string toString() const;
    
    virtual const std::string toStringOriginal() const;
    
    const ElementNames *getElementNames() const { return elementNames; }
    const StringDef *getRegexpDef() const { return regexpDef; }

// doublecpp: dispatch methods, DO NOT MODIFY
public:
virtual void dispatch_build(RegExpStateBuilder *, RegExpStatePointer state);
// doublecpp: end, DO NOT MODIFY
};

#endif /*NAMEDSUBEXPSLANGELEM_H_*/
