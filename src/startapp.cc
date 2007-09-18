/*
 * Copyright (C) 1999-2007  Lorenzo Bettini, www.lorenzobettini.it
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "startapp.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>

#include "colors.h"
#include "cmdline.h"
#include "fileutil.h"
#include "utils.h"
#include "messages.h"

#include "copyright.h"
#include "reportbugs.h"
#include "parsestyles.h"

#include "generatorfactory.h"
#include "srcuntabifier.h"
#include "chartranslator.h"
#include "langdefloader.h"
#include "outputgenerator.h"
#include "langmap.h"
#include "regexpengine.h"
#include "regexpenginedebug.h"
#include "docgenerator.h"
#include "textstyles.h"
#include "outlangdefparserfun.h"
#include "fileinfo.h"
#include "stopwatch.h"
#include "textformatter.h"

#include "languageinfer.h"

// for globals
#include "linenumdigit.h"
#include "globalostream.h"
#include "cmdlineargs.h"
#include "mainoutputbuffer.h"

using namespace std;

// global output stream
ostream* sout;

#ifdef BUILD_AS_CGI
#include "envmapper.h"
#endif // BUILD_AS_CGI

unsigned int line_num_digit = 0; // num of digits to represent line number
char line_num_padding = '0';     // character to use for padding the line number

gengetopt_args_info args_info; // command line structure

static void print_cgi_header();
static void run_ctags(const string &cmd);

/**
 * Print progress status information (provided --quiet is not specified)
 * @param message
 */
static void progressInfo(const string &message) {
    if (args_info.quiet_given)
        return;

    cerr << message;
}

StartApp::StartApp() :
    docgenerator(0), preformatter(0), langmap(new LangMap),
            outlangmap(new LangMap), generator_factory(0), entire_doc(0),
            verbose(0), cssUrl(0), use_css(0), is_cgi(0), gen_version(true),
            generate_line_num(false), generate_ref(false) {
}

StartApp::~StartApp() {
    // cout << "destroying StartApp..." << endl;
    cmdline_parser_free(&args_info);

    if (preformatter)
        delete preformatter;

    if (docgenerator)
        delete docgenerator;

    if (generator_factory)
        delete generator_factory;
}

int StartApp::start(int argc, char * argv[]) {
    char *docTitle;
    char *docHeader; // the buffer with the header
    char *docFooter; // the buffer with the footer
    const char *header_fileName = 0;
    const char *footer_fileName = 0;
    unsigned i;
    int v;
    int tabSpaces = 0;

#ifdef BUILD_AS_CGI
    // map environment to parameters if used as CGI
    char **temp_argv;
    temp_argv = map_environment(&argc, argv);
    is_cgi = temp_argv != argv;
    argv = temp_argv;
#endif // BUILD_AS_CGI
    if ((v = cmdline_parser(argc, argv, &args_info)) != 0)
        // calls cmdline parser. The user gived bag args if it doesn't return -1
        return EXIT_FAILURE;

    if (args_info.version_given) {
        print_version();
        print_copyright();
        return EXIT_SUCCESS;
    }

    if (args_info.help_given) {
        cout << "GNU ";
        cmdline_parser_print_help();
        print_reportbugs();
        return EXIT_SUCCESS;
    }

    gen_version = (args_info.gen_version_flag != 0);

    /* initialization of global symbols */
    inputFileName = outputFileName = 0;
    sout = 0;
    docTitle = 0;
    docHeader = 0;
    docFooter = 0;

    docTitle = args_info.title_arg;
    header_fileName = args_info.header_arg;
    footer_fileName = args_info.footer_arg;
    verbose = args_info.verbose_given;
    const string style_file = args_info.style_file_arg;

    if (args_info.tab_given > 0)
        tabSpaces = args_info.tab_arg;

    if (header_fileName)
        docHeader = read_file(header_fileName);

    if (footer_fileName)
        docFooter = read_file(footer_fileName);

    cssUrl = args_info.css_arg;
    use_css = ( cssUrl != 0 );

    entire_doc =(! args_info.no_doc_given) &&( args_info.doc_given || (docTitle != 0) || use_css );

    string inputFileName;
    if (args_info.input_given)
        inputFileName = args_info.input_arg;

    string outputFileName;
    if (inputFileName.size()&& ! is_cgi && args_info.output_given)
        outputFileName = args_info.output_arg;

    bool generate_to_stdout =(args_info.output_arg &&
            strcmp (args_info.output_arg, "STDOUT") == 0);

    if (verbose)
        setMessager(new DefaultMessages);

    printMessage( PACKAGE);
    printMessage( VERSION);
    printMessage(argv[0]);

    if (verbose) {
        printMessage("command line arguments: ");
        for (int i = 0; i < argc; ++i) {
            printMessage(argv[i]);
        }
    }

    /*
     the starting default path to search for files is computed at
     run-time: it is
     the path of the binary + ".." + RELATIVEDATADIR
     this should make the package relocable (i.e., not stuck
     with a fixed installation directory).
     Of course, the GNU standards for installation directories
     should be followed, but this is not a problem if you use
     configure and make install features.
     If no path is specified in the running program we go back to
     the absolute datadir.
     */
    // this is defined in fileutil.cc
    string prefix_dir = get_file_path(argv[0]);
    if (prefix_dir.size())
        start_path = get_file_path(argv[0])+ RELATIVEDATADIR;
    else
        start_path = ABSOLUTEDATADIR;

    if (args_info.data_dir_given)
        data_dir = args_info.data_dir_arg;

    if (args_info.show_regex_given) {
        if (LangDefLoader::show_regex(data_dir, args_info.show_regex_arg)) {
            return (EXIT_SUCCESS);
        }

        return (EXIT_FAILURE);
    }

    if (args_info.check_lang_given) {
        cout << "checking " << args_info.check_lang_arg << "... ";
        if (LangDefLoader::check_lang_def(data_dir, args_info.check_lang_arg)) {
            cout << "OK" << endl;
            return (EXIT_SUCCESS);
        }

        return (EXIT_FAILURE);
    }

    if (args_info.check_outlang_given) {
        cout << "checking " << args_info.check_outlang_arg << "... ";
        textstyles = parse_outlang_def(data_dir.c_str(),
                args_info.check_outlang_arg);
        cout << "OK" << endl;
        return (EXIT_SUCCESS);
    }

    if (args_info.show_lang_elements_given) {
        // we simply printe all the language elements defined in the
        // language definition file
        if (LangDefLoader::show_lang_elements(data_dir,
                args_info.show_lang_elements_arg))
            return EXIT_SUCCESS;

        return EXIT_FAILURE;
    }

    string lang_map = args_info.lang_map_arg;
    assert(lang_map.size());
    if (! args_info.lang_def_given)
        langmap = LangMapPtr(new LangMap(data_dir, lang_map));

    string outlang_map = args_info.outlang_map_arg;
    assert(outlang_map.size());
    if (! args_info.outlang_def_given)
        outlangmap = LangMapPtr(new LangMap(data_dir, outlang_map));

    if (args_info.lang_list_given) {
        cout << "Supported languages (file extensions)\nand associated language definition files\n\n";
        langmap->print();
        return (EXIT_SUCCESS);
    }

    if (args_info.outlang_list_given) {
        cout << "Supported output languages\nand associated language definition files\n\n";
        outlangmap->print();
        return (EXIT_SUCCESS);
    }

    outputbuffer = new OutputBuffer;
    // when debugging, always flush the output
    outputbuffer->setAlwaysFlush(args_info.debug_langdef_given);

    string title;
    string doc_header;
    string doc_footer;
    string css_url;

    if (docTitle)
        title = docTitle;
    if ((! docTitle) && inputFileName.size())
        title = inputFileName;
    if (docHeader)
        doc_header = docHeader;
    if (docFooter)
        doc_footer = docFooter;
    if (cssUrl)
        css_url = cssUrl;

    if (args_info.line_number_ref_given)
        args_info.line_number_given = args_info.line_number_ref_given;

    string outlangfile;

    if (! args_info.outlang_def_given) {
        string out_format = args_info.out_format_arg;

        if (use_css)
            out_format += "-css";

        if (entire_doc)
            out_format += "-doc";

        outlangfile = outlangmap->get_file(out_format);

        if (! outlangfile.size()) {
            cerr << PACKAGE << ": ";
            cerr << "output language " << out_format<< " not handled" << endl;
            return EXIT_FAILURE;
        }
    } else {
        outlangfile = args_info.outlang_def_arg;
    }

    textstyles = parse_outlang_def(data_dir.c_str(), outlangfile.c_str());

    if (! textstyles->file_extension.size() && ! outputFileName.size()) {
        cerr << PACKAGE << ": ";
        cerr << "empty file extension in output language file " <<outlangfile << endl;
        return EXIT_FAILURE;
    }

    const string ext = "." + textstyles->file_extension;

    RefPosition refposition;
    if (strcmp(args_info.gen_references_arg, "inline")==0)
        refposition = INLINE;
    else if (strcmp(args_info.gen_references_arg, "postline")==0)
        refposition = POSTLINE;
    else if (strcmp(args_info.gen_references_arg, "postdoc")==0)
        refposition = POSTDOC;
    else {
        cerr << PACKAGE << ": ";
        cerr << "Bug: unhandled reference position " <<args_info.gen_references_arg << endl;
        return EXIT_FAILURE;
    }

    if (args_info.gen_references_given && strlen(args_info.ctags_arg)> 0) {
        string ctags_cmd = args_info.ctags_arg;

        if (inputFileName.size()) {
            ctags_cmd += " ";
            ctags_cmd += inputFileName;
        } else if (args_info.inputs_num) {
            for (i = 0; i < (args_info.inputs_num); ++i) {
                ctags_cmd += " ";
                ctags_cmd += args_info.inputs[i];
            }
        }

        run_ctags(ctags_cmd);
    }

    if (tabSpaces)
        preformatter = new Untabifier (tabSpaces);
    else if (args_info.line_number_given)
        preformatter = new Untabifier(8);
    else
        preformatter = new PreFormatter();

    PreFormatterPtr chartranslator(textstyles->charTranslator);
    preformatter->setFormatter(chartranslator);

    string background_color;

    generator_factory =new GeneratorFactory(textstyles, preformatter,
            args_info.gen_references_given,
            args_info.ctags_file_arg,
            refposition, args_info.debug_langdef_given);

    if (args_info.style_css_file_given) {
        parseCssStyles(data_dir, args_info.style_css_file_arg,
                generator_factory, background_color);
    } else {
        parseStyles(data_dir, style_file, generator_factory, background_color);
    }

    generator_factory->addDefaultGenerator();

    if (background_color != "")
        background_color = generator_factory->preprocessColor(background_color);

    docgenerator = new DocGenerator(title, inputFileName,
            doc_header, doc_footer,
            css_url, background_color, entire_doc,
            textstyles->docTemplate.toStringBegin(),
            textstyles->docTemplate.toStringEnd());;

    if (is_cgi)
        print_cgi_header();

    // let's start the translation :-)

    generate_line_num =(args_info.line_number_given || args_info.line_number_ref_given);
    generate_ref = args_info.line_number_ref_given;

    if (args_info.lang_def_arg)
        lang_file = args_info.lang_def_arg;

    int result= EXIT_SUCCESS;

    if (args_info.src_lang_given)
        source_language = args_info.src_lang_arg;

    // if a stopwatch is created, when it is deleted (automatically
    // since we're using a shared pointer, it will print the
    // elapsed seconds.
    boost::shared_ptr<StopWatch> stopwatch;
    if (args_info.statistics_given)
        stopwatch = boost::shared_ptr<StopWatch>(new StopWatch);

    // first the --input file
    if (! args_info.inputs_num) {
        result = processFile(inputFileName, (generate_to_stdout ? "" : outputFileName), ext);
    }

    // let's process other files, if there are any
    if (args_info.inputs_num && !is_cgi) {
        for (i = 0; i < (args_info.inputs_num); ++i) {
            progressInfo(string("Processing ")+ args_info.inputs[i] + " ... ");
            const string &outputFileName = createOutputFileName(
                    args_info.inputs[i], args_info.output_dir_arg, ext);
            result = processFile(args_info.inputs[i], (generate_to_stdout ? "" : outputFileName), ext);
            if (result == EXIT_FAILURE)
                break;
            progressInfo("created " + outputFileName + "\n");
        }
    }

    delete outputbuffer;
    outputbuffer = 0;

    return (result);
}

void StartApp::print_copyright() {
    int i;

    for (i = 1; i <= copyright_text_length; ++i)
        cout << copyright_text[i] << endl;
    ;
}

void StartApp::print_reportbugs() {
    int i;

    for (i = 1; i <= reportbugs_text_length; ++i)
        cout << reportbugs_text[i] << endl;
}

void StartApp::print_version() {
    cout << "GNU " << PACKAGE << " " << VERSION << endl;
}

int process_file(const char *file, TextFormatter *pre, const string &path,
        const string &lang_file, FileInfo *fileinfo, bool verbose) {
    RegExpStatePtr initial_state = LangDefLoader::get_lang_def(path, lang_file);

    try {
        printMessage("Processing " + string((file ? file : "standard input")) + " with regex");
        printMessage("Using language definition " + lang_file);
        RegExpEnginePtr engine;
        if (args_info.debug_langdef_given) {
            RegExpEngineDebug *debugEngine = new RegExpEngineDebug(initial_state, pre, fileinfo);
            debugEngine->setInteractive( strcmp(args_info.debug_langdef_arg, "interactive" ) == 0);
            engine = RegExpEnginePtr(debugEngine);
        } else {
            engine = RegExpEnginePtr(new RegExpEngine(initial_state, pre, fileinfo));
        }
        engine->process_file(file);
    }
    catch(...)
    {
        exitError("error during regex processing");
    }
    return 0;
}

string StartApp::inferLang(const string &inputFileName) {
    printMessage("inferring input language...", cerr);
    if (!inputFileName.size()) {
        cerr << PACKAGE << ": ";
        cerr << "missing feature: language inference requires input file" << endl;
        return "";
    }

    LanguageInfer languageInfer;

    const string &result = languageInfer.infer(inputFileName);
    if (result.size()) {
        printMessage("inferred input language: " + result, cerr);

        // OK now map it into a .lang file
        string mapped_lang = langmap->get_file(result);

        if (!mapped_lang.size()) {
            // try the lower version
            mapped_lang = langmap->get_file(Utils::tolower(result));
        }

        if (mapped_lang.size()) {
            return mapped_lang;
        }
    } else {
        printMessage("couldn't infer input language", cerr);
    }

    return "";
}

int StartApp::processFile(const string &inputFileName,
        const string &outputFileName, const string &file_extension) {
    FILE *in = 0;
    bool deleteOStream = false;
    bool langSpecFound = false;

    if (outputFileName.size()) {
        sout = new ofstream(outputFileName.c_str());
        if (! (*sout)) {
            cerr << "Error in creating " << outputFileName << " for output" << endl;
            return EXIT_FAILURE;
        }
        deleteOStream = true;
        printMessage("output file: " + inputFileName);
    }

    if (inputFileName.size()) {
        unsigned int lines = get_line_count(inputFileName);
        printMessage("input file: " + inputFileName);

        line_num_digit = 0;
        while (lines) {
            ++line_num_digit;
            lines /= 10;
        }
    } else
        line_num_digit = 5;
    // if we read from stdin, we can't read the file in advance and
    // check how many lines of code it contains.  In this case set
    // the number of digit for the line number to 5.

    /*
     * Use default values for any options not provided
     */
    if (sout == 0) {
        sout = &cout;
    }

    if (in == 0) {
        ; /* Well stdin already points to stdin so, .... */
    }

    OutputGenerator *outputgenerator = 0;

    if (generate_line_num) {
        // Read the padding character to use for line numbers
        line_num_padding = args_info.line_number_arg[0];
        outputgenerator =new OutputGenerator(*sout, generator_factory->getTextFormatter()->getGenerator("linenum"),
                &(textstyles->refstyle.anchor), generate_ref,
                (args_info.line_number_ref_given ? args_info.line_number_ref_arg : ""),
                textstyles->line_prefix);
    }
    else
        outputgenerator = new OutputGenerator(*sout, textstyles->line_prefix);

    // when debugging, always flush the output
    outputgenerator->setAlwaysFlush(args_info.debug_langdef_given);

    outputbuffer->setOutputGenerator(outputgenerator);

    docgenerator->set_gen_version(gen_version);

    printMessage("translating source code... ", cerr);

    string langfile = lang_file;

    if (args_info.infer_lang_given) {
        langfile = inferLang(inputFileName);

        if (langfile.size())
            langSpecFound = true;
    }

    // language inference has the precedence (if it succeeds)
    if (!langfile.size() && !langSpecFound) {
        // find the language definition file associated to a language
        if (source_language.size()) {
            langfile = langmap->get_file(source_language);
            if (! langfile.size()) {
                if (! args_info.failsafe_given) {
                    cerr << PACKAGE << ": ";
                    cerr << "source language " << source_language<< " not handled" << endl;
                    return EXIT_FAILURE;
                }
            } else
                langSpecFound = true;
        } else {
            if (! inputFileName.size()) {
                if (! args_info.failsafe_given) {
                    cerr << PACKAGE << ": ";
                    cerr << "when using stdin, please specify a source language"<< endl;
                    return EXIT_FAILURE;
                }
            }

            string file_ext = get_file_extension(inputFileName);

            if (file_ext != "")
                langfile = langmap->get_file(file_ext);

            if (langfile.size())
                langSpecFound = true;
        }
    } else
        langSpecFound = true;

    // language inference is always performed, if the other attempts failed
    // if --infer-lang was specified at command line, then the inference
    // has already been performed, otherwise we perform it now
    if (!langSpecFound && !args_info.infer_lang_given) {
        langfile = inferLang(inputFileName);

        if (langfile.size())
            langSpecFound = true;
    }

    if (!langSpecFound && args_info.failsafe_given) {
        // OK we use default.lang
        langfile = "default.lang";
        langSpecFound = true;
    }

    if (langSpecFound) {
        docgenerator->generate_start_doc();

        const string &i_file_name = get_input_file_name(inputFileName);
        const char *input_file_name = (i_file_name.size() ? i_file_name.c_str() : 0);

        FileInfo fileinfo(i_file_name, outputFileName);
        process_file(input_file_name, generator_factory->getTextFormatter(),
                data_dir, langfile, &fileinfo, verbose);

        outputbuffer->flush();

        docgenerator->generate_end_doc();

        printMessage("done !", cerr);
    } else {
        cerr << PACKAGE << ": ";
        cerr << "unknown input language for "<< (inputFileName.size() ? inputFileName : "(stdin)") << endl;
        return EXIT_FAILURE;
    }

    /*
     else // we're in failsafe mode so we simply copy the file to the output
     {
     istream *input;
     if(! inputFileName.size())
     input = &cin;
     else
     input = open_file_istream_or_error(inputFileName);

     *sout << input->rdbuf();

     if (input != &cin)
     delete input;
     }
     */

    sout->flush();

    if (deleteOStream)
        delete sout;

    delete outputgenerator;

    return EXIT_SUCCESS;
}

void run_ctags(const string &cmd) {
    printMessage("Running ctags: " + cmd);

    int res = system(cmd.c_str());

    if (res != 0) {
        exitError("error running ctags");
    }
}

void print_cgi_header() {
    printf("Content-type: text/html\n");
    printf("\n");
}

