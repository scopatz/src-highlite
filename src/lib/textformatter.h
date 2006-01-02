//
// C++ Interface: textformatter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H

#include <string>
#include <boost/shared_ptr.hpp>

/**
format text

@author Lorenzo Bettini
*/

class FileInfo;

class TextFormatter
{
public:
  TextFormatter();

  ~TextFormatter();

  void format(const std::string &elem, const std::string &text,
    const FileInfo *);
  void format_nl(const std::string &text = "\n");
  void flush();
};

typedef boost::shared_ptr<TextFormatter> TextFormatterPtr;

#endif
