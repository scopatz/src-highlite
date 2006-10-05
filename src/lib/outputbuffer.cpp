//
// C++ Implementation: outputbuffer
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "outputbuffer.h"
#include "outputgenerator.h"

#include <algorithm>
#include <iterator>

using namespace std;

OutputBuffer::OutputBuffer() :
    linebuffer(new LineBuffer), outputGenerator(0), alwaysFlush(false),
    newLine(true)
{
}


OutputBuffer::~OutputBuffer()
{
}

void
OutputBuffer::output_ln(const string &s)
{
  if (alwaysFlush) {
    outputAndFlush( s );
    newLine = true;
  } else {
    linebuffer->output(s);
    outputGenerator->generateLine(linebuffer->getContents());
  }
  const LineBuffer::PostContents &post = linebuffer->getPostContents();
  if (post.size()) {
    for (LineBuffer::PostContents::const_iterator it = post.begin();
         it != post.end(); ++it)
      outputGenerator->outputLine(*it);
  }
  linebuffer = LineBufferPtr(new LineBuffer);
}

void
OutputBuffer::output(const string &s)
{
  if (alwaysFlush)
    outputAndFlush( s );
  else
    linebuffer->output(s);
}

void
OutputBuffer::outputAndFlush(const string &s)
{
  if (newLine) {
    outputGenerator->outputLine( s );
    newLine = false;
  } else {
    outputGenerator->output_string( s );
  }
}

void
OutputBuffer::output_postline(const string &s)
{
  linebuffer->output_post(s);
}

void
OutputBuffer::output_post(const string &s)
{
  insert(s);
}

void
OutputBuffer::reset()
{
  clear();
  linebuffer = LineBufferPtr(new LineBuffer);
  outputGenerator->reset();
}

void
OutputBuffer::flush()
{
  if (! linebuffer->empty())
    output_ln("");

  for (const_iterator it = begin(); it != end(); ++it) {
    outputGenerator->outputLine(*it);
  }

  reset();
}

