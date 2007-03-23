# Copyright (C) 1999, 2000, Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

bin_PROGRAMS = source-highlight
bin_SCRIPTS = java2html cpp2html src-hilite-lesspipe.sh
noinst_LTLIBRARIES = libsh.la
libsh_la_LIBADD = $(BOOST_REGEX_LIB) $(LDADD) lib/libcommon.la 
EXTRA_PROGRAMS = source-highlight-cgi 

SRCHILITE = $(top_builddir)/src/source-highlight$(EXEEXT)

LIBSUBDIR = $(SUBDIRS)

INCLUDES = -I@top_srcdir@/src/lib

AM_CPPFLAGS = -I$(top_srcdir)/gl -I$(top_builddir)/gl

LDADD = @LEXLIB@ $(top_builddir)/gl/libgnu.la

source_highlight_LDADD = libsh.la 
source_highlight_cgi_LDADD = libsh.la 

SUBDIRS = \
	lib \
	includes

DIST_SUBDIRS = \
	lib \
	includes

libsh_la_SOURCES = source-highlight.cc regexpengine.cpp regexpstate.cpp regexpenginedebug.cpp

# for most rules, we use one file per line. `diffs' are more clear this way
source_highlight_SOURCES = startapp.cc 

source_highlight_cgi_SOURCES = startapp-cgi.cc envmapper.c

# files that we don't want automake/autoconf to touch ever.
# just stick them in the distribution as-is
EXTRA_DIST = \
java2html.in \
cpp2html.in \
src-hilite-lesspipe.sh.in \
startapp.h \
envmapper.h \
$(source_highlightdata_DATA)

LANGFILES = \
bison.lang      cpp.lang       javascript.lang  perl.lang    ruby.lang \
c_comment.lang  flex.lang      log.lang         php.lang     sml.lang \
caml.lang       function.lang  lua.lang         prolog.lang  symbols.lang \
changelog.lang  java.lang      number.lang      python.lang  url.lang \
pascal.lang fortran.lang html.lang latex.lang logtalk.lang \
diff.lang c_string.lang langdef.lang outlang.lang style.lang \
extreme_comment.lang extreme_comment2.lang extreme_comment3.lang \
postscript.lang csharp.lang xml.lang sh.lang script_comment.lang \
tcl.lang sql.lang bib.lang makefile.lang css.lang m4.lang \
default.lang nohilite.lang

OUTLANGFILES = \
css_common.outlang \
esc.outlang \
html_common.outlang \
html_notfixed.outlang \
htmlcss.outlang \
htmldoc.outlang \
htmltable.outlang \
html.outlang \
latexdoc.outlang \
latex.outlang \
latexcolordoc.outlang \
latexcolor.outlang \
xhtml_common.outlang \
xhtmlcss.outlang \
xhtmldoc.outlang \
xhtml.outlang \
xhtmltable.outlang \
texinfo.outlang \
javadoc.outlang \
docbook.outlang

STYLEFILES = texinfo.style esc.style

source_highlightdata_DATA = \
$(LANGFILES) $(OUTLANGFILES) \
$(STYLEFILES) \
default.style style2.style style3.style \
lang.map outlang.map \
default.css

# files that are built before distribution gets built
#MAINTAINERCLEANFILES = $(BUILT_SOURCES)

check:
	for langfile in $(LANGFILES); do \
	  $(SRCHILITE) --data-dir=$(srcdir) --check-lang $(srcdir)/$$langfile ; \
	done && \
	for outlangfile in $(OUTLANGFILES); do \
	  $(SRCHILITE) --data-dir=$(srcdir) --check-outlang $(srcdir)/$$outlangfile ; \
	done

tags:
	ctags --c-types='defgmstuv' --recurse=yes $(srcdir)/*

.PHONY: tags

noinst_HEADERS = regexpengine.h regexpstate.h asserttest.h regexpenginedebug.h
