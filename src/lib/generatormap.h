//
// C++ Interface: generatormap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GENERATORMAP_H
#define GENERATORMAP_H

#include <map>
#include <string>
#include <set>
#include "my_sstream.h"

class TextGenerator;
class PreFormatter;
class FileInfo;

/**
map of generators; associate a generator for each program element, e.g., keyword, string, etc.

@author Lorenzo Bettini
*/
class GeneratorMap
{
 protected:
  typedef std::map<std::string, TextGenerator *> MapType;
  typedef std::set<std::string> NoRefType;
  MapType generatormap;
  /// those elements for which no reference info is generated
  NoRefType noreferences;
  TextGenerator *default_generator;
  PreFormatter *preformatter;
  /// where we buffer strings for the current elem
  std::ostringstream elem_buffer;
  /// the element that is currently buffered
  std::string current_elem;
  /// concerns the element currently buffered
  const FileInfo *current_file_info;
  /// whether to turn off optimizazionts (such as buffering), default: false
  bool noOptimizations;

  virtual const std::string generateString(const std::string &elem,
    const std::string &s, const FileInfo *);
  void output(const std::string &s);

 public:
  GeneratorMap(PreFormatter *);
  virtual ~GeneratorMap();

  TextGenerator *getGenerator(const std::string &elem);
  void addGenerator(const std::string &elem, TextGenerator *gen);
  void addNoReference(const std::string &elem);
  bool isNoReference(const std::string &elem) const;

  void setDefaultGenerator(TextGenerator *g);

  void generateEntire( const std::string &elem,
    const std::string &s, const FileInfo * );
  void generateNL( const std::string &s );
  void flush();

  void setNoOptimizations(bool n) { noOptimizations = n; }
};

#endif
