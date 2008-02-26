//
// C++ Interface: RegExpStateBuilder
//
// Description: Builds the RegExpStates starting from all the language elements.
// 
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPSTATEBUILDER_H
#define REGEXPSTATEBUILDER_H

#include <regexpstate.h>
#include <list>

#line 18 "regexpstatebuilder.h"
class RegExpStatePointer
{
  public:
    RegExpStatePtr regExpStatePtr;
    RegExpStatePointer(RegExpStatePtr r) : regExpStatePtr(r) {}
    operator RegExpStatePtr() const { return regExpStatePtr; }
    RegExpStatePtr::element_type * operator->() const { return regExpStatePtr.operator->(); }
};

/**
build a RegExpState starting from language definitions

@author Lorenzo Bettini
*/
// doublecpp: forward declarations, DO NOT MODIFY
class DelimitedLangElem; // file: delimitedlangelem.h
class LangElem; // file: langelem.h
class LangElems; // file: langelems.h
class NamedSubExpsLangElem; // file: namedsubexpslangelem.h
class RegExpStatePointer; // file: regexpstatebuilder.h
class StateLangElem; // file: statelangelem.h
class StateStartLangElem; // file: statestartlangelem.h
class StringListLangElem; // file: stringlistlangelem.h
// doublecpp: end, DO NOT MODIFY

#line 31 "regexpstatebuilder.h"
class RegExpStateBuilder
{
  private:
    /*
      FIXME
      This is a trick to make shared_ptr to nested states and formatters
      still reachable.
    */
    typedef std::list<RegExpFormatterPtr> RegExpFormatterList;
    RegExpFormatterList nested_formatters;
    typedef std::list<RegExpStatePtr> RegExpStateList;
    RegExpStateList nested_states;
    
  protected:
    // the following will be processed by doublecpp
// doublecpp: method branches, DO NOT MODIFY
#line 47 "regexpstatebuilder.h"
virtual void build(StateLangElem * elem, RegExpStatePointer state);
#line 48 "regexpstatebuilder.h"
virtual void build(StringListLangElem * elem, RegExpStatePointer state);
#line 49 "regexpstatebuilder.h"
virtual void build(DelimitedLangElem * elem, RegExpStatePointer state);
#line 50 "regexpstatebuilder.h"
virtual void build(StateStartLangElem * elem, RegExpStatePointer state);
#line 51 "regexpstatebuilder.h"
virtual void build(NamedSubExpsLangElem * elem, RegExpStatePointer state);
#line 52 "regexpstatebuilder.h"
virtual void build(LangElem * elem, RegExpStatePointer state);
#line 53 "regexpstatebuilder.h"
virtual void build(LangElems * elems, RegExpStatePointer state);
public:
void _forward_build(DelimitedLangElem * elem, RegExpStatePointer state)
{
  build(elem, state);
};

void _forward_build(LangElem * elem, RegExpStatePointer state)
{
  build(elem, state);
};

void _forward_build(LangElems * elems, RegExpStatePointer state)
{
  build(elems, state);
};

void _forward_build(NamedSubExpsLangElem * elem, RegExpStatePointer state)
{
  build(elem, state);
};

void _forward_build(StateLangElem * elem, RegExpStatePointer state)
{
  build(elem, state);
};

void _forward_build(StateStartLangElem * elem, RegExpStatePointer state)
{
  build(elem, state);
};

void _forward_build(StringListLangElem * elem, RegExpStatePointer state)
{
  build(elem, state);
};

protected:
virtual void build_DB(LangElem * elem, RegExpStatePointer state);
virtual void build_DB(LangElems * elems, RegExpStatePointer state);
#line 53 "regexpstatebuilder.h"
// doublecpp: end, DO NOT MODIFY


  public:
    RegExpStateBuilder();

    virtual ~RegExpStateBuilder();

    RegExpStatePtr build(LangElems *elems);
};

#endif
