//
// C++ Interface: delimitedlangelem
//
// Description: 
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef DELIMITEDLANGELEM_H
#define DELIMITEDLANGELEM_H

#include "statestartlangelem.h"

class StringDef;

/**
represent a language element that is delimited by strings

@author Lorenzo Bettini
*/
// doublecpp: forward declarations, DO NOT MODIFY
class RegExpStateBuilder; // file: regexpstatebuilder.h
class RegExpStatePointer; // file: regexpstatebuilder.h
// doublecpp: end, DO NOT MODIFY

class DelimitedLangElem : public StateStartLangElem
{
  private:
    StringDef *start;
    StringDef *end;
    StringDef *escape;
    bool multiline;
    bool nested;

public:
    DelimitedLangElem(const std::string &n, StringDef *s, StringDef *e, StringDef *es, bool multi, bool nes);

    ~DelimitedLangElem();
    
    virtual const std::string toString() const;
    
    virtual const std::string toStringOriginal() const;
    
    void set_escape(StringDef *e) { escape = e; }
    
    StringDef *getStart() const { return start; }
    StringDef *getEnd() const { return end; }
    StringDef *getEscape() const { return escape; }
    bool isMultiline() const { return multiline; }
    bool isNested() const { return nested; }    
// doublecpp: dispatch methods, DO NOT MODIFY
public:
virtual void dispatch_build(RegExpStateBuilder *, RegExpStatePointer state);
// doublecpp: end, DO NOT MODIFY
};

#endif
