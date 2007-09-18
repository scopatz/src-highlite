//
// C++ Implementation: outputgenerator
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "outputgenerator.h"

#include <iomanip>
#include "linenumdigit.h"
#include "my_sstream.h"
#include "textgenerator.h"
#include "textstyle.h"

using namespace std;

/// used for line information generation
static SubstitutionMapping substitutionmapping;

OutputGenerator::OutputGenerator(ostream &os, const std::string &pref) :
    output(os), line_prefix(pref), alwaysFlush(false), generateLineInfo(false),
            line_num(1) {
}

OutputGenerator::OutputGenerator(ostream& os, TextGenerator *linegen,
        TextStyle *anch, bool genref, const string &prefix,
        const std::string &line_pref) :
    output(os), line_prefix(line_pref), alwaysFlush(false), generateLineInfo(true),
            generate_ref(genref && ! anch->empty()), anchor(anch), anchor_line_prefix(prefix), line_num(1),
            line_num_generator(linegen) {
}

OutputGenerator::~OutputGenerator() {
}

void OutputGenerator::output_string(const string &s) {
    output << s;

    if (alwaysFlush)
        flush();
}

void OutputGenerator::outputLine(const string &line) {
    if (line_prefix.size())
        output_string(line_prefix);

    output_string(line);
}

void OutputGenerator::generateLine(const string &line) {
    if (line_prefix.size())
        output_string(line_prefix);

    generate_line(line);
}

void OutputGenerator::generate_line(const string &line) {
    if (generateLineInfo)
        generate_line_info();

    ++line_num;

    output_string(line);
}

void OutputGenerator::flush() {
    output << std::flush;
}

void OutputGenerator::reset() {
    line_num = 1;
}

void OutputGenerator::generate_line_info() {
    ostringstream sout;

    sout << std::setw(line_num_digit) << std::setfill(line_num_padding) << line_num << ":";

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

