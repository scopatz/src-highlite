//
// C++ Interface: outputbuffer
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

#include <set>
#include <string>

#include "linebuffer.h"

class OutputGenerator;

/**
contains the output buffer.

@author Lorenzo Bettini
*/
class OutputBuffer : protected LineBuffer::PostContents
{
  private:
    LineBufferPtr linebuffer;
    OutputGenerator *outputGenerator;

    void reset();

  public:
    OutputBuffer();

    ~OutputBuffer();

    void output(const std::string &s);
    void output_ln(const std::string &s);
    void output_postline(const std::string &s);
    void output_post(const std::string &s);

    void flush();

    void setOutputGenerator(OutputGenerator *og) { outputGenerator = og; }
};

#endif
