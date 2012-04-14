# Copyright (C) 1999-2008 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AM_CPPFLAGS = \
	-I$(top_srcdir)/gl \
	-I$(top_builddir)/gl \
	-I$(top_srcdir)/src -I$(srcdir)/..
	$(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_LDFLAGS) -no-install

LDADD = $(top_builddir)/gl/libgnu.la $(LIBDIR)/libsource-highlight.la $(BOOST_REGEX_LIB)

#LIBDIR = $(top_builddir)/lib/srchilite/
LIBDIR = ../srchilite/

VALGRIND_TESTS = test_regexrules test_formatter_manager test_highlighter \
	test_exception test_highlightbuilder test_buffered_output \
	test_textstyle test_textgenerator test_textstyleformatter test_wordtokenizer test_linenum \
	test_sourcefilehighlighter test_textstyleformatterfactory \
	test_langdefmanager test_sourcehighlight test_sourcehighlight_errors test_langinfer \
	test_untabifier test_outlangparser test_outlang_errors test_events test_debuglistener \
	test_regexpreprocessor test_filenotfound test_style_errors \
	test_lineranges test_regexranges test_settings test_langmap \
	test_utils test_instances

if !NO_CTAGS
VALGRIND_TESTS += test_ctagscollector test_ctagsformatter test_ctagsmanager \
	test_formatreferences
endif

TESTS = $(VALGRIND_TESTS) test_sourcehighlight_errors
check_PROGRAMS = $(TESTS)

test_regexrules_SOURCES = test_regexrules_main.cpp

test_formatter_manager_SOURCES = test_formatter_manager_main.cpp

test_highlighter_SOURCES = logformatter.cpp test_highlighter_main.cpp

test_exception_SOURCES = test_exception_main.cpp

test_highlightbuilder_SOURCES = logformatter.cpp test_highlightbuilder_main.cpp

test_buffered_output_SOURCES = test_buffered_output_main.cpp

test_textstyle_SOURCES = test_textstyle_main.cpp 

test_textstyleformatter_SOURCES = test_textstyleformatter_main.cpp

test_textgenerator_SOURCES = test_textgenerator_main.cpp 

test_wordtokenizer_SOURCES = test_wordtokenizer_main.cpp

test_ctagscollector_SOURCES = test_ctagscollector_main.cpp
test_ctagscollector_DEPENDENCIES = mytags
test_ctagscollector_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/lib/srchilite/\""

test_ctagsformatter_SOURCES = test_ctagsformatter_main.cpp
test_ctagsformatter_DEPENDENCIES = mytags
test_ctagsformatter_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/lib/srchilite/\""

test_ctagsmanager_SOURCES = test_ctagsmanager_main.cpp
test_ctagsmanager_DEPENDENCIES = mytags
test_ctagsmanager_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/lib/srchilite/\"" -D CTAGS="\"$(CTAGS)\""

test_formatreferences_SOURCES = logformatter.cpp test_formatreferences_main.cpp
test_formatreferences_DEPENDENCIES = mytags
test_formatreferences_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/lib/srchilite/\""

test_untabifier_SOURCES = test_untabifier_main.cpp

test_sourcefilehighlighter_SOURCES = test_sourcefilehighlighter_main.cpp

test_lineranges_SOURCES = test_lineranges_main.cpp

test_regexranges_SOURCES = test_regexranges_main.cpp

test_debuglistener_SOURCES = test_debuglistener_main.cpp

test_linenum_SOURCES = test_linenum_main.cpp

test_textstyleformatterfactory_SOURCES = test_textstyleformatterfactory_main.cpp

test_langdefmanager_SOURCES = test_langdefmanager_main.cpp
test_langdefmanager_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\""

test_sourcehighlight_SOURCES = test_sourcehighlight_main.cpp
test_sourcehighlight_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_sourcehighlight_errors_SOURCES = test_sourcehighlight_errors_main.cpp
test_sourcehighlight_errors_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_style_errors_SOURCES = test_style_errors_main.cpp
test_style_errors_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_outlang_errors_SOURCES = test_outlang_errors_main.cpp
test_outlang_errors_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_filenotfound_SOURCES = test_filenotfound_main.cpp
test_filenotfound_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_outlangparser_SOURCES = test_outlangparser_main.cpp
test_outlangparser_DEPENDENCIES = outlangtest.outlang
test_outlangparser_CXXFLAGS = -D BASEDIR="\"$(srcdir)/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_langinfer_SOURCES = test_langinfer_main.cpp

test_settings_SOURCES = test_settings_main.cpp
test_settings_CXXFLAGS = -D BASEDIR="\"$(srcdir)/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\"" \
	-D MAINSRCDIR="\"$(top_srcdir)/src/\""

test_events_SOURCES = test_events_main.cpp

test_regexpreprocessor_SOURCES = test_regexpreprocessor_main.cpp

test_langmap_SOURCES = test_langmap_main.cpp 
test_langmap_CXXFLAGS = -D BASEDIR="\"$(srcdir)/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""

test_utils_SOURCES = test_utils_main.cpp
test_utils_CXXFLAGS = -D BASEDIR="\"$(top_srcdir)/src/\""

test_instances_SOURCES = test_instances_main.cpp
test_instances_CXXFLAGS = -D BASEDIR="\"$(srcdir)/\"" -D TESTSDIR="\"$(top_srcdir)/tests/\""


mytags: $(top_srcdir)/lib/srchilite/test_readtags_main.cpp
	$(CTAGS) --excmd=n --fields=+n -o mytags $(top_srcdir)/lib/srchilite/test_readtags_main.cpp $(top_srcdir)/lib/srchilite/readtags.h

check_test_regexpreprocessor: test_regexpreprocessor$(EXEEXT)
	./test_regexpreprocessor$(EXEEXT)

check_test_regexrules: test_regexrules$(EXEEXT)
	./test_regexrules$(EXEEXT)

check_test_formatter_manager: test_formatter_manager$(EXEEXT)
	./test_formatter_manager$(EXEEXT)

check_test_highlighter: test_highlighter$(EXEEXT)
	./test_highlighter$(EXEEXT)

check_test_exception: test_exception$(EXEEXT)
	./test_exception$(EXEEXT)

check_test_highlightbuilder: test_highlightbuilder$(EXEEXT)
	./test_highlightbuilder$(EXEEXT)

check_test_buffered_output: test_buffered_output$(EXEEXT)
	./test_buffered_output$(EXEEXT)

check_test_textstyleformatter: test_textstyleformatter$(EXEEXT)
	./test_textstyleformatter$(EXEEXT)

check_test_textstyle: test_textstyle$(EXEEXT)
	./test_textstyle$(EXEEXT)

check_test_textgenerator: test_textgenerator$(EXEEXT)
	./test_textgenerator$(EXEEXT)

check_test_wordtokenizer: test_wordtokenizer$(EXEEXT)
	./test_wordtokenizer$(EXEEXT)

check_test_ctagscollector: test_ctagscollector$(EXEEXT)
	./test_ctagscollector$(EXEEXT)

check_test_ctagsformatter: test_ctagsformatter$(EXEEXT)
	./test_ctagsformatter$(EXEEXT)

check_test_ctagsmanager: test_ctagsmanager$(EXEEXT)
	./test_ctagsmanager$(EXEEXT)

check_test_formatreferences: test_formatreferences$(EXEEXT)
	./test_formatreferences$(EXEEXT)

check_test_sourcefilehighlighter: test_sourcefilehighlighter$(EXEEXT)
	./test_sourcefilehighlighter$(EXEEXT) 

check_test_linenum: test_linenum$(EXEEXT)
	./test_linenum$(EXEEXT)

check_test_textstyleformatterfactory: test_textstyleformatterfactory$(EXEEXT)
	./test_textstyleformatterfactory$(EXEEXT)

check_test_langdefmanager: test_langdefmanager$(EXEEXT)
	./test_langdefmanager$(EXEEXT)

check_test_sourcehighlight: test_sourcehighlight$(EXEEXT)
	./test_sourcehighlight$(EXEEXT) 

check_test_sourcehighlight_errors: test_sourcehighlight_errors$(EXEEXT)
	./test_sourcehighlight_errors$(EXEEXT) 

check_test_style_errors: test_style_errors$(EXEEXT)
	./test_style_errors$(EXEEXT) 

check_test_outlang_errors: test_outlang_errors$(EXEEXT)
	./test_outlang_errors$(EXEEXT) 

check_test_filenotfound: test_filenotfound$(EXEEXT)
	./test_filenotfound$(EXEEXT) 

check_test_outlangparser: test_outlangparser$(EXEEXT)
	./test_outlangparser$(EXEEXT) 

check_test_langinfer: test_langinfer$(EXEEXT)
	./test_langinfer$(EXEEXT) 

check_test_untabifier: test_untabifier$(EXEEXT)
	./test_untabifier$(EXEEXT)

check_test_events: test_events$(EXEEXT)
	./test_events$(EXEEXT)

check_test_debuglistener: test_debuglistener$(EXEEXT)
	./test_debuglistener$(EXEEXT)

check_test_lineranges: test_lineranges$(EXEEXT)
	./test_lineranges$(EXEEXT)

check_test_regexranges: test_regexranges$(EXEEXT)
	./test_regexranges$(EXEEXT)

check_test_settings: test_settings$(EXEEXT)
	./test_settings$(EXEEXT)

check_test_langmap: test_langmap$(EXEEXT)
	./test_langmap$(EXEEXT)

check_test_utils: test_utils$(EXEEXT)
	./test_utils$(EXEEXT)	

check_test_instances: test_instances$(EXEEXT)
	./test_instances$(EXEEXT)	

VALGRINDTEST = $(builddir)/valgrind_test.sh

check-valgrind: $(VALGRIND_TESTS)
	for prog in $(VALGRIND_TESTS); do \
		$(VALGRINDTEST) ./$$prog ; \
	done ;

EXTRA_DIST = valgrind_test.sh.in \
	outlangtest.outlang \
	testconffile.conf \
	source-highlight.conf \
	test.map

noinst_HEADERS = logformatter.h stdboosterror.h asserttestexit.h 

CLEANFILES = *.java.html mytags*