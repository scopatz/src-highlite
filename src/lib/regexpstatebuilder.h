//
// C++ Interface: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPSTATEBUILDER_H
#define REGEXPSTATEBUILDER_H

#include <regexpstate.h>
#include <list>

class RegExpStatePointer {
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
    branches build
    void (StateLangElem *elem, RegExpStatePointer state);
    void (StringListLangElem *elem, RegExpStatePointer state);
    void (DelimitedLangElem *elem, RegExpStatePointer state);
    void (StateStartLangElem *elem, RegExpStatePointer state);
    void (LangElem *elem, RegExpStatePointer state);
    void (LangElems *elems, RegExpStatePointer state);
    endbranches

  public:
    RegExpStateBuilder();

    virtual ~RegExpStateBuilder();

    RegExpStatePtr build(LangElems *elems);
};

#endif
