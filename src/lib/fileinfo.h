//
// C++ Interface: fileinfo
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FILEINFO_H
#define FILEINFO_H

#include <parserinfo.h>

/**
Information about the file we are processing

@author Lorenzo Bettini
*/
struct FileInfo : public ParserInfo
{
  std::string input_file_name; // with no path
  std::string output_file_name;
  std::string output_file_extension;

  FileInfo(const std::string &input, const std::string &output);

  ~FileInfo();

};

#endif
