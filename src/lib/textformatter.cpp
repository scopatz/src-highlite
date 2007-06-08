//
// C++ Implementation: textformatter
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 1999-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "textformatter.h"
#include "textgenerator.h"
#include "preformatter.h"
#include "mainoutputbuffer.h"
#include "messages.h"
#include "fileutil.h"
#include "fileinfo.h"

#include <boost/regex.hpp>
#include <list>

using namespace std;

bool isTaggable(const string &elem) {
    return elem.find_first_of(' ')== string::npos;
}

static boost::regex string_or_space_regex("([^[:blank:]]+)|([[:blank:]]+)");
static SubstitutionMapping ref_substitutionmapping;

#define SPACE 2
#define NOT_SPACE 1

TextFormatter::TextFormatter(PreFormatter *pf) :
    default_generator(0), preformatter(pf), noOptimizations(false),
            generateReferences(false), ctags_file(0) {
}

TextFormatter::TextFormatter(PreFormatter *pf, const string &_ctags_file_name,
        const TextStyles::RefTextStyle &r, RefPosition pos) :
    default_generator(0), preformatter(pf), noOptimizations(false),
            generateReferences(true), ctags_file_name(_ctags_file_name),
            refstyle(r), refposition(pos) {
    ctags_file = tagsOpen(ctags_file_name.c_str(), &info);
    if (ctags_file == 0) {
        exitError("cannot open tag file: " + ctags_file_name);
    }
}

TextFormatter::~TextFormatter() {
    for (MapType::const_iterator it = textformatter.begin(); it != textformatter.end(); ++it)
        delete it->second;

    if (ctags_file)
        tagsClose(ctags_file);
}

void TextFormatter::setDefaultGenerator(TextGenerator *gen) {
    default_generator = gen;
}

void TextFormatter::addGenerator(const std::string &elem, TextGenerator *gen) {
    textformatter[elem] = gen;
}

TextGenerator *TextFormatter::hasGenerator(const string &elem) {
    MapType::const_iterator it = textformatter.find(elem);
    if (it == textformatter.end())
        return 0;

    return it->second;
}

TextGenerator *TextFormatter::getGenerator(const string &elem) {
    MapType::const_iterator it = textformatter.find(elem);
    if (it == textformatter.end()) {
        // create a copy of the prototype and substitute the style.
        TextGenerator *missing = new TextGenerator(*default_generator);
        missing->subst_style(elem);

        textformatter[elem] = missing;
        return missing;
    }

    return it->second;
}

void TextFormatter::addNoReference(const std::string &elem) {
    noreferences.insert(elem);
}

bool TextFormatter::isNoReference(const std::string &elem) const {
    return (noreferences.find(elem) != noreferences.end());
}

const string TextFormatter::generateString(const std::string &elem,
        const std::string &s, const FileInfo *p) {
    if (!generateReferences || isNoReference(elem)) {
        return generateStringNoRef(elem, s);
    } else {
        return generateStringAndRef(elem, s, p);
    }
}

const string TextFormatter::generateStringNoRef(const std::string &elem,
        const std::string &s) {
    return getGenerator(elem)->generateEntire(preformatter->preformat(s));
}

void TextFormatter::generateEntire(const std::string &elem,
        const std::string &s, const FileInfo *p) {
    if (noOptimizations) {
        // we generate the element right now, since during debugging
        // we want to be very responsive
        if (s.size())
            output(generateString(elem, s, p));

        return;
    }

    // otherwise we optmize output generation: delay formatting a specific
    // element until we deal with another element; this way strings that belong
    // to the same element are formatted using only one tag: e.g.,
    // <comment>/* mycomment */</comment>
    // instead of
    // <comment>/*</comment><comment>mycomment</comment><comment>*/</comment>
    if (elem == current_elem) {
        elem_buffer << s;
    } else {
        // first format the buffered string
        const string toformat = elem_buffer.str();
        if (toformat.size())
            output(generateString(current_elem, toformat, p));

        // then start a new buffer
        elem_buffer.str("");
        elem_buffer << s;
        current_elem = elem;
        current_file_info = p;
    }
}

void TextFormatter::generateNL(const std::string &text) {
    // first format the buffered string
    flush();

    string preformat_text = preformatter->preformat(text);

    if (preformat_text == text)
        preformat_text = "\n";

    outputbuffer->output_ln(preformat_text);
}

void TextFormatter::flush() {
    const string &remainder = elem_buffer.str();
    if (remainder.size()) {
        output(generateString(current_elem, remainder, current_file_info));
        elem_buffer.str("");
        current_elem = "";
        // each line is handled separately
    }
}

void TextFormatter::output(const string &s) {
    outputbuffer->output(s);
}

//#define DEBUGREF
#ifdef DEBUGREF
#include <iostream>
#define DEB(x) cerr << x << endl;
#define DEB2(x) cerr << x ;
#else
#define DEB(x) ;
#define DEB2(x) ;
#endif

/*
 * separates a line in block of spaces and block of non spaces.
 * the stringbuffer tokens stores the pieces seen so far for which no
 * entry in the tag file was found.
 *
 * for each block of non spaces tries to look for an entry in the tag.
 * if it finds it flushes the stringbuffer tokens (by passing its contents
 * to the parent class implementation of generateString).
 *
 * For instance (notice the spaces among the +)
 *    "myfield + myfield2 + myfield3
 * if only an entry for myfield2 is found, the we will generate
 * 3 blocks:
 *  "myfield + "
 *  "myfield2"
 *  " + myfield3"
 */
const std::string TextFormatter::generateStringAndRef(const std::string& elem,
        const std::string& s, const FileInfo* fileinfo) {
    buffer.str("");
    ostringstream tokens;

    boost::sregex_iterator i(s.begin(), s.end(), string_or_space_regex);
    boost::sregex_iterator j;
    while (i != j) {
        if ((*i)[SPACE].matched) {
            tokens << string((*i)[SPACE].first, (*i)[SPACE].second);
        } else {
            string not_spaces = string((*i)[NOT_SPACE].first, (*i)[NOT_SPACE].second);
            string found_refs = generateRefInfo(elem, not_spaces, fileinfo);
            if (found_refs.size()) {
                const string &previous = tokens.str();
                if (previous.size()) {
                    buffer << generateStringNoRef(elem, previous);
                    tokens.str("");
                }
                buffer << found_refs;
            } else {
                tokens << not_spaces;
            }
        }

        ++i;
    }

    const string &remainder = tokens.str();
    if (remainder.size()) {
        buffer << generateStringNoRef(elem, remainder);
    }

    return buffer.str();
}

struct RefEntry {
    string filename;
    unsigned long linenumber;
};

const string TextFormatter::generateRefInfo(const std::string& elem,
        const std::string& s, const FileInfo* fileinfo) {
    tagEntry entry;
    bool found = false; // whether we found a tag
    bool found_anchor = false; // whether we found an anchor
    string output;
    typedef list<RefEntry> FoundRefList;
    FoundRefList foundreflist;

    DEB("inspecting " + s)

    if (tagsFind(ctags_file, &entry, s.c_str(), TAG_FULLMATCH)== TagSuccess) {
        found = true;
        do {
            RefEntry refentry;
            refentry.filename = entry.file;
            if ((refentry.filename == fileinfo->filename ||
                    refentry.filename == fileinfo->input_file_name) &&entry.address.lineNumber == fileinfo->line) {
                ostringstream gen_info;
                // we just found the reference to this very element
                // so we must generate an anchor
                gen_info << entry.address.lineNumber;DEB("   found anchor " + gen_info.str());
                ref_substitutionmapping["$text"] = preformatter->preformat(s);
                ref_substitutionmapping["$infilename"] = strip_file_path(refentry.filename);
                ref_substitutionmapping["$infile"] = refentry.filename;
                ref_substitutionmapping["$linenum"] = gen_info.str();
                output = refstyle.anchor.output(ref_substitutionmapping);
                found_anchor = true;
                break;
            }

            DEB2("   found " + string(entry.name) + " : ");DEB(entry.address.lineNumber);

            refentry.linenumber = entry.address.lineNumber;
            foundreflist.push_back(refentry);
        } while (tagsFindNext(ctags_file, &entry)== TagSuccess);
    }

    if (found) {
        if (! found_anchor) {
            ref_substitutionmapping["$text"] = preformatter->preformat(s);
            TextStyle *referencestyle = 0;
            if ((foundreflist.size()>1 && refposition == INLINE) || refposition == POSTLINE)
                referencestyle = &(refstyle.postline_reference);
            else if (refposition == POSTDOC)
                referencestyle = &(refstyle.postdoc_reference);
            else
                referencestyle = &(refstyle.inline_reference);

            for (FoundRefList::const_iterator it = foundreflist.begin(); it != foundreflist.end(); ++it) {
                ostringstream gen_info;
                // we found where this element appears so we generate a reference
                // if it's a link in the same file, we use the output_file_name...
                if (it->filename == fileinfo->filename || it->filename == fileinfo->input_file_name)
                    gen_info << fileinfo->output_file_name;
                else
                    gen_info << it->filename << fileinfo->output_file_extension;
                // ...otherwise we build the referenced file by using the output_file_extension
                // in fact, in this case, it probably means that multiple input files have been specified

                ref_substitutionmapping["$outfile"] = gen_info.str();
                ref_substitutionmapping["$infilename"] = strip_file_path(it->filename);
                ref_substitutionmapping["$infile"] = it->filename;

                gen_info.str("");
                gen_info << it->linenumber;
                ref_substitutionmapping["$linenum"] = gen_info.str();
                output += referencestyle->output(ref_substitutionmapping);

                // if the following is true, it means that there more than one reference
                if (foundreflist.size()> 1 || refposition != INLINE) {
                    output += preformatter->preformat("\n");

                    if (refposition == POSTLINE || refposition == INLINE) {
                        outputbuffer->output_postline(output);
                    } else { // (refposition == POSTDOC)
                        outputbuffer->output_post(output);
                    }

                    output = ""; // no need to modify the current element
                }
            }
        }
    }

    return output;
}

void TextFormatter::format(const string &elem, const string &text,
        const FileInfo *p) {
    if (! text.size())
        return;

    generateEntire(elem, text, p);
}

void TextFormatter::format_nl(const string &text) {
    generateNL(text);
}
