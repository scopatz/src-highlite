//
// C++ Interface: textformatter
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
#include "readtags.h"
#include "textstyles.h"
#include "refposition.h"

class TextGenerator;
class PreFormatter;
class FileInfo;

/**
 * Formats the elements of a source file, using a map of generators; 
 * associate a generator for each program element, e.g., keyword, string, etc.
 *
 * @author Lorenzo Bettini
 */
class TextFormatter {
protected:
    typedef std::map<std::string, TextGenerator *> MapType;
    typedef std::set<std::string> NoRefType;
    MapType textformatter;
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

    bool generateReferences;

    // for references

    const std::string ctags_file_name;
    TextStyles::RefTextStyle refstyle;
    RefPosition refposition;
    tagFile *ctags_file;
    tagFileInfo info;
    std::ostringstream buffer;

    const std::string generateString(const std::string &elem,
            const std::string &s, const FileInfo *);

    const std::string generateStringAndRef(const std::string &elem,
            const std::string &s, const FileInfo *);

    const std::string generateStringNoRef(const std::string &elem,
            const std::string &s);

    /**
     * Generates the reference information
     */
    const std::string generateRefInfo(const std::string& elem,
            const std::string& s, const FileInfo* arg1);

    /**
     * Actually performs the output through an OutputBuffer
     */
    void output(const std::string &s);

    void generateEntire(const std::string &elem, const std::string &s,
            const FileInfo *);
    void generateNL(const std::string &s);

public:
    TextFormatter(PreFormatter *);

    TextFormatter(PreFormatter *pf, const std::string &_ctags_file_name,
            const TextStyles::RefTextStyle &r, RefPosition pos);

    ~TextFormatter();

    /**
     * Returns the generator for the specific element name or null if
     * there's no generator for the element
     * @param elem 
     * @return 
     */
    TextGenerator *hasGenerator(const std::string &elem);

    /**
     * Retrieves the generator for a specific element; if it doesn't find it,
     * it creates a generator for that element, using the default generator
     * (i.e., the one for "normal" element)
     * @param elem 
     * @return 
     */
    TextGenerator *getGenerator(const std::string &elem);
    void addGenerator(const std::string &elem, TextGenerator *gen);
    void addNoReference(const std::string &elem);
    bool isNoReference(const std::string &elem) const;

    void setDefaultGenerator(TextGenerator *g);

    void flush();

    void setNoOptimizations(bool n) {
        noOptimizations = n;
    }

    void format(const std::string &elem, const std::string &text,
            const FileInfo *);
    void format_nl(const std::string &text = "\n");
};

#endif
