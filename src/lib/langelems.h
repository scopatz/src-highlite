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
#ifndef LANGELEMS_H
#define LANGELEMS_H

#include "langelem.h"

#include <list>
#include <map>
#include <string>

using std::list;
using std::map;
using std::string;

typedef list<LangElem *> LangElemsBase;

/**
collection of LangElem

@author Lorenzo Bettini
*/
// doublecpp: forward declarations, DO NOT MODIFY
class LangElemsPrinter; // file: langelemsprinter.h
class RegExpStateBuilder; // file: regexpstatebuilder.h
class RegExpStatePointer; // file: regexpstatebuilder.h
// doublecpp: end, DO NOT MODIFY

class LangElems : protected list<LangElem *>
{
  typedef list<LangElem *> base;
  typedef base::iterator Pointer;
  typedef list<Pointer> PointerList;
  typedef map<string, PointerList> ElemMap;
  
  ElemMap elem_map;
  
  public:
    using base::const_iterator;
    using base::begin;
    using base::end;
    using base::size;
    
    LangElems();

    virtual ~LangElems();
    
    void add(LangElem *el);
    void redef(LangElem *el);
    void subst(LangElem *el);
    
    const std::string toString() const;
    const std::string toStringOriginal() const;
// doublecpp: dispatch methods, DO NOT MODIFY
public:
virtual void dispatch_build(RegExpStateBuilder *, RegExpStatePointer state);
virtual void dispatch_collect_const(LangElemsPrinter *);
// doublecpp: end, DO NOT MODIFY
};

#endif
