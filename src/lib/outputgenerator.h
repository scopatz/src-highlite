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

class TextGenerator;
class TextStyle;

/**
base class that actually writes the generated output to the output stream

@author Lorenzo Bettini
*/
class OutputGenerator
{
  private:
    /// the stream used to output strings
    std::ostream &output;
    /// the string generated at the beginning of each new line
    std::string line_prefix;
    /// whether to flush the stream at each output (default = false)
    bool alwaysFlush;
    
    /// whether to generate line information
    bool generateLineInfo;
    
    // for line information

    bool generate_ref;
    TextStyle *anchor;
    std::string anchor_line_prefix;
    unsigned int line_num;
    TextGenerator *line_num_generator;

  public:
    OutputGenerator(std::ostream &os, const std::string &pref);
    
    OutputGenerator(std::ostream& os, TextGenerator *linegen,
                TextStyle *anch, bool genref, const std::string &prefix,
                const std::string &line_pref);

    ~OutputGenerator();

    void setAlwaysFlush(bool b) { alwaysFlush = b; }

    /**
     * Outputs the passed string in the output
     * @param s The string to output
     */
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

    /**
     * Flushes the stream
     */
    void flush();

    /**
     * Resets the generator (i.e., resets line number)
     */
    void reset();

  protected:
    /**
     * This actually generates the line, and can be redefined
     * by subclasses.
     *
     * @param s
     */
    void generate_line(const std::string &s);
    
    /**
     * Generates line information
     */
    void generate_line_info();
};

#endif
