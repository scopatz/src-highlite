//
// C++ Interface: outputgenerator
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include <iostream>

/**
base class that actually writes the generated output to the output stream

@author Lorenzo Bettini
*/
class OutputGenerator
{
  private:
    std::ostream &output;
    std::string line_prefix;

  public:
    OutputGenerator(std::ostream &os, const std::string &pref);

    virtual ~OutputGenerator();

    void output_string(const std::string &s);
    /**
     * Generates a generic line (i.e., not necessarily an input
     * line, e.g., a reference line without line number in front)
     * @param s
     */
    void outputLine(const std::string &s);
    /**
     * Generates an input line
     * @param s
     */
    void generateLine(const std::string &s);
    virtual void reset() {}

  protected:
    /**
     * This actually generates the line, and can be redefined
     * by subclasses.
     *
     * @param s
     */
    virtual void generate_line(const std::string &s);
};

#endif
