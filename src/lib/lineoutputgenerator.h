//
// C++ Interface: lineoutputgenerator
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LINEOUTPUTGENERATOR_H
#define LINEOUTPUTGENERATOR_H

#include <outputgenerator.h>

class TextGenerator;
class TextStyle;

/**
a specialized output generator that also generates the line number before each line

@author Lorenzo Bettini
*/
class LineOutputGenerator : public OutputGenerator
{
private:
  bool generate_ref;
  TextStyle *anchor;
  std::string anchor_line_prefix;
  unsigned int line_num;
  TextGenerator *line_num_generator;

public:
    LineOutputGenerator(std::ostream& os,
      TextStyle *anch, bool genref, const std::string &prefix,
      const std::string &line_pref);

    ~LineOutputGenerator();

protected:
  virtual void generate_line(const std::string &line);
    virtual void reset();

    virtual void generate_line_info();
};

#endif
