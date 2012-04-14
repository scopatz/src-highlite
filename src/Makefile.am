# Copyright (C) 1999-2009 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SUFFIXES = .ggo

if NO_GENGETOPT
#.ggo.c:
#	touch $@
else

check-regexp_cmd.c: $(srcdir)/check-regexp_cmd.ggo
	$(GENGETOPT) --input $(srcdir)/check-regexp_cmd.ggo --unamed-opts -F check-regexp_cmd --output-dir=$(srcdir)

.ggo.c:
	$(GENGETOPT) --input $< --unamed-opts --no-handle-help --no-handle-version --output-dir=$(srcdir)
endif

# in order to make it work with parallel make we need to make
# these deps explicit
cmdline.h: cmdline.c

#bin_PROGRAMS = check-regexp source-highlight
bin_PROGRAMS = check-regexp source-highlight source-highlight-settings
bin_SCRIPTS = java2html cpp2html src-hilite-lesspipe.sh \
	source-highlight-esc.sh

EXTRA_PROGRAMS = source-highlight-cgi 

SRCHILITE = $(top_builddir)/src/source-highlight$(EXEEXT)

AM_CPPFLAGS = -I$(top_srcdir)/gl -I$(top_builddir)/gl -I$(top_srcdir)/lib $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_LDFLAGS)

LDADD = $(top_builddir)/gl/libgnu.la

source_highlight_LDADD = $(LDADD) $(top_builddir)/lib/srchilite/libsource-highlight.la
source_highlight_cgi_LDADD = $(source_highlight_LDADD)

check_regexp_LDADD = $(BOOST_REGEX_LIB) $(top_builddir)/gl/libgnu.la

source_highlight_settings_LDADD = $(LDADD) $(top_builddir)/lib/srchilite/libsource-highlight.la

# for most rules, we use one file per line. `diffs' are more clear this way
#source_highlight_SOURCES = cmdline.c startapp.cc source-highlight.cc
source_highlight_SOURCES = cmdline.c source-highlight.cc 
check_regexp_SOURCES = check-regexp_cmd.c check-regexp.cpp
source_highlight_settings_SOURCES = source-highlight-settings.cpp

source_highlight_cgi_SOURCES = cmdline.c source-highlight-cgi.cc envmapper.c

# files that we don't want automake/autoconf to touch ever.
# just stick them in the distribution as-is
EXTRA_DIST = \
java2html.in \
cpp2html.in \
src-hilite-lesspipe.sh.in \
envmapper.h \
cmdline.ggo check-regexp_cmd.ggo \
$(source_highlightdata_DATA) \
src.pro source-highlight.pro source-highlight-settings.pro

LANGFILES = \
bison.lang      c.lang cpp.lang       javascript.lang  perl.lang    ruby.lang \
c_comment.lang  flex.lang      log.lang         php.lang     sml.lang \
caml.lang       function.lang  lua.lang         prolog.lang  symbols.lang \
changelog.lang  java.lang      number.lang      python.lang  url.lang \
pascal.lang fortran.lang fixed-fortran.lang \
html.lang html_simple.lang latex.lang logtalk.lang \
diff.lang c_string.lang langdef.lang outlang.lang style.lang \
extreme_comment.lang extreme_comment2.lang extreme_comment3.lang \
postscript.lang csharp.lang xml.lang sh.lang script_comment.lang \
tcl.lang sql.lang bib.lang makefile.lang css.lang m4.lang \
default.lang nohilite.lang slang.lang key_string.lang properties.lang \
desktop.lang lsm.lang spec.lang haxe.lang ldap.lang glsl.lang xorg.lang \
clike_vardeclaration.lang scala.lang ada.lang conf.lang pc.lang oz.lang \
texinfo.lang haskell.lang haskell_literate.lang \
manifest.lang asm.lang todo.lang applescript.lang \
vbscript.lang awk.lang bat.lang clipper.lang cobol.lang d.lang \
errors.lang erlang.lang proto.lang vala.lang lisp.lang islisp.lang \
scheme.lang po.lang opa.lang javalog.lang upc.lang tml.lang \
lilypond.lang

LANGFILES_NOTTOCHECK= \
tml_formatting_all.lang  tml_macrolinks.lang      tml_macrosdelayed2.lang \
tml_formatting.lang      tml_macros1.lang         tml_macrosdelayed3.lang \
tml_glue.lang            tml_macros2.lang         tml_macros.lang \
tml_macrosdelayed1.lang  tml_macrotokens.lang

OUTLANGFILES = \
css_common.outlang \
esc.outlang \
esc256.outlang \
html_common.outlang \
html_ref.outlang \
html_notfixed.outlang \
htmlcss.outlang \
htmltable.outlang \
htmltablelinenum.outlang \
html.outlang \
latex.outlang \
latexcolor.outlang \
xhtml_common.outlang \
xhtmlcss.outlang \
xhtml.outlang \
xhtml_notfixed.outlang \
xhtmltable.outlang \
texinfo.outlang \
javadoc.outlang \
docbook.outlang \
odf.outlang \
mediawiki.outlang


STYLEFILES = texinfo.style esc.style esc256.style lilypond.style

source_highlightdata_DATA = \
$(LANGFILES) $(LANGFILES_NOTTOCHECK) $(OUTLANGFILES) \
$(STYLEFILES) \
default.style style2.style style3.style \
javalog.style \
lang.map outlang.map \
default.css \
style.defaults

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

noinst_HEADERS = cmdline.h check-regexp_cmd.h          
