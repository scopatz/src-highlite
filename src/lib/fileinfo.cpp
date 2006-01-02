//
// C++ Implementation: fileinfo
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "fileinfo.h"
#include "fileutil.h"

using namespace std;

FileInfo::FileInfo(const string &input, const string &output)
 : ParserInfo(input), input_file_name(strip_file_path(input)),
   output_file_name(output), output_file_extension("."+get_file_extension(output))
{
}


FileInfo::~FileInfo()
{
}


