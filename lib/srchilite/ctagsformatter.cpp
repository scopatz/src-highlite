//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ctagsformatter.h"

#include "preformatter.h"
#include "fileutil.h"
#include "ctagscollector.h"
#include "formatterparams.h"

using namespace std;

namespace srchilite {

/// for formatting anchors and references
static SubstitutionMapping ref_substitutionmapping;

CTagsFormatter::CTagsFormatter(PreFormatter *pre,
        const TextStyles::RefTextStyle &r, CTagsCollector *ctagsC) :
    preFormatter(pre), refstyle(r), ctagsCollector(ctagsC) {
}

CTagsFormatter::~CTagsFormatter() {
}

void CTagsFormatter::setFileInfo(const std::string &input,
        const std::string &output) {
    inputFile = input;
    outputFile = output;

    inputFileName = strip_file_path(inputFile);
    outputFileExtension = ("." + get_file_extension(outputFile));
}

bool CTagsFormatter::formatCTags(const std::string &word,
        CTagsFormatterResults &result, const FormatterParams *params) {
    CTagsInfos ctagsInfo;

    if (!ctagsCollector->collectTags(word, ctagsInfo, params))
        return false; // no tags found for this word

    if (preFormatter)
        ref_substitutionmapping["$text"] = preFormatter->preformat(word);
    else
        ref_substitutionmapping["$text"] = word;

    string output;

    for (CTagsInfos::const_iterator info = ctagsInfo.begin(); info
            != ctagsInfo.end(); ++info) {
        if (info->isAnchor) {
            ref_substitutionmapping["$infilename"]
                    = strip_file_path(info->fileName);
            ref_substitutionmapping["$infile"] = info->fileName;
            ref_substitutionmapping["$linenum"] = info->lineNumber;

            // format and store the anchor
            result.inlineResult
                    = refstyle.anchor.output(ref_substitutionmapping);

            break; // if there's an anchor there can be nothing else
        } else {
            TextStyle *referencestyle = 0;

            // choose the right style
            if (info->refposition == POSTLINE)
                referencestyle = &(refstyle.postline_reference);
            else if (info->refposition == POSTDOC)
                referencestyle = &(refstyle.postdoc_reference);
            else
                referencestyle = &(refstyle.inline_reference);

            string gen_info;
            // we found where this element appears so we generate a reference
            // if it's a link in the same file, we use the output_file_name...
            if (info->fileName == inputFile || info->fileName == inputFileName)
                gen_info = outputFile;
            else
                gen_info = info->fileName + outputFileExtension;
            // ...otherwise we build the referenced file by using the output_file_extension
            // in fact, in this case, it probably means that multiple input files have been specified

            ref_substitutionmapping["$outfile"] = gen_info;
            ref_substitutionmapping["$infilename"]
                    = strip_file_path(info->fileName);
            ref_substitutionmapping["$infile"] = info->fileName;
            ref_substitutionmapping["$linenum"] = info->lineNumber;

            // format and store the reference
            output += referencestyle->output(ref_substitutionmapping);

            // if the following is true, it means that there's not only one reference
            if (ctagsInfo.size()> 1 || info->refposition != INLINE) {
                if (preFormatter)
                    output += preFormatter->preformat("\n");
                else
                    output += "\n";

                if (info->refposition == POSTLINE || info->refposition
                        == INLINE) {
                    result.postLineResult.push_back(output);
                } else { // (refposition == POSTDOC)
                    result.postDocResult.push_back(output);
                }

                output = ""; // no need to modify the current element
            } else {
                result.inlineResult = output;
            }

        }
    }

    return true;
}

}
