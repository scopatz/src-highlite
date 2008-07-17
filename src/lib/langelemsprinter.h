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
#include <ostream>

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
     * to the specified ostream.
     * @param elems
     * @param os
     */
    void print(const LangElems *elems, std::ostream &os);

protected:
    branches collect
    void (const StateLangElem *elem);
    void (const LangElem *elem);
    void (const LangElems *elem);
    void (const NamedSubExpsLangElem *elem);
    endbranches
};

#endif
