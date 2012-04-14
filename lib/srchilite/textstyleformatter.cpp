/**
 * C++ class: textstyleformatter.cpp
 *
 * Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005-2008
 * Copyright: See COPYING file that comes with this distribution
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "textstyleformatter.h"
#include "bufferedoutput.h"
#include "preformatter.h"
#include "ctagsformatter.h"
#include "wordtokenizer.h"
#include <sstream>

using namespace std;

namespace srchilite {

TextStyleFormatter::TextStyleFormatter(const TextStyle &style, BufferedOutput *o) :
    textstyle(style), output(o), preFormatter(0), ctagsFormatter(0) {
}

TextStyleFormatter::TextStyleFormatter(const string &repr, BufferedOutput *o) :
    textstyle(TextStyle(repr)), output(o), preFormatter(0), ctagsFormatter(0) {
}

void TextStyleFormatter::format(const string &s, const FormatterParams *params) {
    // first check whether the reference formatter can format the paragraph
    if (!formatReferences(s, params))
        doFormat(s); // otherwise we do it ourselves
}

void TextStyleFormatter::doFormat(const string &s, bool preformat) {
    if (!s.size())
        return;

    if (preFormatter && preformat) {
        output->output(textstyle.output(preFormatter->preformat(s)));
    } else {
        output->output(textstyle.output(s));
    }
}

bool TextStyleFormatter::formatReferences(const string &s,
        const FormatterParams *params) {
    if (ctagsFormatter && params) {
        // for each word in s try to format an anchor or reference
        WordTokenizer::WordTokenizerResults tokens;
        WordTokenizer::tokenize(s, tokens);

        // here we buffer parts that are not references (or spaces)
        ostringstream notReferences;
        CTagsFormatterResults results;

        for (WordTokenizer::WordTokenizerResults::const_iterator token =
                tokens.begin(); token != tokens.end(); ++token) {
            if (token->first.size())  { // a space
                notReferences << token->first;
            } else {
                if (ctagsFormatter->formatCTags(token->second, results, params)) {
                    // first format the previous non reference parts if any
                    doFormat(notReferences.str());
                    notReferences.str("");

                    // then the anchors and references
                    if (results.inlineResult.size()) {
                        // don't preformat: it's already been done
                        doFormat(results.inlineResult, false);
                    } else {
                        // inline result excludes the other ones
                        output->postLineInsertFrom(results.postLineResult);
                        output->postDocInsertFrom(results.postDocResult);

                        // we still need to format this word, since otherwise
                        // it won't appear in the text of the program
                        doFormat(token->second);
                    }

                    // clear results for possible other formatting
                    results.clear();
                } else {
                    notReferences << token->second;
                }
            }
        }

        // format possible buffered tokens
        doFormat(notReferences.str());

        return true;
    }

    return false;
}

}
