//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef HIGHLIGHTSTATEBUILDER_H_
#define HIGHLIGHTSTATEBUILDER_H_

#include "highlightstate.h"

class LangElems;
class HighlightRuleFactory;

/**
 * Builds an HighlightState from the language definition file collected structures
 */
// doublecpp: forward declarations, DO NOT MODIFY
class DelimitedLangElem; // file: delimitedlangelem.h
class HighlightState; // file: highlightstate.h
class LangElem; // file: langelem.h
class NamedSubExpsLangElem; // file: namedsubexpslangelem.h
class StateLangElem; // file: statelangelem.h
class StringListLangElem; // file: stringlistlangelem.h
// doublecpp: end, DO NOT MODIFY

#line 18 "highlightstatebuilder.h"
class HighlightStateBuilder
{
    /// the factory for creating rules
    HighlightRuleFactory *highlightRuleFactory;
public:
    HighlightStateBuilder(HighlightRuleFactory *_highlightRuleFactory);
    virtual ~HighlightStateBuilder();

    /**
     * Builds all the rules into the passed mainState as specified in the
     * passed LangElems
     * 
     * @param elems the element definitions retrieved from the lang file
     * @param mainState the main state where to store all the rules
     */
    void build(LangElems *elems, HighlightStatePtr mainState);
    
    // the following will be processed by doublecpp
// doublecpp: method branches, DO NOT MODIFY
#line 36 "highlightstatebuilder.h"
virtual void build(LangElem * elem, HighlightState * state);
#line 37 "highlightstatebuilder.h"
virtual void build(StringListLangElem * elem, HighlightState * state);
#line 38 "highlightstatebuilder.h"
virtual void build(DelimitedLangElem * elem, HighlightState * state);
#line 39 "highlightstatebuilder.h"
virtual void build(NamedSubExpsLangElem * elem, HighlightState * state);
#line 40 "highlightstatebuilder.h"
virtual void build(StateLangElem * elem, HighlightState * state);
virtual void build_DB(LangElem * elem, HighlightState * state);
#line 40 "highlightstatebuilder.h"
// doublecpp: end, DO NOT MODIFY

};

#endif /*HIGHLIGHTSTATEBUILDER_H_*/
