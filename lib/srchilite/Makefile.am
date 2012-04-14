# Copyright (C) 1999-2009 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

#SUBDIRS = includes

if NO_DOUBLECPP

else

SUFFIXES = .hpp .h

# we need to put doublecpp generated files in the srcdir
# since we want to distribute them

.h.hpp:
	cd $(srcdir) && \
	$(DOUBLECPP) --output-source-ext cc --invade-target --input-header-ext h --output-header-ext hpp --output-source-suff=_dbtab --verbose --assume-virtual -i $(notdir $<)
	touch $@
endif

# for doxygen documentation
if HAVE_DOXYGEN
DOXYFILE=$(builddir)/srchilite.doxyfile

help_dir=$(htmldir)/api

doxygen.stamp: $(DOXYFILE)
	$(DOXYGEN) $(DOXYFLAGS) $<
	echo Timestamp > $@

## This rule requires Autoconf 2.62 or newer.
install-data-local: doxygen.stamp
	@$(NORMAL_INSTALL)
	$(MKDIR_P) $(DESTDIR)$(help_dir)
	$(INSTALL_DATA) $(builddir)/html/* $(DESTDIR)$(help_dir)

## Warning: the following rule assumes that this package is the
## sole owner of files below $(help_dir)!
uninstall-local:
	@$(NORMAL_UNINSTALL)
	rm -f $(DESTDIR)$(help_dir)/*

clean-local:
	rm -f $(builddir)/html/*
endif

AM_CPPFLAGS = -I$(top_srcdir)/gl -I$(top_builddir)/gl -I$(top_srcdir)/src $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_LDFLAGS)

LDADD = $(top_builddir)/gl/libgnu.la

lib_LTLIBRARIES = libsource-highlight.la

libsource_highlight_la_SOURCES = \
	fileutil.cc \
	substfun.cpp \
	stopwatch.cpp utils.cpp \
	ioexception.cpp \
	settings.cpp \
	versions.cpp \
	verbosity.cpp \
	sourcehighlight.cpp styleparser.cc \
	stylescanner.cc outlangdefparser.cc \
	stylecssparser.cc stylecssscanner.cc outlangdefscanner.cc \
	debuglistener.cpp langmap.cpp stylefileparser.cpp \
	langelem.cpp statelangelem.cpp \
	langelems.cpp statestartlangelem.cpp stringlistlangelem.cpp \
	delimitedlangelem.cpp langelemsprinter.cpp langelemsprinter.hpp \
	namedsubexpslangelem.cpp stringdef.cpp \
	highlightrule.cpp highlighttoken.cpp \
	highlightstate.cpp highlightrulefactory.cpp highlightstateprinter.cpp \
	sourcehighlighter.cpp sourcefilehighlighter.cpp \
	linenumgenerator.cpp lineranges.cpp regexranges.cpp \
	formatter.cpp formattermanager.cpp \
	textstyle.cpp textstyleformatter.cpp bufferedoutput.cpp \
	preformatter.cpp wordtokenizer.cpp ctagscollector.cpp readtags.c ctagsformatter.cpp \
	srcuntabifier.cpp textstyleformatterfactory.cpp \
	docgenerator.cc doctemplate.cpp chartranslator.cc \
	textstylebuilder.cpp fileinfo.cpp ctagsmanager.cpp \
	regexhighlightrule.cpp regexrulefactory.cpp \
	regexpreprocessor.cpp \
	highlightstatebuilder.cpp highlightstatebuilder.hpp \
	highlightbuilderexception.cpp langdefmanager.cpp \
	langdefparser.cc langdefscanner.cc \
	languageinfer.cpp \
	parserexception.cpp \
	stringtable.cpp vardefinitions.cpp \
	sourcehighlightutils.cpp \
	instances.cpp

libsource_highlight_la_LIBADD = $(top_builddir)/gl/libgnu.la \
	@LTLIBOBJS@ $(BOOST_REGEX_LIB)

libsource_highlight_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(LIBRARY_VERSION)

library_includedir=$(includedir)/$(LIBRARY_NAMESPACE)
library_include_HEADERS = $(h_sources)

h_sources = parsestyles.h \
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
	textstyleformatter.h formatterfactory.h textstyleformatterfactory.h \
	langdefmanager.h sourcehighlight.h \
	textstyleformattercollection.h \
	ioexception.h parserexception.h stringtable.h \
	eventgenerator.h highlightevent.h highlighteventlistener.h \
	debuglistener.h ctagsmanager.h bufferedoutput.h lineranges.h regexranges.h \
	colors.h \
             keys.h styleparser.h stylecssparser.h \
             fileutil.h \
             chartranslator.h \
             docgenerator.h \
             srcuntabifier.h colormap.h \
             langdefparser.h outlangdefparser.h \
             stylefileparser.h \
             settings.h \
             versions.h \
             verbosity.h \
             sourcehighlightutils.h utils.h \
             instances.h

EXTRA_DIST = $(h_sources) \
langelemsprinter_dbtab.cc \
highlightstatebuilder_dbtab.cc \
srchilite.doxyfile.in \
srchilite.pro \
styleparser.yy \
stylescanner.ll outlangdefparser.yy \
stylecssparser.yy stylecssscanner.ll outlangdefscanner.ll \
langdefparser.yy langdefscanner.ll

BUILT_SOURCES = \
langdefparser.cc langdefparser.h langdefscanner.cc \
outlangdefparser.cc outlangdefparser.h outlangdefscanner.cc \
styleparser.cc styleparser.h \
stylecssparser.cc stylecssparser.h \
stylescanner.cc stylecssscanner.cc \
langelemsprinter.hpp langelemsprinter_dbtab.cc \
highlightstatebuilder.hpp highlightstatebuilder_dbtab.cc

langdefscanner.cc: $(srcdir)/langdefscanner.ll
	$(LEX) $(LFLAGS) -o $(srcdir)/langdefscanner.cc $(srcdir)/langdefscanner.ll

langdefparser.cc: $(srcdir)/langdefparser.yy
	$(YACC) -p langdef_ -o $(srcdir)/langdefparser.cc $(srcdir)/langdefparser.yy --defines=$(srcdir)/langdefparser.h

langdefparser.h: langdefparser.cc

outlangdefscanner.cc: $(srcdir)/outlangdefscanner.ll
	$(LEX) $(LFLAGS) -o $(srcdir)/outlangdefscanner.cc $(srcdir)/outlangdefscanner.ll

outlangdefparser.cc outlangdefparser.h: $(srcdir)/outlangdefparser.yy
	$(YACC) -p outlangdef_ -o $(srcdir)/outlangdefparser.cc $(srcdir)/outlangdefparser.yy --defines=$(srcdir)/outlangdefparser.h

stylescanner.cc: $(srcdir)/stylescanner.ll
	$(LEX) $(LFLAGS) -o $(srcdir)/stylescanner.cc $(srcdir)/stylescanner.ll

stylecssscanner.cc: $(srcdir)/stylecssscanner.ll
	$(LEX) $(LFLAGS) -o $(srcdir)/stylecssscanner.cc $(srcdir)/stylecssscanner.ll

styleparser.cc styleparser.h: $(srcdir)/styleparser.yy
	$(YACC) -p stylesc_ -o $(srcdir)/styleparser.cc $(srcdir)/styleparser.yy --defines=$(srcdir)/styleparser.h

stylecssparser.cc stylecssparser.h: $(srcdir)/stylecssparser.yy
	$(YACC) -p stylecsssc_ -o $(srcdir)/stylecssparser.cc $(srcdir)/stylecssparser.yy --defines=$(srcdir)/stylecssparser.h

if !NO_CTAGS
EXTRA_PROGRAMS = test_readtags
endif

test_readtags_SOURCES = test_readtags_main.cpp readtags.h
test_readtags_DEPENDENCIES = mytags
test_readtags_LDADD = readtags.$(OBJEXT)

mytags: $(srcdir)/test_readtags_main.cpp
	$(CTAGS) --excmd=n --fields=+n -o mytags $(srcdir)/test_readtags_main.cpp $(srcdir)/readtags.h

CLEANFILES = doxygen.stamp

DISTCLEANFILES = mytags

MAINTAINERCLEANFILES = styleparser.cc styleparser.h stylescanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
outlangdefparser.cc outlangdefparser.h outlangdefscanner.cc


