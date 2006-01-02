//
// C++ Implementation: lineoutputgenerator
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "lineoutputgenerator.h"

#include <iomanip>
#include "linenumdigit.h"
#include "my_sstream.h"
#include "maingeneratormap.h"
#include "textgenerator.h"
#include "textstyle.h"

using namespace std;

static SubstitutionMapping substitutionmapping;

LineOutputGenerator::LineOutputGenerator(ostream& os,
    TextStyle *anch, bool genref, const string &prefix,
    const std::string &line_pref):
  OutputGenerator(os, line_pref), generate_ref(genref && ! anch->empty()),
  anchor(anch), anchor_line_prefix(prefix), line_num(1)
{
  line_num_generator = generatormap->getGenerator("linenum");
}


LineOutputGenerator::~LineOutputGenerator()
{
}


void LineOutputGenerator::generate_line(const string &line)
{
  generate_line_info();
  ++line_num;
  OutputGenerator::generate_line(line);
}

void LineOutputGenerator::reset()
{
    OutputGenerator::reset();
    line_num = 1;
}

void
LineOutputGenerator::generate_line_info()
{
  ostringstream sout;

  sout << std::setw (line_num_digit) << std::setfill ('0')
        << line_num << ":";

  string line_str = line_num_generator->generateEntire(sout.str().c_str());

  if (generate_ref) {
    ostringstream line_n;
    line_n << anchor_line_prefix << line_num;
    sout.str("");
    substitutionmapping["$text"] = line_str;
    substitutionmapping["$linenum"] = line_n.str();
    sout << anchor->output(substitutionmapping);
    line_str = sout.str();
  }

  output_string(line_str + " ");
}
