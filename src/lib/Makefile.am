# Copyright (C) 1999-2008 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SUBDIRS = tests

SUFFIXES = .text .hpp .h

.text.c:
	$(TXTC) -c $<

if NO_DOUBLECPP
.h.hpp:
	touch $@
else
.h.hpp:
	$(DOUBLECPP) --output-source-ext cc --invade-target --input-header-ext h --output-header-ext hpp --output-source-suff=_dbtab --verbose --assume-virtual -i $<
	touch $@
endif

AM_CPPFLAGS = -I$(top_srcdir)/gl -I$(top_builddir)/gl $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_LDFLAGS)

LDADD = @LEXLIB@ $(top_builddir)/gl/libgnu.la

noinst_LTLIBRARIES = libcommon.la librules.la libregexrules.la \
	libformatter.la libhighlighter.la libhighlighterbuilder.la \
	liblangelem.la libshformatter.la liblangdef.la \
	libsrchilite.la

libcommon_la_SOURCES = copyright.text reportbugs.text \
	fileutil.cc \
	substfun.cpp \
	stopwatch.cpp utils.cpp utils.h \
	ioexception.cpp

noinst_HEADERS = parsestyles.h \
	stringdef.h langelem.h \
	statelangelem.h langelems.h langdefparserfun.h outlangdefparserfun.h \
	tostringcollection.h regexpreprocessor.h \
	langdefscanner.h outlangdefscanner.h parsestruct.h langmap.h statestartlangelem.h \
	stringlistlangelem.h delimitedlangelem.h vardefinitions.h textstyle.h \
	textstyles.h textstylebuilder.h doctemplate.h substfun.h \
	parserinfo.h readtags.h fileinfo.h linebuffer.h preformatter.h \
	langelemsprinter.h languageinfer.h stopwatch.h stylekey.h \
	namedsubexpslangelem.h refposition.h \
	highlightrule.h highlighttoken.h highlightrulefactory.h highlightstate.h \
	regexhighlightrule.h regexrulefactory.h \
	highlightstateprinter.h sourcehighlighter.h matchingparameters.h \
	formatter.h formattermanager.h \
	highlightstatebuilder.h highlightbuilderexception.h \
	wordtokenizer.h ctagscollector.h formatterparams.h ctagsformatter.h \
	sourcefilehighlighter.h linenumgenerator.h \
	textstyleformatter.h textstyleformatterfactory.h \
	langdefmanager.h sourcehighlight.h \
	textstyleformattercollection.h \
	ioexception.h parserexception.h stringtable.h \
	verbose.h eventgenerator.h highlightevent.h highlighteventlistener.h \
	debuglistener.h ctagsmanager.h bufferedoutput.h lineranges.h

liblangelem_la_SOURCES = langelem.cpp statelangelem.cpp \
	langelems.cpp statestartlangelem.cpp stringlistlangelem.cpp \
	delimitedlangelem.cpp langelemsprinter.cpp langelemsprinter.hpp langelemsprinter_dbtab.cc \
	namedsubexpslangelem.cpp stringdef.cpp

librules_la_SOURCES = highlightrule.cpp highlighttoken.cpp \
	highlightstate.cpp highlightrulefactory.cpp highlightstateprinter.cpp

libhighlighter_la_SOURCES = sourcehighlighter.cpp sourcefilehighlighter.cpp \
	linenumgenerator.cpp lineranges.cpp
libhighlighter_la_LIBADD = $(BOOST_REGEX_LIB) ./libformatter.la ./libcommon.la

libformatter_la_SOURCES = formatter.cpp formattermanager.cpp

libshformatter_la_SOURCES = textstyle.cpp textstyleformatter.cpp bufferedoutput.cpp \
	preformatter.cpp wordtokenizer.cpp ctagscollector.cpp readtags.c ctagsformatter.cpp \
	srcuntabifier.cpp textstyleformatterfactory.cpp \
	docgenerator.cc doctemplate.cpp chartranslator.cc \
	textstylebuilder.cpp fileinfo.cpp ctagsmanager.cpp
libshformatter_la_LIBADD = $(BOOST_REGEX_LIB) ./libformatter.la ./libcommon.la

libregexrules_la_SOURCES = regexhighlightrule.cpp regexrulefactory.cpp \
	regexpreprocessor.cpp
libregexrules_la_LIBADD = $(BOOST_REGEX_LIB) ./librules.la

libhighlighterbuilder_la_SOURCES = highlightstatebuilder.cpp highlightstatebuilder.hpp \
	highlightstatebuilder_dbtab.cc highlightbuilderexception.cpp langdefmanager.cpp
libhighlighterbuilder_la_LIBADD = ./libregexrules.la ./liblangdef.la

libcommon_la_LIBADD = $(BOOST_REGEX_LIB)

liblangdef_la_SOURCES = langdefparser.yy langdefscanner.ll \
	languageinfer.cpp \
	parserexception.cpp \
	stringtable.cpp vardefinitions.cpp
liblangdef_la_LIBADD = ./libcommon.la ./liblangelem.la

libsrchilite_la_SOURCES = sourcehighlight.cpp styleparser.yy \
	stylescanner.ll outlangdefparser.yy \
	stylecssparser.yy stylecssscanner.ll outlangdefscanner.ll \
	debuglistener.cpp langmap.cpp
libsrchilite_la_LIBADD = ./libshformatter.la \
	./libhighlighter.la ./libhighlighterbuilder.la

INCLUDES = -I@top_srcdir@/src

EXTRA_DIST = colors.h \
             keys.h styleparser.h stylecssparser.h \
             tokens.h fileutil.h \
             chartranslator.h my_sstream.h \
             docgenerator.h \
             copyright.h reportbugs.h \
             srcuntabifier.h colormap.h \
             langdefparser.h outlangdefparser.h

BUILT_SOURCES = styleparser.cc styleparser.h \
stylecssparser.cc stylecssparser.h \
stylescanner.cc stylecssscanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
langelemsprinter.hpp langelemsprinter_dbtab.cc \
highlightstatebuilder.hpp highlightstatebuilder_dbtab.cc

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

if !NO_CTAGS
EXTRA_PROGRAMS = test_readtags
endif

test_readtags_SOURCES = test_readtags_main.cpp readtags.h
test_readtags_DEPENDENCIES = mytags
test_readtags_LDADD = readtags.$(OBJEXT)

mytags: $(srcdir)/test_readtags_main.cpp
	$(CTAGS) --excmd=n --fields=+n -o mytags $(srcdir)/test_readtags_main.cpp $(srcdir)/readtags.h

DISTCLEANFILES = mytags copyright.c reportbugs.c

MAINTAINERCLEANFILES = styleparser.cc styleparser.h stylescanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
outlangdefparser.cc outlangdefparser.h outlangdefscanner.cc


