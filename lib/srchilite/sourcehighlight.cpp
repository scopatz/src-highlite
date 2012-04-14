//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fstream>

#include "sourcehighlight.h"
#include "fileutil.h"
#include "formattermanager.h"
#include "textstyles.h"
#include "preformatter.h"
#include "parsestyles.h"
#include "textstyleformatter.h"
#include "textstyleformatterfactory.h"
#include "outlangdefparserfun.h"
#include "langdefmanager.h"
#include "regexrulefactory.h"
#include "highlightstate.h"
#include "sourcehighlighter.h"
#include "bufferedoutput.h"
#include "sourcefilehighlighter.h"
#include "linenumgenerator.h"
#include "ioexception.h"
#include "docgenerator.h"
#include "srcuntabifier.h"
#include "langmap.h"
#include "parserexception.h"
#include "ctagsmanager.h"
#include "ctagsformatter.h"
#include "highlightstateprinter.h"
#include "langelemsprinter.hpp"
#include "langelems.h"
#include "verbosity.h"
#include "settings.h"

using namespace std;

namespace srchilite {

SourceHighlight::SourceHighlight(const std::string &_outputLang) :
    outputLang(_outputLang), dataDir(Settings::retrieveDataDir()), styleFile(
            "default.style"), formatterManager(0), preFormatter(0),
            langDefManager(new LangDefManager(new RegexRuleFactory)),
            lineNumGenerator(0), docGenerator(0), noDocGenerator(0),
            highlightEventListener(0), ctagsManager(0), ctagsFormatter(0),
            lineRanges(0), regexRanges(0), optimize(true), generateLineNumbers(
                    false), generateLineNumberRefs(false), lineNumberPad('0'),
            lineNumberDigits(0), generateEntireDoc(false),
            generateVersion(true), canUseStdOut(true), binaryOutput(false),
            tabSpaces(0) {
}

SourceHighlight::~SourceHighlight() {
    if (formatterManager)
        delete formatterManager;

    if (preFormatter)
        delete preFormatter;

    delete langDefManager->getRuleFactory();
    delete langDefManager;

    if (lineNumGenerator)
        delete lineNumGenerator;

    if (docGenerator)
        delete docGenerator;

    if (noDocGenerator)
        delete noDocGenerator;

    if (ctagsFormatter)
        delete ctagsFormatter;
}

void SourceHighlight::initialize() {
    if (formatterManager)
        return; // already initialized

    TextStylesPtr textStyles = parse_outlang_def(dataDir.c_str(),
            outputLang.c_str());

    FormatterPtr defaultFormatter(new TextStyleFormatter("$text"));
    formatterManager = new FormatterManager(defaultFormatter);

    if (tabSpaces) {
        preFormatter = new Untabifier(tabSpaces);
        preFormatter->setPreFormatter(PreFormatterPtr(new PreFormatter(
                textStyles->charTranslator)));
    } else {
        preFormatter = new PreFormatter(textStyles->charTranslator);
    }

    linePrefix = textStyles->line_prefix;

    if (ctagsManager) {
        ctagsFormatter = ctagsManager->createCTagsFormatter(
                textStyles->refstyle);
        ctagsFormatter->setPreFormatter(preFormatter);
    }

    TextStyleFormatterFactory formatterFactory(textStyles, preFormatter,
            ctagsFormatter, formatterManager);

    if (styleCssFile.size())
        parseCssStyles(dataDir, styleCssFile, &formatterFactory,
                backgroundColor);
    else
        parseStyles(dataDir, styleFile, &formatterFactory, backgroundColor);

    // keep the background color empty if none is specified
    if (backgroundColor != "")
        backgroundColor = formatterFactory.preprocessColor(backgroundColor);

    formatterFactory.addDefaultFormatter();

    // use the style default file to build missing formatters
    if (styleDefaultFile.size()) {
        LangMap defaultStyles(dataDir, styleDefaultFile);
        defaultStyles.open();
        for (LangMap::const_iterator it = defaultStyles.begin(); it
                != defaultStyles.end(); ++it) {
            formatterFactory.createMissingFormatter(it->first, it->second);
        }
    }

    formatterCollection = formatterFactory.getFormatterCollection();

    // initialize the line number generator
    TextStyleFormatter *lineNumFormatter =
            dynamic_cast<TextStyleFormatter *> (formatterManager->getFormatter(
                    "linenum").get());
    lineNumGenerator = new LineNumGenerator(lineNumFormatter->toString(), 5,
            lineNumberPad);
    lineNumGenerator->setAnchorPrefix(lineNumberAnchorPrefix);
    if (generateLineNumberRefs)
        lineNumGenerator->setAnchorStyle(textStyles->refstyle.anchor);

    docGenerator = new DocGenerator(textStyles->docTemplate.toStringBegin(),
            textStyles->docTemplate.toStringEnd());
    noDocGenerator = new DocGenerator(
            textStyles->noDocTemplate.toStringBegin(),
            textStyles->noDocTemplate.toStringEnd());

    docGenerator->set_gen_version(generateVersion);
    noDocGenerator->set_gen_version(generateVersion);

    docGenerator->setBackgroundColor(backgroundColor);
    noDocGenerator->setBackgroundColor(backgroundColor);

    docGenerator->setCss(css);
    noDocGenerator->setCss(css);

    // open possible header and footer files
    if (headerFileName.size()) {
        const string &header = readFile(headerFileName);
        docGenerator->setHeader(header);
        noDocGenerator->setHeader(header);
    }

    if (footerFileName.size()) {
        const string &footer = readFile(footerFileName);
        docGenerator->setFooter(footer);
        noDocGenerator->setFooter(footer);
    }

    // set the preformatter in all the formatters
    for (TextStyleFormatterCollection::const_iterator it =
            formatterCollection.begin(); it != formatterCollection.end(); ++it) {
        (*it)->setPreFormatter(preFormatter);
    }

    outputFileExtension = textStyles->file_extension;
}

void SourceHighlight::highlight(const std::string &input,
        const std::string &_output, const std::string &inputLang) {

    initialize();

    // the output file name could be empty, and we might generate it, so make a copy
    string output = _output;

    HighlightStatePtr highlightState = langDefManager->getHighlightState(
            dataDir, inputLang);

    // compute line number digits (if a file name is specified)
    if (generateLineNumbers && input.size()) {
        ifstream is(input.c_str());

        if (!is) {
            throw IOException("cannot open input file", input);
        }

        unsigned int lines = get_line_count(is);

        int line_num_digit = 0;
        while (lines) {
            ++line_num_digit;
            lines /= 10;
        }

        lineNumGenerator->setDigitNum(line_num_digit);
    }

    ifstream is;
    ofstream os;

    bool use_stdin = !input.size();

    // in case of multiple files we must disable generation to stdout.
    bool use_stdout = (!output.size() && canUseStdOut) || output == "STDOUT";

    if (!use_stdin) {
        is.open(input.c_str());
        if (!is) {
            throw IOException("cannot open input file", input);
        }
    }

    if (!use_stdout) {
        // in case the output file is not specified
        if (!output.size()) {
            // in this case we need the extension defined in the outlang
            if (!outputFileExtension.size()) {
                // we can't continue
                ParserException e("missing file extension in " + outputLang,
                        "source-highlight");
                e.additional
                        = "this is needed when the output file is not specified";
                throw e;
            }

            // generate the output file name starting from known info
            output = createOutputFileName(input);
        }

        if (binaryOutput) {
            os.open(output.c_str(), std::ios::out | std::ios::binary);
        } else {
            os.open(output.c_str());
        }

        if (!os) {
            throw IOException("cannot open output file", output);
        }
    }

    docGenerator->setInputFileName(input);
    noDocGenerator->setInputFileName(input);

    if (!title.size()) {
        // if the title was not set, then use the input file name
        docGenerator->setTitle(input);
        noDocGenerator->setTitle(input);
    }

    docGenerator->setInputLang(inputLang);
    noDocGenerator->setInputLang(inputLang);      

    if (ctagsFormatter) {
        // if we need to generate references, then set the file info
        ctagsFormatter->setFileInfo(input, output);
    }

    highlight((use_stdin ? cin : is), (use_stdout ? cout : os), inputLang,
            input);

    if (is.is_open())
        is.close();
    if (os.is_open())
        os.close();
}

const string SourceHighlight::createOutputFileName(const std::string &inputFile) {
    return srchilite::createOutputFileName(inputFile, outputFileDir,
            outputFileExtension);
}

void SourceHighlight::highlight(std::istream &input, std::ostream &output,
        const std::string &inputLang, const std::string &inputFileName) {

    initialize();

    HighlightStatePtr highlightState = langDefManager->getHighlightState(
            dataDir, inputLang);

    SourceHighlighter highlighter(highlightState);
    highlighter.setFormatterManager(formatterManager);
    highlighter.setOptimize(optimize);
    if (highlightEventListener)
        highlighter.addListener(highlightEventListener);

    BufferedOutput bufferedOutput(output);

    // if no optimization, then always flush the output
    if (!optimize)
        bufferedOutput.setAlwaysFlush(true);

    updateBufferedOutput(&bufferedOutput);

    SourceFileHighlighter fileHighlighter(inputFileName, &highlighter,
            &bufferedOutput);

    fileHighlighter.setLineRanges(lineRanges);
    fileHighlighter.setRegexRanges(regexRanges);

    if (generateLineNumbers) {
        fileHighlighter.setLineNumGenerator(lineNumGenerator);
        if (lineNumberDigits != 0) {
            lineNumGenerator->setDigitNum(lineNumberDigits);
        }
    }

    // set the prefix for all lines
    fileHighlighter.setLinePrefix(linePrefix);

    fileHighlighter.setPreformatter(preFormatter);

    // set the range separator only after the preformatter!
    // since the separator itself might have to be preformatted
    if (rangeSeparator.size()) {
        fileHighlighter.setRangeSeparator(rangeSeparator);
    }

    // the formatter for possible context lines
    fileHighlighter.setContextFormatter(formatterManager->getFormatter(
            "context").get());

    DocGenerator *documentGenerator = (generateEntireDoc ? docGenerator
            : noDocGenerator);

    if (title.size()) {
        // for each output set the title
        documentGenerator->setTitle(title);
    }

    documentGenerator->setInputLang(inputLang);

    // first generate the start of the output file
    documentGenerator->generate_start_doc(&output);

    fileHighlighter.highlight(input);

    // finally generate the end of the output file
    documentGenerator->generate_end_doc(&output);

    // since the highlighter can be re-used, we need to remove the
    // listener for other runs
    if (highlightEventListener)
        highlighter.removeListener(highlightEventListener);
}

void SourceHighlight::checkLangDef(const std::string &langFile) {
    // make sure to build the highlight state each time
    langDefManager->buildHighlightState(dataDir, langFile);

    // if we get here, no problems were found, otherwise this method
    // exits with an exception
}

void SourceHighlight::checkOutLangDef(const std::string &outlangFile) {
    // make sure to build the highlight state each time
    parse_outlang_def(dataDir.c_str(), outlangFile.c_str());

    // if we get here, no problems were found, otherwise this method
    // exits with an exception
}

void SourceHighlight::printHighlightState(const std::string &langFile,
        std::ostream &os) {
    HighlightStatePrinter printer(os);

    printer.printHighlightState(langDefManager->buildHighlightState(dataDir,
            langFile).get());
}

void SourceHighlight::printLangElems(const std::string &langFile,
        std::ostream &os) {
    LangElemsPrinter printer;
    LangElems *elems = langDefManager->getLangElems(dataDir, langFile);

    printer.print(elems, os);

    delete elems;
}

void SourceHighlight::updateBufferedOutput(BufferedOutput *output) {
    for (TextStyleFormatterCollection::const_iterator it =
            formatterCollection.begin(); it != formatterCollection.end(); ++it) {
        (*it)->setBufferedOutput(output);
    }
}

}
