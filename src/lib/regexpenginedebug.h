//
// C++ Interface: regexpenginedebug
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPENGINEDEBUG_H
#define REGEXPENGINEDEBUG_H

#include <regexpengine.h>

/**
Generate Debug information while scanning a source file with regular expressions.
A specialization of RegExpEngine

@author Lorenzo Bettini
*/
class RegExpEngineDebug : public RegExpEngine
{
public:
    RegExpEngineDebug(RegExpStatePtr v, TextFormatter* pre, FileInfo *f);

    ~RegExpEngineDebug();

    void setInteractive(bool i) { interactive = i; }
protected:
  /// whether it's an interactive debug session
  bool interactive;

    virtual void enterState(RegExpStatePtr state, int index);
    virtual void exitAll();
    virtual void exitState(int level);
    virtual void format(int index, RegExpStatePtr state, const std::string& s);

    /**
     * Waits for a step command (if in interactive mode)
     */
    virtual void step();
};

#endif
