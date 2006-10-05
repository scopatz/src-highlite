//
// C++ Implementation: outputgenerator
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "outputgenerator.h"

using namespace std;

OutputGenerator::OutputGenerator(ostream &os, const std::string &pref) :
    output(os), line_prefix(pref), alwaysFlush(false)
{
}

OutputGenerator::~OutputGenerator()
{
}

void
OutputGenerator::output_string(const string &s)
{
    output << s;

    if (alwaysFlush)
      flush();
}

void
OutputGenerator::outputLine(const string &line)
{
  if (line_prefix.size())
    output_string(line_prefix);

  output_string(line);
}

void
OutputGenerator::generateLine(const string &line)
{
  if (line_prefix.size())
    output_string(line_prefix);

  generate_line(line);
}

void
OutputGenerator::generate_line(const string &line)
{
  output_string(line);
}

void
OutputGenerator::flush()
{
  output << std::flush;
}
