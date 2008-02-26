//
// C++ Interface: langelemsprinter
//
// Description: 
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LANGELEMSPRINTER_H
#define LANGELEMSPRINTER_H

#include <set>
#include <string>

/**
Prints all the language elements

	@author Lorenzo Bettini <http://www.lorenzobettini.it>
*/
// doublecpp: forward declarations, DO NOT MODIFY
class LangElem; // file: langelem.h
class LangElems; // file: langelems.h
class StateLangElem; // file: statelangelem.h
// doublecpp: end, DO NOT MODIFY

#line 23 "langelemsprinter.h"
class LangElemsPrinter
{
    typedef std::set<std::string> SetOfElements;
    SetOfElements setOfElements;
    
public:
    LangElemsPrinter();

    virtual ~LangElemsPrinter();

    /**
     * Prints all the elements contained in the passed LangElems
     * to the standard output.
     */
    void print(const LangElems *elems);

protected:
// doublecpp: method branches, DO NOT MODIFY
#line 41 "langelemsprinter.h"
virtual void collect(const StateLangElem * elem);
#line 42 "langelemsprinter.h"
virtual void collect(const LangElem * elem);
#line 43 "langelemsprinter.h"
virtual void collect(const LangElems * elem);
public:
void _forward_collect(const LangElem * elem)
{
  collect(elem);
};

void _forward_collect(const LangElems * elem)
{
  collect(elem);
};

void _forward_collect(const StateLangElem * elem)
{
  collect(elem);
};

protected:
virtual void collect_DB(const LangElem * elem);
virtual void collect_DB(const LangElems * elem);
#line 43 "langelemsprinter.h"
// doublecpp: end, DO NOT MODIFY

};

#endif
