//
// C++ Implementation: langelemsprinter
//
// Description: 
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "langelemsprinter.H"

#include "statelangelem.h"
#include "langelems.h"

#include <iostream>

using namespace std;

LangElemsPrinter::LangElemsPrinter()
{
}


LangElemsPrinter::~LangElemsPrinter()
{
}

void LangElemsPrinter::print(const LangElems *elems)
{
    if (!elems)
        return;
    
    collect_DB(elems);

    for (SetOfElements::const_iterator it = setOfElements.begin();
         it != setOfElements.end(); ++it)
        cout << *it << endl;
}

void LangElemsPrinter::collect(const LangElems *elems)
{
    if (elems)
        for (LangElems::const_iterator it = elems->begin(); it != elems->end(); ++it)
            collect_DB(*it);
}

void LangElemsPrinter::collect(const StateLangElem *elem)
{
    setOfElements.insert(elem->getName());

    const LangElems *elems = elem->getElems();
    if (elems)
        collect_DB (elems);
}

void LangElemsPrinter::collect(const LangElem *elem)
{
    setOfElements.insert(elem->getName());
}
