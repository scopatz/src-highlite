//
// C++ Implementation: preformatter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "preformatter.h"

using namespace std;

PreFormatter::PreFormatter(PreFormatterPtr f) :
    decorator(f)
{
}

PreFormatter::~PreFormatter()
{
}

void
PreFormatter::setFormatter(PreFormatterPtr f)
{
  if (decorator.get())
    decorator->setFormatter(f);
  else
    decorator = f;
}

const string
PreFormatter::preformat(const string &text)
{
  if (! text.size())
    return text;

  string preformat_text = text;
  PreFormatter *inner = this;
  while (inner) // start the chain of preformatting
  {
    preformat_text = inner->doPreformat(preformat_text);
    inner = inner->decorator.get();
  }

  return preformat_text;
}

const string
PreFormatter::doPreformat(const string &text)
{
  return text;
}


