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
    branches collect
    void (const StateLangElem *elem);
    void (const LangElem *elem);
    void (const LangElems *elem);
    endbranches
};

#endif
