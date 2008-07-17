//
// C++ Implementation: SourceFileHighlighter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <iostream>
#include <fstream>

#include "sourcefilehighlighter.h"

#include "sourcehighlighter.h"
#include "formatterparams.h"
#include "bufferedoutput.h"
#include "preformatter.h"
#include "linenumgenerator.h"
#include "my_sstream.h"
#include "ioexception.h"

using namespace std;

typedef enum {FOUND_EOF=0, FOUND_NL, FOUND_END} load_line_ret;

static load_line_ret load_line(std::string& s, std::istream& is);

SourceFileHighlighter::SourceFileHighlighter(const std::string &file,
        SourceHighlighter *_sourceHighlighter, BufferedOutput *_output) :
    fileName(file), sourceHighlighter(_sourceHighlighter), output(_output),
            debugPolicy(NO_DEBUG), preformatter(0), lineNumGenerator(0) {
}

load_line_ret load_line(std::string& s, std::istream& is) {
    s.erase();
    if (is.bad()|| is.eof())
        return FOUND_EOF;

    char c;
    while (is.get(c)) {
        if (c == '\n')
            return FOUND_NL;
        if (c != '\r')
            s.append(1, c);
    }

    return FOUND_END;
}

void SourceFileHighlighter::highlight() {
    istream *is = 0;

    if (fileName != "") {
        is = new ifstream(fileName.c_str());
        if (!is || ! (*is)) {
            throw IOException("cannot open for input", fileName);
        }
    } else
        is = &cin;

    highlight(*is);

    if (fileName != "")
        delete is;
}

void SourceFileHighlighter::highlight(istream &is) {
    std::string s;

    FormatterParams params(fileName);
    params.line = 1;

    sourceHighlighter->setFormatterParams(&params);

    load_line_ret ret;
    while ((ret = load_line(s, is)) != FOUND_EOF) {
        output->output(linePrefix);

        if (lineNumGenerator)
            output->output(lineNumGenerator->generateLine(params.line));

        sourceHighlighter->highlightParagraph(s);

        // format the newline
        if (ret == FOUND_NL) {
            // the newline char is not highlighted, but only generated
            // possibly after a transformation
            output->output((preformatter ? preformatter->preformat("\n")
                    : "\n"));
        }

        (params.line)++;

        output->writePostLine(linePrefix);
    }

    output->writePostDoc(linePrefix);
}

void SourceFileHighlighter::highlight(const string &s) {
    istringstream is(s);
    highlight(is);
}
