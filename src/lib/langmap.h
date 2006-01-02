//
// C++ Interface: langmap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LANGMAP_H
#define LANGMAP_H

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

/**
map a file extension to a language definition

@author Lorenzo Bettini
*/
class LangMap
{
  typedef std::map<std::string, std::string> Map;

  Map langmap;

public:
  LangMap() {}
  LangMap(const std::string &path, const std::string &filename);

  ~LangMap();

  void print();
  const std::string &get_file(const std::string &lang) {
    return langmap[lang];
  }
};

typedef boost::shared_ptr<LangMap> LangMapPtr;

#endif
