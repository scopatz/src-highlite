//
// C++ Implementation: linebuffer
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "linebuffer.h"

LineBuffer::LineBuffer()
{
}


LineBuffer::~LineBuffer()
{
}

bool LineBuffer::empty() const
{
  return (buffer.str().size() == 0 && post.size() == 0);
}
