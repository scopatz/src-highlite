//
// C++ Interface: statestartlangelem
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STATESTARTLANGELEM_H
#define STATESTARTLANGELEM_H

#include "langelem.h"

class StringDef;
class StateLangElem;

/**
A language element that may start a new state/environment

@author Lorenzo Bettini
*/
// doublecpp: forward declarations, DO NOT MODIFY
class RegExpStateBuilder; // file: regexpstatebuilder.h
class RegExpStatePointer; // file: regexpstatebuilder.h
// doublecpp: end, DO NOT MODIFY

class StateStartLangElem : public LangElem
{
  private:
    bool exit;
    bool exit_all;
    StateLangElem *statelangelem; // the possible State of which we
    // represent the start.

public:
    StateStartLangElem(const std::string &n, bool exit = false, bool all = false);

    virtual ~StateStartLangElem();

    virtual const std::string toString() const;

    void set_exit() { exit = true; }
    void set_exitall() { exit_all = true; }

    bool exitAll() const { return exit_all; }
    bool doExit() const { return exit; }

    StateLangElem *getStateLangElem() const { return statelangelem; }
    void setStateLangElem(StateLangElem *s) { statelangelem = s; }
// doublecpp: dispatch methods, DO NOT MODIFY
public:
virtual void dispatch_build(RegExpStateBuilder *, RegExpStatePointer state);
// doublecpp: end, DO NOT MODIFY
};

#endif
