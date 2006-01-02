//
// C++ Implementation: refgeneratormap
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "refgeneratormap.h"
#include "messages.h"
#include "fileinfo.h"
#include "fileutil.h"
#include "mainoutputbuffer.h"
#include "preformatter.h"

#include <boost/regex.hpp>
#include <list>

using namespace std;

bool isTaggable(const string &elem)
{
  return elem.find_first_of(' ') == string::npos;
}

RefGeneratorMap::RefGeneratorMap(PreFormatter *pf, const string &_ctags_file_name,
                                 const TextStyles::RefTextStyle &r, RefPosition pos)
 : GeneratorMap(pf), ctags_file_name(_ctags_file_name),
   refstyle(r), refposition(pos)
{
  ctags_file = tagsOpen (ctags_file_name.c_str(), &info);
  if (ctags_file == 0)
    {
      exitError("cannot open tag file: " + ctags_file_name);
    }
}


RefGeneratorMap::~RefGeneratorMap()
{
  tagsClose(ctags_file);
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

static boost::regex string_or_space_regex("([^[:blank:]]+)|([[:blank:]]+)");
static SubstitutionMapping ref_substitutionmapping;

#define SPACE 2
#define NOT_SPACE 1

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
const std::string RefGeneratorMap::generateString(const std::string& elem, const std::string& s, const FileInfo* fileinfo)
{
    if (isNoReference(elem))
      return GeneratorMap::generateString(elem, s, fileinfo);

    buffer.str("");
    ostringstream tokens;

    boost::sregex_iterator i(s.begin(), s.end(), string_or_space_regex);
    boost::sregex_iterator j;
    while (i != j) {
      if ((*i)[SPACE].matched) {
        tokens << string((*i)[SPACE].first, (*i)[SPACE].second);
      } else {
        string not_spaces = string((*i)[NOT_SPACE].first, (*i)[NOT_SPACE].second);
        string found_refs = _generateString(elem, not_spaces, fileinfo);
        if (found_refs.size()) {
          const string &previous = tokens.str();
          if (previous.size()) {
            buffer << GeneratorMap::generateString(elem, previous, fileinfo);
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
      buffer << GeneratorMap::generateString(elem, remainder, fileinfo);
    }

    return buffer.str();
}

struct RefEntry
{
  string filename;
  unsigned long linenumber;
};

const string RefGeneratorMap::_generateString(const std::string& elem, const std::string& s, const FileInfo* fileinfo)
{
    tagEntry entry;
    bool found = false; // whether we found a tag
    bool found_anchor = false; // whether we found an anchor
    string output;
    typedef list<RefEntry> FoundRefList;
    FoundRefList foundreflist;

    DEB("inspecting " + s)

    if (tagsFind (ctags_file, &entry, s.c_str(), TAG_FULLMATCH) == TagSuccess)
    {
        found = true;
        do
        {
            RefEntry refentry;
            refentry.filename = entry.file;
            if ((refentry.filename == fileinfo->filename ||
                 refentry.filename == fileinfo->input_file_name) &&
                  entry.address.lineNumber == fileinfo->line) {
                ostringstream gen_info;
                  // we just found the reference to this very element
                  // so we must generate an anchor
                gen_info << entry.address.lineNumber;
                DEB("   found anchor " + gen_info.str());
                ref_substitutionmapping["$text"] = preformatter->preformat(s);
                ref_substitutionmapping["$infilename"] = strip_file_path(refentry.filename);
                ref_substitutionmapping["$infile"] = refentry.filename;
                ref_substitutionmapping["$linenum"] = gen_info.str();
                output = refstyle.anchor.output(ref_substitutionmapping);
                found_anchor = true;
                break;
            }
            DEB2("   found " + string(entry.name) + " : ");
            DEB(entry.address.lineNumber);
            refentry.linenumber = entry.address.lineNumber;
            foundreflist.push_back(refentry);
        } while (tagsFindNext (ctags_file, &entry) == TagSuccess);
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
          if (foundreflist.size() > 1 || refposition != INLINE) {
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
