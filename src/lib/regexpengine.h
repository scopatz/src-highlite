//
// C++ Interface: regexpengine
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef REGEXPENGINE_H
#define REGEXPENGINE_H

#include "regexpstate.h"

class TextFormatter;

#include <string>
#include <stack>
#include <boost/shared_ptr.hpp>
#include "fileinfo.h"

/**
 the class that actually performs regular expression processing

 @author Lorenzo Bettini
 */
class RegExpEngine {
protected:
    RegExpStatePtr currentstate, initial_state;
    FileInfo *fileinfo;

private:
    TextFormatter *formatter;
    typedef std::stack<RegExpStatePtr> stack_of_states;
    stack_of_states states_stack;
    
    typedef std::stack<boost::smatch> stack_of_matches;
    /**
     * Each element provides the replacement values for back references in regular
     * expressions of the shape @{digit}
     */
    stack_of_matches reference_env;

protected:
    virtual void enterState(RegExpStatePtr state, int index);
    virtual void exitState(int level);
    virtual void exitAll();
    virtual void format(int index, RegExpStatePtr state, const std::string &s);

public:
    RegExpEngine(RegExpStatePtr v, TextFormatter *pre, FileInfo *f) :
        currentstate(v), fileinfo(f), formatter(pre) {
    }

    virtual ~RegExpEngine();

    void process_file(const char *file);
};

typedef boost::shared_ptr<RegExpEngine> RegExpEnginePtr;

#endif
