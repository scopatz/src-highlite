//
// C++ Implementation: %{MODULE}
//
// Description:
//
//
// Author: %{AUTHOR} <%{EMAIL}>, (C) %{YEAR}
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "langelem.h"

using namespace std;

LangElem::LangElem(const string &n) : name(n), redef(false), subst(false)
{
}


LangElem::~LangElem()
{
}

const std::string 
LangElem::toString() const
{
  return name;
}

