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
#ifndef LANGELEM_H
#define LANGELEM_H

#include "parserinfo.h"

/**
represent a language element

@author Lorenzo Bettini
*/
// doublecpp: forward declarations, DO NOT MODIFY
class LangElemsPrinter; // file: langelemsprinter.h
class RegExpStateBuilder; // file: regexpstatebuilder.h
class RegExpStatePointer; // file: regexpstatebuilder.h
// doublecpp: end, DO NOT MODIFY

class LangElem : public ParserInfo
{
  private:
    const std::string name;
    bool redef; // whether this redefs an existing language element
    bool subst; // whether this substitutes an existing language element

public:
  LangElem(const std::string &n) : name(n), redef(false), subst(false) {}

  virtual ~LangElem() {}

  const std::string getName() const { return name; }
  virtual const std::string toString() const { return name; }

  /**
   * return the original string representation of this element;
   * this must be defined by subclasses
   */
  virtual const std::string toStringOriginal() const = 0;
  
  bool isRedef() const { return redef; }
  void setRedef() { redef = true; }
  bool isSubst() const { return subst; }
  void setSubst() { subst = true; }

// doublecpp: dispatch methods, DO NOT MODIFY
public:
virtual void dispatch_build(RegExpStateBuilder *, RegExpStatePointer state);
virtual void dispatch_collect_const(LangElemsPrinter *);
// doublecpp: end, DO NOT MODIFY
};

#endif
