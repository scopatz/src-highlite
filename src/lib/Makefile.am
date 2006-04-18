# Copyright (C) 1999-2006 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SUFFIXES = .text .ggo

.cc.stamp:
	sed -f $(srcdir)/$*.sed $< > __temp.cc
	cp -f __temp.cc $<
	rm -f __temp.cc
	if test -f $*.h ; then \
	sed -f $(srcdir)/$*.sed $*.h > __temp.h ;\
	cp -f __temp.h $*.h ;\
	rm -f __temp.h ;\
	else :; fi
	echo timestamp > $@

.text.o:
	$(TXTC) $<

if NO_GENGETOPT
.ggo.c:
	touch $@
else
.ggo.c:
	$(GENGETOPT) --input $< --unamed-opts --no-handle-help --no-handle-version
endif

if NO_DOUBLECPP
$(srcdir)/%.H: $(srcdir)/%.h
	touch $@
else
$(srcdir)/%.H: $(srcdir)/%.h
	$(DOUBLECPP) --output-source-ext cc --invade-target --input-header-ext h --output-header-ext H --output-source-suff=_dbtab --verbose --assume-virtual -i $<
	touch $@
endif

noinst_LIBRARIES = libcommon.a
EXTRA_LIBRARIES = libcgi.a

libcommon_a_AR = @ar_to_use@
libcommon_a_SOURCES = copyright.text reportbugs.text cmdline.c styles.cc \
		messages.cc fileutil.cc chartranslator.cc generatorfactory.cc docgenerator.cc \
		optparser.yy optscanner.ll langdefparser.yy langdefscanner.ll outlangdefparser.yy \
		outlangdefscanner.ll srcuntabifier.cpp generatormap.cpp maingeneratormap.cpp \
		outputbuffer.cpp outputgenerator.cpp mainoutputbuffer.cpp lineoutputgenerator.cpp \
		stringdef.cpp langelem.cpp statelangelem.cpp langelems.cpp regexpreprocessor.cpp \
		regexpstatebuilder.H regexpstatebuilder_dbtab.cc regexpstatebuilder.cpp langdefloader.cpp \
		langmap.cpp statestartlangelem.cpp stringlistlangelem.cpp delimitedlangelem.cpp \
		vardefinitions.cpp textformatter.cpp textstyle.cpp textgenerator.cpp textstylebuilder.cpp \
		doctemplate.cpp substfun.cpp refgeneratormap.cpp readtags.c fileinfo.cpp linebuffer.cpp \
		preformatter.cpp regexpstateprinter.cpp

libcgi_a_AR = @ar_to_use@
libcgi_a_SOURCES = $(libcommon_a_SOURCES) envmapper.c

# LIBADD = @LIBOBJS@

# libcgi_a_LIBADD = $(LIBADD)
# libcommon_a_LIBADD = $(LIBADD)

INCLUDES = -I@top_srcdir@/src

EXTRA_DIST = colors.h generatorfactory.h \
             keys.h optparser.h styles.h  \
             tokens.h messages.h fileutil.h \
             cmdline.h envmapper.h \
             chartranslator.h my_set.h my_sstream.h my_string.h \
             linenumdigit.h globalostream.h \
             docgenerator.h \
             cmdlineargs.h \
             cmdline.ggo \
             copyright.h reportbugs.h \
             srcuntabifier.h colormap.h \
             optparser.sed optscanner.sed \
             langdefparser.sed langdefscanner.sed \
             langdefparser.h outlangdefparser.h \
             outlangtest.outlang.tmpl

BUILT_SOURCES = optparser.cc optparser.h optscanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
regexpstatebuilder.H regexpstatebuilder_dbtab.cc

langdefscanner.cc: $(srcdir)/langdefscanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/langdefscanner.ll

langdefparser.cc langdefparser.h: $(srcdir)/langdefparser.yy
	$(YACC) -p langdef_ -o $@ $(srcdir)/langdefparser.yy --defines=$*.h

outlangdefscanner.cc: $(srcdir)/outlangdefscanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/outlangdefscanner.ll

outlangdefparser.cc outlangdefparser.h: $(srcdir)/outlangdefparser.yy
	$(YACC) -p outlangdef_ -o $@ $(srcdir)/outlangdefparser.yy --defines=$*.h

optscanner.cc: $(srcdir)/optscanner.ll
	$(LEX) $(LFLAGS) -o $@ $(srcdir)/optscanner.ll

optparser.cc optparser.h: $(srcdir)/optparser.yy
	$(YACC) -p opsc_ -o $@ $(srcdir)/optparser.yy --defines=$*.h

TESTS = test_textstyle test_textgenerator test_outlangparser test_readtags

check_PROGRAMS = test_langdefparser test_langmap test_textstyle test_textgenerator test_outlangparser test_readtags

test_langdefparser_SOURCES = test_langdefparser_main.cpp
test_langmap_SOURCES = test_langmap_main.cpp langmap.cpp fileutil.cc messages.cc
test_textstyle_SOURCES = textstyle.cpp test_textstyle_main.cpp substfun.cpp
test_textgenerator_SOURCES = test_textgenerator_main.cpp textstylebuilder.cpp

test_outlangparser_SOURCES = textstyle.cpp test_outlangparser_main.cpp
test_outlangparser_DEPENDENCIES = outlangtest.outlang

test_readtags_SOURCES = test_readtags_main.cpp readtags.c readtags.h
test_readtags_DEPENDENCIES = mytags

mytags: $(srcdir)/test_readtags_main.cpp
	ctags --excmd=n --fields=+n -o mytags $(srcdir)/test_readtags_main.cpp $(srcdir)/readtags.h

outlangtest.outlang: $(srcdir)/outlangtest.outlang.tmpl
	rm -f outlangtest.outlang
	cp -f $(srcdir)/outlangtest.outlang.tmpl outlangtest.outlang

DISTCLEANFILES = outlangtest.outlang mytags

MAINTAINERCLEANFILES = optparser.cc optparser.h optscanner.cc \
langdefparser.cc langdefparser.h langdefscanner.cc \
outlangdefparser.cc outlangdefparser.h outlangdefscanner.cc

noinst_HEADERS = parsestyles.h generatormap.h maingeneratormap.h outputbuffer.h \
		outputgenerator.h mainoutputbuffer.h lineoutputgenerator.h stringdef.h langelem.h \
		statelangelem.h langelems.h langdefparserfun.h outlangdefparserfun.h \
		tostringcollection.h regexpreprocessor.h regexpstatebuilder.h langdefloader.h \
		langdefscanner.h outlangdefscanner.h parsestruct.h langmap.h \
		statestartlangelem.h stringlistlangelem.h delimitedlangelem.h vardefinitions.h \
		textformatter.h textstyle.h textstyles.h textgenerator.h textstylebuilder.h \
		doctemplate.h substfun.h parserinfo.h refgeneratormap.h readtags.h fileinfo.h \
		linebuffer.h preformatter.h regexpstateprinter.h

test_langdefparser_LDADD = -l$(BOOST_REGEX_LIB) libcommon.a
test_langmap_LDADD = -l$(BOOST_REGEX_LIB)
test_textstyle_LDADD = -l$(BOOST_REGEX_LIB)
test_textgenerator_LDADD = -l$(BOOST_REGEX_LIB) libcommon.a
test_outlangparser_LDADD = -l$(BOOST_REGEX_LIB) libcommon.a

