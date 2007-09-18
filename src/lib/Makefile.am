# Copyright (C) 1999-2007 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SUFFIXES = .text .H .h

.text.c:
	$(TXTC) -c $<

if NO_DOUBLECPP
.h.H:
	touch $@
else
.h.H:
	$(DOUBLECPP) --output-source-ext cc --invade-target --input-header-ext h --output-header-ext H --output-source-suff=_dbtab --verbose --assume-virtual -i $<
	touch $@
endif

AM_CPPFLAGS = -I$(top_srcdir)/gl -I$(top_builddir)/gl

LDADD = @LEXLIB@ $(top_builddir)/gl/libgnu.la

noinst_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = copyright.text reportbugs.text messages.cc \
	fileutil.cc chartranslator.cc generatorfactory.cc docgenerator.cc styleparser.yy \
	stylescanner.ll langdefparser.yy langdefscanner.ll outlangdefparser.yy \
	stylecssparser.yy stylecssscanner.ll outlangdefscanner.ll srcuntabifier.cpp \
	textformatter.cpp outputbuffer.cpp outputgenerator.cpp \
	mainoutputbuffer.cpp statelangelem.cpp \
	langelems.cpp regexpreprocessor.cpp regexpstatebuilder.H regexpstatebuilder_dbtab.cc \
	regexpstatebuilder.cpp langdefloader.cpp langmap.cpp statestartlangelem.cpp \
	stringlistlangelem.cpp delimitedlangelem.cpp vardefinitions.cpp \
	textstyle.cpp textgenerator.cpp textstylebuilder.cpp doctemplate.cpp substfun.cpp \
	readtags.c fileinfo.cpp preformatter.cpp \
	regexpstateprinter.cpp langelemsprinter.cpp langelemsprinter.H langelemsprinter_dbtab.cc \
	languageinfer.cpp stopwatch.cpp utils.cpp utils.h \
	regexpengine.cpp regexpstate.cpp regexpenginedebug.cpp \
	namedsubexpslangelem.cpp stringdef.cpp

libcommon_la_LIBADD = $(BOOST_REGEX_LIB)

INCLUDES = -I@top_srcdir@/src

EXTRA_DIST = colors.h generatorfactory.h \
             keys.h styleparser.h stylecssparser.h \
             tokens.h messages.h fileutil.h \
             chartranslator.h my_sstream.h \
             linenumdigit.h globalostream.h \
             docgenerator.h \
             copyright.h reportbugs.h \
             srcuntabifier.h colormap.h \
             langdefparser.h outlangdefparser.h \
             outlangtest.outlang.tmpl

BUILT_SOURCES = styleparser.cc styleparser.h \
stylecssparser.cc stylecssparser.h \
stylescanner.cc stylecssscanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
regexpstatebuilder.H regexpstatebuilder_dbtab.cc \
langelemsprinter.H langelemsprinter_dbtab.cc

langdefscanner.cc: $(srcdir)/langdefscanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/langdefscanner.ll

langdefparser.cc: $(srcdir)/langdefparser.yy
	$(YACC) -p langdef_ -o $@ $(srcdir)/langdefparser.yy --defines=$*.h

langdefparser.h: langdefparser.cc

outlangdefscanner.cc: $(srcdir)/outlangdefscanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/outlangdefscanner.ll

outlangdefparser.cc outlangdefparser.h: $(srcdir)/outlangdefparser.yy
	$(YACC) -p outlangdef_ -o $@ $(srcdir)/outlangdefparser.yy --defines=$*.h

stylescanner.cc: $(srcdir)/stylescanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/stylescanner.ll

stylecssscanner.cc: $(srcdir)/stylecssscanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/stylecssscanner.ll

styleparser.cc styleparser.h: $(srcdir)/styleparser.yy
	$(YACC) -p stylesc_ -o $@ $(srcdir)/styleparser.yy --defines=$*.h

stylecssparser.cc stylecssparser.h: $(srcdir)/stylecssparser.yy
	$(YACC) -p stylecsssc_ -o $@ $(srcdir)/stylecssparser.yy --defines=$*.h

TESTS = test_textstyle test_textgenerator test_outlangparser \
test_langinfer test_regexpreprocessor

check_PROGRAMS = test_langdefparser test_langmap test_textstyle test_textgenerator test_outlangparser test_langinfer test_regexpreprocessor

if !NO_CTAGS
TESTS += test_readtags
check_PROGRAMS += test_readtags
endif


test_langdefparser_SOURCES = test_langdefparser_main.cpp
test_langdefparser_LDADD = libcommon.la

test_langmap_SOURCES = test_langmap_main.cpp 
test_langmap_LDADD = langmap.$(OBJEXT) fileutil.$(OBJEXT) messages.$(OBJEXT) $(BOOST_REGEX_LIB)

test_textstyle_SOURCES = test_textstyle_main.cpp 
test_textstyle_LDADD = $(BOOST_REGEX_LIB) textstyle.$(OBJEXT) substfun.$(OBJEXT)

test_textgenerator_SOURCES = test_textgenerator_main.cpp 
test_textgenerator_LDADD = libcommon.la textstylebuilder.$(OBJEXT)

test_outlangparser_SOURCES = test_outlangparser_main.cpp
test_outlangparser_DEPENDENCIES = outlangtest.outlang
test_outlangparser_LDADD = libcommon.la textstyle.$(OBJEXT)

test_readtags_SOURCES = test_readtags_main.cpp readtags.h
test_readtags_DEPENDENCIES = mytags
test_readtags_LDADD = readtags.$(OBJEXT)

test_langinfer_SOURCES = test_langinfer.cpp
test_langinfer_LDADD = libcommon.la

test_regexpreprocessor_SOURCES = test_regexpreprocessor_main.cpp
test_regexpreprocessor_LDADD = $(BOOST_REGEX_LIB) stringdef.$(OBJEXT) \
regexpreprocessor.$(OBJEXT) 

check_test_regexpreprocessor: test_regexpreprocessor$(EXEEXT)
	./test_regexpreprocessor$(EXEEXT)

mytags: $(srcdir)/test_readtags_main.cpp
	$(CTAGS) --excmd=n --fields=+n -o mytags $(srcdir)/test_readtags_main.cpp $(srcdir)/readtags.h

outlangtest.outlang: $(srcdir)/outlangtest.outlang.tmpl
	rm -f outlangtest.outlang
	cp -f $(srcdir)/outlangtest.outlang.tmpl outlangtest.outlang

DISTCLEANFILES = outlangtest.outlang mytags copyright.c reportbugs.c

MAINTAINERCLEANFILES = styleparser.cc styleparser.h stylescanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
outlangdefparser.cc outlangdefparser.h outlangdefscanner.cc

noinst_HEADERS = parsestyles.h textformatter.h outputbuffer.h \
	outputgenerator.h mainoutputbuffer.h stringdef.h langelem.h \
	statelangelem.h langelems.h langdefparserfun.h outlangdefparserfun.h \
	tostringcollection.h regexpreprocessor.h regexpstatebuilder.h langdefloader.h \
	langdefscanner.h outlangdefscanner.h parsestruct.h langmap.h statestartlangelem.h \
	stringlistlangelem.h delimitedlangelem.h vardefinitions.h textstyle.h \
	textstyles.h textgenerator.h textstylebuilder.h doctemplate.h substfun.h \
	parserinfo.h readtags.h fileinfo.h linebuffer.h preformatter.h \
	regexpstateprinter.h langelemsprinter.h languageinfer.h stopwatch.h stylekey.h \
	regexpengine.h regexpstate.h regexpenginedebug.h \
	namedsubexpslangelem.h refposition.h


