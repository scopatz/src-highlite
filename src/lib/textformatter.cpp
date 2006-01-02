//
// C++ Implementation: textformatter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "textformatter.h"

#include "maingeneratormap.h"

using namespace std;

TextFormatter::TextFormatter()
{
}

TextFormatter::~TextFormatter()
{
}

void
TextFormatter::format(const string &elem, const string &text, const FileInfo *p)
{
  if (! text.size())
    return;

  generatormap->generateEntire(elem, text, p);
}

void
TextFormatter::format_nl(const string &text)
{
  generatormap->generateNL(text);
}

void
TextFormatter::flush()
{
  generatormap->flush();
}
