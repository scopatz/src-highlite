#include "stringlistlangelem.h"

#include "statestartlangelem.h"

#include "statelangelem.h"

#include "namedsubexpslangelem.h"

#include "delimitedlangelem.h"

#include "langelems.h"

#include "langelem.h"

#include "regexpstatebuilder.H"

void
RegExpStateBuilder::build_DB(LangElem * elem, RegExpStatePointer state)
{
  elem->dispatch_build(this, state);
}

void
RegExpStateBuilder::build_DB(LangElems * elems, RegExpStatePointer state)
{
  elems->dispatch_build(this, state);
}

void
DelimitedLangElem::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

void
LangElem::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

void
LangElems::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

void
NamedSubExpsLangElem::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

void
StateLangElem::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

void
StateStartLangElem::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

void
StringListLangElem::dispatch_build(RegExpStateBuilder *RegExpStateBuilder_o, RegExpStatePointer state)
{
  RegExpStateBuilder_o->_forward_build(this, state);
}

