//
// C++ Interface: linebuffer
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LINEBUFFER_H
#define LINEBUFFER_H

#include <string>
#include <set>
#include <boost/shared_ptr.hpp>

#include "my_sstream.h"

/**
A buffer for a line to be generated

@author Lorenzo Bettini
*/
class LineBuffer
{
  public:
    typedef std::set<std::string> PostContents;

  private:
    ostringstream buffer; // the line contents
    PostContents post; // to be generated after the line

  public:
    LineBuffer() {}
    ~LineBuffer() {}

    void output(const std::string &s) { buffer << s; }
    void output_post(const std::string &s) { post.insert(s); }

    const std::string getContents() const { return buffer.str(); }
    const PostContents &getPostContents() const { return post; }

    bool empty() const { return (buffer.str().size() == 0 && post.size() == 0); }
};

typedef boost::shared_ptr<LineBuffer> LineBufferPtr;

#endif
