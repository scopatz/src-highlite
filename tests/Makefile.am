# Copyright (C) 1999-2008 Lorenzo Bettini <http://www.lorenzobettini.it>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SUBDIRS = output_dir

SUFFIXES = .lang .err_out .outlang .style .css .css.java.html .nf_css.java.html .css_doc.java.html .css_xhtml.java.html

STD_STYLE = --style-file $(top_srcdir)/src/default.style
STD_CSS_STYLE = --style-css-file $(top_srcdir)/src/default.css
STD_STYLE_HTML = -f html $(STD_STYLE)
STD_STYLE_DEFAULTS = --style-defaults $(top_srcdir)/src/style.defaults
DATADIROPTION = --data-dir $(top_srcdir)/src/

# use --binary-output so that output test files are always generated
# with \n only also on other operating systems.
PROGEXE = $(top_builddir)/src/$(PACKAGE)$(EXEEXT) --binary-output

# use --strip-trailing-cr since if run on windows, it may
# add \r to output files, while the reference files distributed
# are built on linux
DIFF = diff

# we disable the generation of the version of source-highlight
# so that the version does not interfere with the diffing
PROGNAME = $(PROGEXE) --gen-version $(DATADIROPTION)
PROGNAME_CSSSTYLE = $(PROGEXE) --gen-version $(DATADIROPTION) $(STD_CSS_STYLE)
PROGNAME_DOCBOOK = $(PROGEXE) --gen-version $(DATADIROPTION) -f docbook --doc --title="listing in docbook" --tab=8
PROGNAME_STD = $(PROGNAME) $(STD_STYLE_HTML) 

CHECKLANG = $(top_builddir)/src/$(PACKAGE)$(EXEEXT) --check-lang

CHECKOUTLANG = $(top_builddir)/src/$(PACKAGE)$(EXEEXT) --check-outlang

JAVA2HTML = $(PROGNAME) -s java $(STD_STYLE_HTML) 

JAVA2HTMLDOC = $(JAVA2HTML) --title="This is the title"

JAVA2ODF = $(PROGNAME) -s java -f odf

JAVA2ODFDOC = $(JAVA2ODF) --title="This is the title"

JAVA2MEDIAWIKI = $(PROGNAME) -s java -f mediawiki

JS2HTML = $(PROGNAME) -s javascript $(STD_STYLE_HTML) 

URL2HTML = $(PROGNAME) --lang-def=url.lang $(STD_STYLE_HTML) 

JAVA2XHTML = $(PROGNAME) -s java -f xhtml $(STD_STYLE) --lang-def=$(srcdir)/../src/java.lang

JAVA2XHTMLDOC = $(JAVA2XHTML) --doc

# note that we don't use $(srcdir), since we're only interested in
# the output of source-highlight to test it
JAVA2XHTMLCSS = $(JAVA2XHTML) --css ../doc/mono.css --no-doc

JAVA2XHTMLCSSDOC = $(JAVA2XHTML) --css ../doc/mono.css

JAVA2HTMLNOTFIXED = $(PROGNAME) -s java --outlang-def=$(srcdir)/../src/html_notfixed.outlang $(STD_STYLE) --doc --lang-def=$(srcdir)/../src/java.lang

JAVA2XHTMLNOTFIXED = $(PROGNAME) -s java --outlang-def=$(srcdir)/../src/xhtml_notfixed.outlang $(STD_STYLE) --doc --lang-def=$(srcdir)/../src/java.lang

JAVA2ESC = $(PROGNAME) -s java -f esc --style-file=$(top_srcdir)/src/esc.style --doc --lang-def=$(srcdir)/../src/java.lang

JAVA2TEX = $(PROGNAME) --doc -s java -f latexcolor $(STD_STYLE) --title="formatted with source-highlight"

CPP2TEX = $(PROGNAME) --doc -s cpp -f latexcolor $(STD_STYLE) 

JAVA2TEXINFO = $(PROGNAME) -s java -f texinfo --style-file $(top_srcdir)/src/texinfo.style

CPP2TEXINFO_WREFS = $(PROGNAME) -s cpp -f texinfo --style-file $(top_srcdir)/src/texinfo.style --gen-references=postline --line-number

# this refers to an "absolute" path (../doc/) without using the automake
# variables.  However this way the generated files will always be the
# same so tests won't fail.  You may have some problems if you want to
# view the generated file, test_css.html, and you are building in a
# different directory.  However this is not the spirit of the test :-)
# the important thing is that the generated file is always the same.
JAVA2HTMLCSS = $(PROGNAME) -s java -f html --css ../doc/mono.css --lang-def=$(srcdir)/../src/java.lang

JAVA2HTMLCSSNODOC = $(PROGNAME) -s java -f html --css ../doc/mono.css --no-doc --lang-def=$(srcdir)/../src/java.lang

CPP2HTML = $(PROGNAME) -s cpp $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/cpp.lang

C2HTML = $(PROGNAME) -s c $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/c.lang

CSHARP2HTML = $(PROGNAME) -s csharp $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/csharp.lang

PROLOG2HTML = $(PROGNAME) -s prolog $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/prolog.lang

PERL2HTML = $(PROGNAME) -s perl $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/perl.lang

PHP2HTML = $(PROGNAME) -s php3 $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/php.lang

PYTHON2HTML = $(PROGNAME) -s python $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/python.lang

FLEX2HTML = $(PROGNAME) -s flex $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/flex.lang

BISON2HTML = $(PROGNAME) -s bison $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/bison.lang

CHANGELOG2HTML = $(PROGNAME) -s changelog $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/changelog.lang

CHANGELOG2HTMLCSS = $(PROGNAME) -s changelog -f html --css ./changelog.css  --title="ChangeLog with css" --lang-def=$(srcdir)/../src/changelog.lang

RUBY2HTML = $(PROGNAME) -s ruby $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/ruby.lang

LUA2HTML = $(PROGNAME) -s lua $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/lua.lang

CAML2HTML = $(PROGNAME) -s caml $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/caml.lang

SML2HTML = $(PROGNAME) -s sml $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/sml.lang

LOG2HTML = $(PROGNAME) -s log -f html --style-file=$(srcdir)/syslog.style --lang-def=$(srcdir)/../src/log.lang

LATEX2HTML = $(PROGNAME) -s latex $(STD_STYLE_HTML)

LOGTALK2HTML = $(PROGNAME) -s logtalk $(STD_STYLE_HTML)

DIFF2HTML = $(PROGNAME) -s diff $(STD_STYLE_HTML)

LANG2HTML = $(PROGNAME) -s langdef $(STD_STYLE_HTML)

STYLE2HTML = $(PROGNAME) -s style $(STD_STYLE_HTML)

PROPERTIES2HTML = $(PROGNAME) $(STD_STYLE_HTML)

DESKTOP2HTML = $(PROGNAME) $(STD_STYLE_HTML)

LSM2HTML = $(PROGNAME) $(STD_STYLE_HTML)

HAXE2HTML = $(PROGNAME) $(STD_STYLE_HTML)

FORTRAN2HTML = $(PROGNAME) $(STD_STYLE_HTML)

SPEC2HTML = $(PROGNAME) $(STD_STYLE_HTML)

TXT2HTML = $(PROGNAME) -s style $(STD_STYLE_HTML) --lang-def=default.lang

FAILSAFE = $(PROGNAME) --failsafe

INFER = $(PROGNAME) --infer-lang

# language inference is performed implicitly if everything else failed
INFERIMPLICIT = $(PROGNAME)

SIMPLE = $(PROGEXE) --gen-version --outlang-def=$(srcdir)/simple.outlang --lang-def=$(srcdir)/simple.lang $(STD_STYLE) --style-defaults=$(srcdir)/../src/style.defaults

# test with a defaults file
TESTWDEFAULTS = $(PROGNAME) --lang-def=$(srcdir)/lang4defaults.lang $(STD_STYLE) --style-defaults=$(srcdir)/test.defaults

# test without a defaults file
TESTWODEFAULTS = $(PROGNAME) --lang-def=$(srcdir)/lang4defaults.lang $(STD_STYLE)

TESTISOLATE = $(PROGNAME) --lang-def=$(srcdir)/test_isolate.lang

TESTBACKREF = $(PROGNAME) --lang-def=$(srcdir)/test_backref.lang

# for testing named groups
NAMEDGROUPS = $(PROGEXE) --gen-version --lang-def=$(srcdir)/namedgroups.lang $(STD_STYLE) $(DATADIROPTION)
NAMEDGROUPS_STATE = $(PROGEXE) --gen-version --lang-def=$(srcdir)/namedgroups_state.lang $(STD_STYLE) $(DATADIROPTION)

DEBUGLANG = $(PROGNAME) -s java $(STD_STYLE_HTML) --debug-lang=dump

WRONGFILES = wrong_exp.lang wrong_var.lang wrong_trans.outlang wrong_syntax_simple.lang wrong_syntax.lang wrong_syntax_include.lang wrong_namedgroups.lang wrong_namedgroups_subexps.lang wrong_namedgroups_subexps2.lang wrong_backref.lang wrong_backref2.lang wrong_dyn_backref.lang wrong_dyn_backref2.lang wrong_include.lang wrong_outlang_include.outlang
WRONGFILESOUT = wrong_exp.err wrong_var.err wrong_trans.err missing_langmap.err missing_extension.err wrong_syntax_simple.err wrong_syntax.err wrong_syntax_include.err wrong_namedgroups.err wrong_namedgroups_subexps.err wrong_namedgroups_subexps2.err wrong_backref.err wrong_backref2.err wrong_dyn_backref.err wrong_dyn_backref2.err wrong_include.err wrong_outlang_include.err
WRONGSTYLES = wrong_dircolor.style wrong_already_defined.style wrong_already_defined_css.css
WRONGSTYLESOUT = wrong_dircolor.err wrong_already_defined.err wrong_already_defined_css.err
WRONGCMDLINEPARAMS = wrong_line_range.err wrong_regex_range.err \
 wrong_syntax_mode.err
# missing_langmap2.err

OUTPUTWREFS=test_ref.html test_refs.h.html test_refs.cpp.html test_ref.tex test_ref_post.tex test_ref.texinfo test_ref.docbook test_ref.xhtml

TAGFILES=test_ref.tags test_ref_multi.tags

EXTRA_DIST = test.java test.java.html test.java.doc.html \
test.js test.js.html test.h test.h.html test_c.c test_c.c.html \
test_no_line_at_the_end.c test_no_line_at_the_end.c.html \
test_line_at_the_end.c test_line_at_the_end.c.html \
test_no_line_at_the_end.java test_no_line_at_the_end.java.html \
test_comments.cc test_comments.cc.html test_comments.java \
test_comments.java.html test_template.cc test_template.cc.html \
test.pl test.pl.html header.html footer.html test_header.html \
test_java_lines.html test_cpp_lines.html test_pl_lines.html \
test.pm test_comments.pm test.pm.html test_comments.pm.html \
test_perl_lines.html \
test.php3 test.php3.html test_php3_lines.html \
test_with_html.php.html test_with_html.php \
test.py test.py.html test_python_lines.html \
test_comments.py test_comments.py.html test_py_comments_lines.html \
test_xhtml.html test_xhtml_notfixed.html test_xhtml_doc.html \
test_xhtml_css.html test_xhtml_css_doc.html \
test_css.html test_css_nodoc.html test_notfixed.html \
test.chlog test.chlog.html test.chlog_css.html \
test.l test.l.html \
test.y test.y.html \
test.rb test_comments.rb test.rb.html test_comments.rb.html \
test.java.txt \
test.java.tex test.java.tex.html \
test.java.fodt test.java.doc.fodt \
test.java.mediawiki \
test.java.texinfo \
test.lua test.lua.html \
test.ml test.ml.html \
test.sml test.sml.html \
test.log test.log.html \
access.log access.log.html \
auth.log auth.log.html \
error.log error.log.html \
syslog.log syslog.log.html \
test.pas test.pas.html \
test.htm test.htm.html \
test_with_embed.htm test_with_embed.htm.html \
test_html5.htm test_html5.htm.html \
test2.htm test2.htm.html \
test.diff test.diff.html \
test2.diff test2.diff.html \
test3.diff test3.diff.html \
test.simple test.simple.html \
test.unknown test.unknown.html \
syslog.style syslog.style.html \
test.tex test.tex.html \
test.lgt test.lgt.html \
$(OUTPUTWREFS) \
test_refs.h test_refs.cpp \
changelog.css \
simple.lang simple.outlang \
test_isolate.lang \
test.isolate test.isolate.html \
test_backref.lang \
test.backref test.backref.html \
test2.backref test2.backref.html \
log.lang.html c.lang.html \
default.style.html \
lang.map \
debug.debug debug.java debug.java.html \
test_extreme_comment.cpp test_extreme_comment2.cpp test_extreme_comment3.cpp \
test.cs test.cs.html \
test.xml test.xml.html \
test.sh test.sh.html \
test2.sh test2.sh.html \
test.url test.url.html \
test.txt test.txt.html \
test2.pl test2.pl.html \
test.tcl test.tcl.html \
test.sql test.sql.html \
test.bib test.bib.html \
test.makefile test.makefile.html \
test.css test.css.html \
test.ps test.ps.html \
$(WRONGFILES) \
$(WRONGFILESOUT) \
$(WRONGSTYLES) $(WRONGSTYLESOUT) \
$(WRONGCMDLINEPARAMS) \
valgrind_tests.sh.in valgrind_suppressions.sh.in \
valgrind_test.sh.in suppressions.supp \
erasedir.sed erasedir2.sed erasedir3.sed \
erasedir_inputlang.sed \
namedgroups.lang namedgroups_state.lang \
test.ngroups test.ngroups.html \
test_state.ngroups test_state.ngroups.html \
c_comment.show namedgroups_state.show \
cpp.langelems \
lang.list outlang.list \
test.h.docbook \
test.sl test.sl.html \
lang4defaults.lang test.defaults test.wdefault test.wodefault \
test.wdefault.html test.wodefault.html \
test.properties test.properties.html \
test.desktop test.desktop.html \
test.lsm test.lsm.html \
test.hx test.hx.html \
test.fortran test.fortran.html test.fixed-fortran.html \
test.spec test.spec.html \
test.ldap test.ldap.html \
test.m4 test.m4.html \
test.glsl test.glsl.html \
test.xorg test.xorg.html \
test.conf test.conf.html \
test.scala test.scala.html \
test.adb test.adb.html \
test.pc test.pc.html \
test_string_stop.java test_string_stop.java.html \
test_java_stop.java test_java_stop.java.html \
test_string_stop.lang \
test_vardecl.java test_vardecl.java.html \
test_vardecl.cc test_vardecl.cc.html \
test_newlines.lang test_nonewlines.lang \
test_linerange1.html test_linerange2.html \
test_linerange_sep.html \
test_regexrange1.html test_regexrange2.html \
test_regexrange3.html test_regexrange4.html \
test_nobgcolor.cpp test_nobgcolor.html \
test_tabs.java.html \
test.texinfo test.texinfo.html \
test.hs test.hs.html \
test.lhs test.lhs.html \
test.ecore test.ecore.html \
test.MF test.MF.html \
test.asm test.asm.html \
test.scpt test.scpt.html \
test.vbs test.vbs.html \
test.awk test.awk.html \
test.bat test.bat.html \
test.clipper test.clipper.html \
test.cobol test.cobol.html \
test.d test.d.html \
test.errors test.errors.html \
test.erl test.erl.html \
test.proto test.proto.html \
test.vala test.vala.html \
test.lisp test.lisp.html \
test.scm test.scm.html \
test.po test.po.html \
test.opa test.opa.html \
test.javalog test.javalog.html \
test.upc test.upc.html \
test.tml test.tml.html \
test.ly test.ly.html

LINERANGE1EXE=$(JAVA2HTML) --line-range="12-18","29-34" --line-number
LINERANGE2EXE=$(JAVA2HTML) --line-range="12-18","29-34" --line-number --range-context=3
LINERANGESEPEXE=$(JAVA2HTML) --line-range="12-18","29-34" --line-number --range-context=3 --range-separator="<...>"

REGEXRANGE1EXE=$(JAVA2HTML) --regex-range="/// [[:alpha:]]+" --line-number

REGEXRANGE2EXE=$(JAVA2HTML) --regex-range="/\\* main \\*/" --line-number

REGEXRANGE3EXE=$(JAVA2HTML) --regex-range="/\\* main \\*/","/\\* mymethod \\*/" --line-number

REGEXRANGE4EXE=$(JAVA2HTML) --regex-range="/\\* [[:alpha:]]+ \\*/" --line-number

WRONGLINERANGEEXE=$(PROGEXE) --line-range="a-b"  --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null

WRONGREGEXRANGEEXE=$(PROGEXE) --regex-range="ab","foobar","{wrong"  --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null


WRONGSYNTAXMODEEXE=$(PROGEXE) --data-dir=$(top_srcdir)/src -o /dev/null $(srcdir)/test.java

PROG_NOLANGDEF=$(PROGEXE) --outlang-def=$(srcdir)/simple.outlang $(STD_STYLE) --data-dir=$(srcdir)/ $(STD_STYLE_DEFAULTS)
PROG_NOOUTLANGDEF=$(PROGEXE) --lang-def=$(srcdir)/simple.lang $(STD_STYLE) $(STD_STYLE_DEFAULTS) --quiet

CPP2HTML_WHEADERS = $(CPP2HTML) --header=$(srcdir)/header.html --footer=$(srcdir)/footer.html

CTAGS_COMMAND=--ctags="$(CTAGS) --excmd=number --tag-relative=yes -o test_ref.tags" --ctags-file="test_ref.tags"
# for more than one file: test.h test.cpp
CTAGS_COMMAND_MULTI=--ctags="$(CTAGS) --excmd=number --tag-relative=yes -o test_ref_multi.tags" --ctags-file="test_ref_multi.tags"
CTAGS_COMMAND_TEST=--ctags="$(CTAGS) --excmd=number --tag-relative=yes -o my_test_ref_tmp.tags" --ctags-file="my_test_ref_tmp"

CPP2HTML_WREFS = $(CPP2HTML) --title="Contains references to tags" --gen-references=inline

CPP2LATEX_WREFS = $(CPP2TEX) --title="Contains references to tags" --gen-references=postline --line-number

CPP2LATEX_WREFSPOST = $(CPP2TEX) --title="Contains references to tags" --gen-references=postdoc --line-number

CPP2DOCBOOK_WREFS = $(PROGNAME_DOCBOOK) --gen-references=postline --line-number 

CPP2XHTML_WREFS = $(PROGNAME) -s cpp -f xhtml --css ../src/default.css --gen-references=inline --line-number-ref --title="XHTML with refs"

CTAGS_CMD=$(CTAGS) --excmd=number --tag-relative=yes 

# these are files processed using a css as the style file
.java.css.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@

# these are files processed using a css as the style file
.java.css_doc.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@ --title="This is the title"

# these are files processed using a css as the style file and a non fixed html
.java.nf_css.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@ --outlang-def=$(srcdir)/../src/html_notfixed.outlang

# these are files processed using a css as the style file
.java.css_xhtml.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@ -f xhtml

if MAINTAINER_MODE
check: check-produced-output \
check_wrong check_missing \
check_wrong_lineranges \
check_wrong_regexranges \
check_wrong_syntaxmode
else
check: check-produced-output
endif

check-produced-output: \
check_java2html check_javascript \
check_java2xhtml check_cpp2html check_csharp2html \
check_prolog2html check_logtalk2html \
check_perl2html \
check_php32html check_python2html check_changelog check_flex check_bison \
check_ruby check_lua check_ml check_sml check_log check_pascal check_html \
check_xml \
check_sh \
check_url \
check_latex \
check_diff \
check_simple \
check_isolate \
check_backref \
check_lang \
check_langelems \
check_list \
check_txt \
check_sql \
check_bib \
check_infer \
check_debug \
check_ref \
check_show \
check_makefile \
check_asm \
check_css \
check_ps \
check_docbook \
check_namedgroups \
check_slang \
check_defaults \
check_properties \
check_desktop \
check_lsm \
check_spec \
check_haxe \
check_fortran \
check_ldap \
check_m4 \
check_glsl \
check_xorg \
check_conf \
check_scala \
check_ada \
check_pkgconfig \
check_texinfo \
check_haskell \
check_manifest \
check_applescript \
check_vbscript \
check_awk \
check_bat \
check_clipper \
check_cobol \
check_d \
check_errors \
check_erlang \
check_proto \
check_vala \
check_lisp \
check_scheme \
check_po \
check_opa \
check_javalog \
check_upc \
check_lilypond \
check_tml \
check-output-dir \
check_stop \
check_vardecl \
check_newlines \
check_lineranges \
check_regexranges \
check_nobgcolor \
check_tabs \
check_failsafe

remove_css_html_files:
	rm -f *.css.java.html *.nf_css.java.html

remove_css_xhtml_files:
	rm -f *.css_xhtml.java.html

remove_css_doc_files:
	rm -f *.css_doc.java.html

check_java2html: remove_css_html_files remove_css_doc_files test.css.java.html test.nf_css.java.html test.css_doc.java.html
	$(JAVA2HTML) -i $(srcdir)/test.java -o test.java.out.html
	$(JAVA2HTMLDOC) -i $(srcdir)/test.java -o test.java.doc.out.html
	$(JAVA2HTMLNOTFIXED) < $(srcdir)/test.java > test_notfixed.out.html
	tr -d '\r' < test_notfixed.out.html > temp.output && cp -f temp.output test_notfixed.out.html
	$(JAVA2HTMLCSS) < $(srcdir)/test.java > test_css.out.html
	tr -d '\r' < test_css.out.html > temp.output && cp -f temp.output test_css.out.html
	$(JAVA2HTMLCSSNODOC) < $(srcdir)/test.java > test_css_nodoc.out.html
	tr -d '\r' < test_css_nodoc.out.html > temp.output && cp -f temp.output test_css_nodoc.out.html
	$(JAVA2HTML) -i $(srcdir)/test_comments.java -o test_comments.java.out.html
	$(JAVA2HTML) -n --line-number-ref -i $(srcdir)/test.java -o test_java_lines.out.html
	$(JAVA2HTML) -n -i $(srcdir)/test_no_line_at_the_end.java -o test_no_line_at_the_end.java.out.html
	$(JAVA2ESC) -n -i $(srcdir)/test.java -o test.java.out.txt
	$(JAVA2TEX) --line-number=" " -i $(srcdir)/test.java -o test.java.out.tex
	$(JAVA2TEXINFO) -n -i $(srcdir)/test.java -o test.java.out.texinfo
	$(JAVA2ODF) --line-number=" " -i $(srcdir)/test.java -o test.java.out.fodt
	$(JAVA2ODFDOC) --line-number=" " -i $(srcdir)/test.java -o test.java.out.doc.fodt
	$(JAVA2MEDIAWIKI) -i $(srcdir)/test.java -o test.java.out.mediawiki
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.java.html test.java.out.html
	$(DIFF) $(srcdir)/test.java.doc.html test.java.doc.out.html
	$(DIFF) $(srcdir)/test_notfixed.html test_notfixed.out.html
	$(DIFF) $(srcdir)/test_css.html test_css.out.html
	$(DIFF) $(srcdir)/test_css_nodoc.html test_css_nodoc.out.html
	$(DIFF) $(srcdir)/test_comments.java.html test_comments.java.out.html
	$(DIFF) $(srcdir)/test_java_lines.html test_java_lines.out.html
	$(DIFF) $(srcdir)/test_no_line_at_the_end.java.html test_no_line_at_the_end.java.out.html
	$(DIFF) $(srcdir)/test.java.txt test.java.out.txt
	$(DIFF) $(srcdir)/test.java.tex test.java.out.tex
	$(DIFF) $(srcdir)/test.java.texinfo test.java.out.texinfo
	$(DIFF) $(srcdir)/test.java.fodt test.java.out.fodt
	$(DIFF) $(srcdir)/test.java.doc.fodt test.java.out.doc.fodt
	$(DIFF) $(srcdir)/test.java.mediawiki test.java.out.mediawiki
	$(DIFF) $(srcdir)/test.java.html test.css.java.html
	$(DIFF) $(srcdir)/test_notfixed.html test.nf_css.java.html
	$(DIFF) $(srcdir)/test.java.doc.html test.css_doc.java.html

check_javascript: 
	$(JS2HTML) < $(srcdir)/test.js -o test.js.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.js.html test.js.out.html

check_java2xhtml: remove_css_xhtml_files test.css_xhtml.java.html
	$(JAVA2XHTML) < $(srcdir)/test.java -o test_xhtml.out.html
	$(JAVA2XHTMLNOTFIXED) < $(srcdir)/test.java -o test_xhtml_notfixed.out.html
	$(JAVA2XHTMLDOC) < $(srcdir)/test.java -o test_xhtml_doc.out.html
	sed -itesttmp -f $(srcdir)/erasedir_inputlang.sed test_xhtml_doc.out.html
	$(JAVA2XHTMLCSS) < $(srcdir)/test.java -o test_xhtml_css.out.html
	$(JAVA2XHTMLCSSDOC) < $(srcdir)/test.java -o test_xhtml_css_doc.out.html
	sed -itesttmp -f $(srcdir)/erasedir_inputlang.sed test_xhtml_css_doc.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_xhtml.html test_xhtml.out.html
	$(DIFF) $(srcdir)/test_xhtml_notfixed.html test_xhtml_notfixed.out.html
	$(DIFF) $(srcdir)/test_xhtml_doc.html test_xhtml_doc.out.html
	$(DIFF) $(srcdir)/test_xhtml_css.html test_xhtml_css.out.html
	$(DIFF) $(srcdir)/test_xhtml_css_doc.html test_xhtml_css_doc.out.html
	$(DIFF) $(srcdir)/test_xhtml.html test.css_xhtml.java.html

check_cpp2html: 
	$(CPP2HTML) -i $(srcdir)/test.h -o test.h.out.html
	$(CPP2HTML) -i $(srcdir)/test_comments.cc -o test_comments.cc.out.html
	$(CPP2HTML) -i $(srcdir)/test_template.cc -o test_template.cc.out.html
	$(CPP2HTML_WHEADERS) -i $(srcdir)/test.h -o test_header.out.html
	$(CPP2HTML) -n -i $(srcdir)/test.h -o test_cpp_lines.out.html
	$(CPP2HTML) -n -i $(srcdir)/test_no_line_at_the_end.c -o test_no_line_at_the_end.c.out.html
	$(CPP2HTML) -n -i $(srcdir)/test_line_at_the_end.c -o test_line_at_the_end.c.out.html
	$(C2HTML) -i $(srcdir)/test_c.c -o test_c.c.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.h.html test.h.out.html
	$(DIFF) $(srcdir)/test_comments.cc.html test_comments.cc.out.html
	$(DIFF) $(srcdir)/test_template.cc.html test_template.cc.out.html
	$(DIFF) $(srcdir)/test_header.html test_header.out.html
	$(DIFF) $(srcdir)/test_cpp_lines.html test_cpp_lines.out.html
	$(DIFF) $(srcdir)/test_no_line_at_the_end.c.html test_no_line_at_the_end.c.out.html
	$(DIFF) $(srcdir)/test_line_at_the_end.c.html test_line_at_the_end.c.out.html
	$(DIFF) $(srcdir)/test_c.c.html test_c.c.out.html

check_csharp2html: 
	$(CSHARP2HTML) -i $(srcdir)/test.cs -o test.cs.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.cs.html test.cs.out.html

check_prolog2html: 
	$(PROLOG2HTML) < $(srcdir)/test.pl -o test.pl.out.html
	$(PROLOG2HTML) -n -i $(srcdir)/test.pl -o test_pl_lines.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.pl.html test.pl.out.html
	$(DIFF) $(srcdir)/test_pl_lines.html test_pl_lines.out.html

check_logtalk2html:
	$(LOGTALK2HTML) < $(srcdir)/test.lgt -o test.lgt.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.lgt.html test.lgt.out.html

check_perl2html:
	$(PERL2HTML) < $(srcdir)/test.pm -o test.pm.out.html
	$(PERL2HTML) < $(srcdir)/test_comments.pm -o test_comments.pm.out.html
	$(PERL2HTML) -n -i $(srcdir)/test.pm -o test_perl_lines.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.pm.html test.pm.out.html
	$(DIFF) $(srcdir)/test_comments.pm.html test_comments.pm.out.html 
	$(DIFF) $(srcdir)/test_perl_lines.html test_perl_lines.out.html

check_php32html:
	$(PHP2HTML) < $(srcdir)/test.php3 -o test.php3.out.html
	$(PHP2HTML) < $(srcdir)/test_with_html.php -o test_with_html.php.out.html
	$(PHP2HTML) -n -i $(srcdir)/test.php3 -o test_php3_lines.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.php3.html test.php3.out.html
	$(DIFF) $(srcdir)/test_with_html.php.html test_with_html.php.out.html
	$(DIFF) $(srcdir)/test_php3_lines.html test_php3_lines.out.html

check_python2html:
	$(PYTHON2HTML) < $(srcdir)/test.py -o test.py.out.html
	$(PYTHON2HTML) < $(srcdir)/test_comments.py -o test_comments.py.out.html
	$(PYTHON2HTML) -n -i $(srcdir)/test.py -o test_python_lines.out.html
	$(PYTHON2HTML) -n -i $(srcdir)/test_comments.py -o test_py_comments_lines.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.py.html test.py.out.html
	$(DIFF) $(srcdir)/test_comments.py.html test_comments.py.out.html
	$(DIFF) $(srcdir)/test_python_lines.html test_python_lines.out.html
	$(DIFF) $(srcdir)/test_py_comments_lines.html test_py_comments_lines.out.html

check_changelog:
	$(CHANGELOG2HTML) < $(srcdir)/test.chlog -o test.chlog.out.html
	$(CHANGELOG2HTMLCSS) -i $(srcdir)/test.chlog -o test.chlog_css.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.chlog.html test.chlog.out.html
	$(DIFF) $(srcdir)/test.chlog_css.html test.chlog_css.out.html

check_flex:
	$(FLEX2HTML) < $(srcdir)/test.l -o test.l.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.l.html test.l.out.html

check_bison:
	$(BISON2HTML) < $(srcdir)/test.y -o test.y.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.y.html test.y.out.html

check_ruby:
	$(RUBY2HTML) < $(srcdir)/test.rb -o test.rb.out.html
	$(RUBY2HTML) < $(srcdir)/test_comments.rb -o test_comments.rb.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.rb.html test.rb.out.html
	$(DIFF) $(srcdir)/test_comments.rb.html test_comments.rb.out.html

check_lua:
	$(LUA2HTML) < $(srcdir)/test.lua -o test.lua.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.lua.html test.lua.out.html

check_ml:
	$(CAML2HTML) < $(srcdir)/test.ml -o test.ml.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.ml.html test.ml.out.html

check_sml:
	$(SML2HTML) < $(srcdir)/test.sml -o test.sml.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.sml.html test.sml.out.html

check_log:
	$(LOG2HTML) < $(srcdir)/test.log -o test.log.out.html
	$(LOG2HTML) < $(srcdir)/access.log -o access.log.out.html
	$(LOG2HTML) < $(srcdir)/auth.log -o auth.log.out.html
	$(LOG2HTML) < $(srcdir)/error.log -o error.log.out.html
	$(LOG2HTML) < $(srcdir)/syslog.log -o syslog.log.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.log.html test.log.out.html
	$(DIFF) $(srcdir)/access.log.html access.log.out.html
	$(DIFF) $(srcdir)/auth.log.html auth.log.out.html
	$(DIFF) $(srcdir)/error.log.html error.log.out.html
	$(DIFF) $(srcdir)/syslog.log.html syslog.log.out.html

check_diff:
	$(DIFF2HTML) < $(srcdir)/test.diff -o test.diff.out.html
	$(DIFF2HTML) < $(srcdir)/test2.diff -o test2.diff.out.html
	$(DIFF2HTML) < $(srcdir)/test3.diff -o test3.diff.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.diff.html test.diff.out.html
	$(DIFF) $(srcdir)/test2.diff.html test2.diff.out.html
	$(DIFF) $(srcdir)/test3.diff.html test3.diff.out.html

check_pascal:
	$(PROGNAME) -i $(srcdir)/test.pas -o test.pas.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.pas.html test.pas.out.html

check_html:
	$(PROGNAME) -i $(srcdir)/test.htm --title="html output formatted in html" -o test.htm.out.html
	$(PROGNAME) -i $(srcdir)/test2.htm --title="html output formatted in html" -o test2.htm.out.html
	$(PROGNAME) -i $(srcdir)/test_html5.htm --title="html output formatted in html" -o test_html5.htm.out.html
	$(PROGNAME) -i $(srcdir)/test_with_embed.htm --title="html output formatted in html" -o test_with_embed.htm.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.htm.html test.htm.out.html
	$(DIFF) $(srcdir)/test2.htm.html test2.htm.out.html
	$(DIFF) $(srcdir)/test_html5.htm.html test_html5.htm.out.html
	$(DIFF) $(srcdir)/test_with_embed.htm.html test_with_embed.htm.out.html

check_xml:
	$(PROGNAME) -i $(srcdir)/test.xml --title="xml formatted in html" -o test.xml.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.xml.html test.xml.out.html

check_sh:
	$(PROGNAME) -i $(srcdir)/test.sh -o test.sh.out.html
	$(PROGNAME) -i $(srcdir)/test2.sh -o test2.sh.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.sh.html test.sh.out.html
	$(DIFF) $(srcdir)/test2.sh.html test2.sh.out.html

check_slang:
	$(PROGNAME) -i $(srcdir)/test.sl -o test.sl.out.html --title="S-LANG test"
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.sl.html test.sl.out.html

check_url:
	$(URL2HTML) -i $(srcdir)/test.url -o test.url.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.url.html test.url.out.html

check_properties:
	$(PROPERTIES2HTML) -i $(srcdir)/test.properties -o test.properties.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.properties.html test.properties.out.html

check_desktop:
	$(DESKTOP2HTML) -i $(srcdir)/test.desktop -o test.desktop.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.desktop.html test.desktop.out.html

check_lsm:
	$(LSM2HTML) -i $(srcdir)/test.lsm -o test.lsm.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.lsm.html test.lsm.out.html

check_haxe:
	$(HAXE2HTML) -i $(srcdir)/test.hx -o test.hx.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.hx.html test.hx.out.html

check_ldap:
	$(PROGNAME_STD) -i $(srcdir)/test.ldap -o test.ldap.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.ldap.html test.ldap.out.html

check_m4:
	$(PROGNAME_STD) -i $(srcdir)/test.m4 -o test.m4.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.m4.html test.m4.out.html

check_glsl:
	$(PROGNAME_STD) -i $(srcdir)/test.glsl -o test.glsl.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.glsl.html test.glsl.out.html

check_xorg:
	$(PROGNAME_STD) -i $(srcdir)/test.xorg -s xorg  -o test.xorg.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.xorg.html test.xorg.out.html

check_conf:
	$(PROGNAME_STD) -i $(srcdir)/test.conf -s conf  -o test.conf.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.conf.html test.conf.out.html

check_scala:
	$(PROGNAME_STD) -i $(srcdir)/test.scala -s scala  -o test.scala.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.scala.html test.scala.out.html

check_ada:
	$(PROGNAME_STD) -i $(srcdir)/test.adb -s ada  -o test.adb.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.adb.html test.adb.out.html

check_pkgconfig:
	$(PROGNAME_STD) -i $(srcdir)/test.pc -s pc  -o test.pc.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.pc.html test.pc.out.html

check_texinfo:
	$(PROGNAME_STD) -i $(srcdir)/test.texinfo -o test.texinfo.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.texinfo.html test.texinfo.out.html

check_haskell:
	$(PROGNAME_STD) -i $(srcdir)/test.hs -o test.hs.out.html
	$(PROGNAME) $(STD_STYLE) -f xhtml  -i $(srcdir)/test.lhs -o test.lhs.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.hs.html test.hs.out.html
	$(DIFF) $(srcdir)/test.lhs.html test.lhs.out.html

check_manifest:
	$(PROGNAME_STD) -i $(srcdir)/test.MF -o test.MF.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.MF.html test.MF.out.html

check_asm:
	$(PROGNAME_STD) -i $(srcdir)/test.asm -o test.asm.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.asm.html test.asm.out.html

check_applescript:
	$(PROGNAME_STD) -i $(srcdir)/test.scpt -o test.scpt.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.scpt.html test.scpt.out.html

check_vbscript:
	$(PROGNAME_STD) -i $(srcdir)/test.vbs -o test.vbs.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.vbs.html test.vbs.out.html

check_awk:
	$(PROGNAME_STD) -i $(srcdir)/test.awk -o test.awk.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.awk.html test.awk.out.html

check_bat:
	$(PROGNAME_STD) -i $(srcdir)/test.bat -o test.bat.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.bat.html test.bat.out.html

check_clipper:
	$(PROGNAME_STD) -i $(srcdir)/test.clipper -o test.clipper.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.clipper.html test.clipper.out.html

check_cobol:
	$(PROGNAME_STD) -i $(srcdir)/test.cobol -o test.cobol.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.cobol.html test.cobol.out.html

check_d:
	$(PROGNAME_STD) -i $(srcdir)/test.d -o test.d.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.d.html test.d.out.html

check_errors:
	$(PROGNAME_STD) -i $(srcdir)/test.errors -o test.errors.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.errors.html test.errors.out.html

check_erlang:
	$(PROGNAME_STD) -i $(srcdir)/test.erl -o test.erl.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.erl.html test.erl.out.html

check_fortran:
	$(FORTRAN2HTML) -i $(srcdir)/test.fortran -o test.fortran.out.html
	$(FORTRAN2HTML) -i $(srcdir)/test.fortran -s fixed-fortran -o test.fixed-fortran.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.fortran.html test.fortran.out.html
	$(DIFF) $(srcdir)/test.fixed-fortran.html test.fixed-fortran.out.html

check_proto:
	$(PROGNAME_STD) -i $(srcdir)/test.proto -o test.proto.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.proto.html test.proto.out.html

check_vala:
	$(PROGNAME_STD) -i $(srcdir)/test.vala -o test.vala.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.vala.html test.vala.out.html

check_lisp:
	$(PROGNAME_STD) -i $(srcdir)/test.lisp -o test.lisp.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.lisp.html test.lisp.out.html

check_scheme:
	$(PROGNAME_STD) -i $(srcdir)/test.scm -o test.scm.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.scm.html test.scm.out.html

check_po:
	$(PROGNAME_STD) -i $(srcdir)/test.po -o test.po.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.po.html test.po.out.html

check_opa:
	$(PROGNAME_STD) -i $(srcdir)/test.opa -o test.opa.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.opa.html test.opa.out.html

check_javalog:
	$(PROGNAME) --style-file $(top_srcdir)/src/javalog.style -i $(srcdir)/test.javalog -o test.javalog.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.javalog.html test.javalog.out.html

check_upc:
	$(PROGNAME_STD) -i $(srcdir)/test.upc -o test.upc.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.upc.html test.upc.out.html

check_lilypond:
	$(PROGNAME) --style-file $(top_srcdir)/src/lilypond.style -i $(srcdir)/test.ly -o test.ly.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.ly.html test.ly.out.html

check_tml:
	$(PROGNAME_STD) -i $(srcdir)/test.tml -o test.tml.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.tml.html test.tml.out.html

check_spec:
	$(SPEC2HTML) -i $(srcdir)/test.spec -o test.spec.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.spec.html test.spec.out.html

check_txt:
	$(TXT2HTML) -i $(srcdir)/test.txt -o test.txt.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.txt.html test.txt.out.html

myscript: test.sh
	cp $(srcdir)/test.sh $@

myimplicitxml.foo: test.xml
	cp $(srcdir)/test.xml $@

myimplicitphp.foo: test.php3
	cp $(srcdir)/test.php3 $@

check_infer: myscript myimplicitxml.foo myimplicitphp.foo
	rm -f myscript.html
	rm -f myimplicitxml.foo.html
	$(INFER) -i $(srcdir)/test2.pl -o test2.pl.out.html
	$(INFER) -i $(srcdir)/test.tcl -o test.tcl.out.html
	$(INFERIMPLICIT) -i myscript -o myscript.html
	$(INFERIMPLICIT) -i $(srcdir)/test.ecore -o test.ecore.out.html
	$(INFERIMPLICIT) --title="xml formatted in html" -i myimplicitxml.foo -o myimplicitxml.foo.html
	$(INFERIMPLICIT) -i myimplicitphp.foo -o myimplicitphp.foo.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test2.pl.html test2.pl.out.html
	$(DIFF) $(srcdir)/test.tcl.html test.tcl.out.html
	$(DIFF) $(srcdir)/test.sh.html myscript.html
	$(DIFF) $(srcdir)/test.ecore.html test.ecore.out.html
	$(DIFF) $(srcdir)/test.xml.html myimplicitxml.foo.html
	$(DIFF) $(srcdir)/test.php3.html myimplicitphp.foo.html

check_latex:
	$(PROGNAME) -i $(srcdir)/test.tex  -o test.tex.out.html
	$(PROGNAME) -i $(srcdir)/test.java.tex  -o test.java.tex.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.tex.html test.tex.out.html
	$(DIFF) $(srcdir)/test.java.tex.html test.java.tex.out.html

check_docbook:
	$(PROGNAME_DOCBOOK) -i $(srcdir)/test.h --line-number -o test.h.out.docbook
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.h.docbook test.h.out.docbook

check_sql:
	$(PROGNAME) -i $(srcdir)/test.sql -o test.sql.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.sql.html test.sql.out.html

check_bib:
	$(PROGNAME) -i $(srcdir)/test.bib -o test.bib.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.bib.html test.bib.out.html

check_makefile:
	$(PROGNAME) -i $(srcdir)/test.makefile -o test.makefile.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.makefile.html test.makefile.out.html

check_css:
	$(PROGNAME) -i $(srcdir)/test.css -o test.css.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.css.html test.css.out.html

check_ps:
	$(PROGNAME) -i $(srcdir)/test.ps -o test.ps.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.ps.html test.ps.out.html

check_lang:
	$(LANG2HTML) -i $(top_srcdir)/src/log.lang -o log.lang.out.html
	$(LANG2HTML) -i $(top_srcdir)/src/c.lang -o c.lang.out.html
	$(STYLE2HTML) -i $(top_srcdir)/src/default.style -o default.style.out.html
	$(STYLE2HTML) -i $(srcdir)/syslog.style -o syslog.style.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/log.lang.html log.lang.out.html
	$(DIFF) $(srcdir)/c.lang.html c.lang.out.html
	$(DIFF) $(srcdir)/default.style.html default.style.out.html
	$(DIFF) $(srcdir)/syslog.style.html syslog.style.out.html

check_simple:
	$(SIMPLE) -i $(srcdir)/test.simple -o test.simple.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.simple.html test.simple.out.html

check_isolate:
	$(TESTISOLATE) -i $(srcdir)/test.isolate -o test.isolate.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.isolate.html test.isolate.out.html

check_backref:
	$(TESTBACKREF) -i $(srcdir)/test.backref -o test.backref.out.html
	$(TESTBACKREF) -i $(srcdir)/test2.backref -o test2.backref.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.backref.html test.backref.out.html
	$(DIFF) $(srcdir)/test2.backref.html test2.backref.out.html

check_namedgroups:
	$(NAMEDGROUPS) -i $(srcdir)/test.ngroups -o test.ngroups.out.html
	$(NAMEDGROUPS_STATE) -i $(srcdir)/test_state.ngroups -o test_state.ngroups.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.ngroups.html test.ngroups.out.html
	$(DIFF) $(srcdir)/test_state.ngroups.html test_state.ngroups.out.html

.lang.err_out:
	$(CHECKLANG) ./$< 2> $@ || true; 
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

.outlang.err_out:
	$(CHECKOUTLANG) ./$< 2> $@ || true; 
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

.style.err_out:
	$(PROGEXE) --lang-def=$(srcdir)/simple.lang --style-file=./$< --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null 2> $@ || true;
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

.css.err_out:
	$(PROGEXE) --lang-def=$(srcdir)/simple.lang --style-css=./$< --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null 2> $@ || true;
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

check_wrong:
	rm -f *.err_out
	$(MAKE) wrong_exp.err_out
	$(MAKE) wrong_syntax.err_out
	$(MAKE) wrong_syntax_include.err_out
	$(MAKE) wrong_var.err_out
	$(MAKE) wrong_trans.err_out
	$(MAKE) wrong_dircolor.err_out
	$(MAKE) wrong_already_defined.err_out
	$(MAKE) wrong_already_defined_css.err_out
	$(MAKE) wrong_namedgroups.err_out
	$(MAKE) wrong_namedgroups_subexps.err_out
	$(MAKE) wrong_namedgroups_subexps2.err_out
	$(MAKE) wrong_backref.err_out
	$(MAKE) wrong_backref2.err_out
	$(MAKE) wrong_dyn_backref.err_out
	$(MAKE) wrong_dyn_backref2.err_out
	$(MAKE) wrong_include.err_out
	$(MAKE) wrong_outlang_include.err_out
	@echo expect no output from diff
	$(DIFF) $(srcdir)/wrong_exp.err wrong_exp.err_out
	$(DIFF) $(srcdir)/wrong_syntax.err wrong_syntax.err_out
	$(DIFF) $(srcdir)/wrong_syntax_include.err wrong_syntax_include.err_out
	$(DIFF) $(srcdir)/wrong_var.err wrong_var.err_out
	$(DIFF) $(srcdir)/wrong_trans.err wrong_trans.err_out
	$(DIFF) $(srcdir)/wrong_dircolor.err wrong_dircolor.err_out
	$(DIFF) $(srcdir)/wrong_already_defined.err wrong_already_defined.err_out
	$(DIFF) $(srcdir)/wrong_already_defined_css.err wrong_already_defined_css.err_out
	$(DIFF) $(srcdir)/wrong_namedgroups.err wrong_namedgroups.err_out
	$(DIFF) $(srcdir)/wrong_namedgroups_subexps.err wrong_namedgroups_subexps.err_out
	$(DIFF) $(srcdir)/wrong_namedgroups_subexps2.err wrong_namedgroups_subexps2.err_out
	$(DIFF) $(srcdir)/wrong_backref.err wrong_backref.err_out
	$(DIFF) $(srcdir)/wrong_backref2.err wrong_backref2.err_out
	$(DIFF) $(srcdir)/wrong_dyn_backref.err wrong_dyn_backref.err_out
	$(DIFF) $(srcdir)/wrong_dyn_backref2.err wrong_dyn_backref2.err_out
	$(DIFF) $(srcdir)/wrong_include.err wrong_include.err_out
	$(DIFF) $(srcdir)/wrong_outlang_include.err wrong_outlang_include.err_out

check_wrong_lineranges:
	rm -f *.err_out
	$(WRONGLINERANGEEXE) 2> wrong_line_range.err_out || true
	@echo expect no output from diff
	$(DIFF) $(srcdir)/wrong_line_range.err wrong_line_range.err_out

check_wrong_regexranges:
	rm -f *.err_out
	$(WRONGREGEXRANGEEXE) 2> wrong_regex_range.err_out || true
	@echo expect no output from diff
	$(DIFF) $(srcdir)/wrong_regex_range.err wrong_regex_range.err_out

check_wrong_syntaxmode:
	rm -f *.err_out
	$(WRONGSYNTAXMODEEXE) 2> wrong_syntax_mode.err_out || true
	@echo expect no output from diff
	$(DIFF) $(srcdir)/wrong_syntax_mode.err wrong_syntax_mode.err_out

check_lineranges:
	$(LINERANGE1EXE) < $(srcdir)/test.java -o test_linerange1.out.html
	$(LINERANGE2EXE) < $(srcdir)/test.java -o test_linerange2.out.html
	$(LINERANGESEPEXE) < $(srcdir)/test.java -o test_linerange_sep.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_linerange1.html test_linerange1.out.html
	$(DIFF) $(srcdir)/test_linerange2.html test_linerange2.out.html
	$(DIFF) $(srcdir)/test_linerange_sep.html test_linerange_sep.out.html

check_regexranges:
	$(REGEXRANGE1EXE) < $(srcdir)/test.java -o test_regexrange1.out.html
	$(REGEXRANGE2EXE) < $(srcdir)/test.java -o test_regexrange2.out.html
	$(REGEXRANGE3EXE) < $(srcdir)/test.java -o test_regexrange3.out.html
	$(REGEXRANGE4EXE) < $(srcdir)/test.java -o test_regexrange4.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_regexrange1.html test_regexrange1.out.html
	$(DIFF) $(srcdir)/test_regexrange2.html test_regexrange2.out.html
	$(DIFF) $(srcdir)/test_regexrange3.html test_regexrange3.out.html
	$(DIFF) $(srcdir)/test_regexrange4.html test_regexrange4.out.html

check_nobgcolor:
	$(PROGNAME) --style-file=texinfo.style --doc --title="source file" -i $(srcdir)/test_nobgcolor.cpp -o test_nobgcolor.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_nobgcolor.html test_nobgcolor.out.html

check_tabs:
	$(JAVA2HTML) --tab=4 -i $(srcdir)/test.java -o test_tabs.java.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_tabs.java.html test_tabs.java.out.html


#$(PROG_NOOUTLANGDEF) -i $(srcdir)/test.simple -o test.err_out --data-dir=/tmp 2-o missing_langmap2.err_out || true
#sed -r -i -f $(srcdir)/erasedir2.sed missing_langmap2.err_out
#diff $(srcdir)/missing_langmap2.err missing_langmap2.err_out

check_missing:
	rm -f *.err_out
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple -o test.err_out 2> missing_langmap.err_out || true
	$(PROG_NOOUTLANGDEF) --outlang-def=$(srcdir)/simple.outlang $(srcdir)/test.simple 2> missing_extension.err_out || true
	@echo expect no output from diff
	sed -itesttmp -f $(srcdir)/erasedir2.sed missing_langmap.err_out
	sed -itesttmp -f $(srcdir)/erasedir2.sed missing_extension.err_out
	$(DIFF) $(srcdir)/missing_langmap.err missing_langmap.err_out
	$(DIFF) $(srcdir)/missing_extension.err missing_extension.err_out
	rm -f *testtmp

check_failsafe:
	$(FAILSAFE) -i $(srcdir)/test.unknown -o test.unknown.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.unknown.html test.unknown.out.html

check_debug:
	rm -f *.out.debug
	$(DEBUGLANG) -i $(srcdir)/debug.java -o debug.java.out.html > debug.out.debug
	tr -d '\r' < debug.out.debug > temp.output && cp -f temp.output debug.out.debug
	@echo expect no output from diff
	$(DIFF) $(srcdir)/debug.debug debug.out.debug
	$(DIFF) $(srcdir)/debug.java.html debug.java.out.html

check_defaults:
	$(TESTWDEFAULTS) -i $(srcdir)/test.wdefault -o test.wdefault.out.html
	$(TESTWODEFAULTS) -i $(srcdir)/test.wodefault -o test.wodefault.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test.wdefault.html test.wdefault.out.html
	$(DIFF) $(srcdir)/test.wodefault.html test.wodefault.out.html

TEMP_TAGFILE=temp_test_refs.tags

# disable reference tests
if NO_CTAGS
check_ref:
	@echo warning: tests with references are disabled
	@echo because we could not find a usable ctags program
else
# sed -i -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.html # eliminate leading paths
check_ref:
	$(CPP2HTML_WREFS) -i $(srcdir)/test.h -o test_ref.out.html $(CTAGS_COMMAND_TMP)
	sed -itesttmp -e 's/test\_ref\.out\.html/test\_ref\.html/g' test_ref.out.html
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref.out.html # eliminate leading paths
	rm -f test_refs_tmp.* *testtmp
	cp -f $(srcdir)/test_refs.h test_refs_tmp.h
	cp -f $(srcdir)/test_refs.cpp test_refs_tmp.cpp
	$(CTAGS_CMD) -o $(TEMP_TAGFILE) test_refs_tmp.h test_refs_tmp.cpp
	$(CPP2HTML_WREFS) --ctags-file=$(TEMP_TAGFILE) --line-number test_refs_tmp.h test_refs_tmp.cpp --verbose
	sed -itesttmp -e 's/\_tmp\.h/\.h/g' test_refs_tmp.h.html test_refs_tmp.cpp.html
	sed -itesttmp -e 's/\_tmp\.cpp/\.cpp/g' test_refs_tmp.h.html test_refs_tmp.cpp.html
	$(CPP2LATEX_WREFS) -i $(srcdir)/test.h -o test_ref.out.tex $(CTAGS_COMMAND_TMP)
	sed -itesttmp -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.tex # eliminate leading paths
	$(CPP2LATEX_WREFSPOST) -i $(srcdir)/test.h -o test_ref_post.out.tex $(CTAGS_COMMAND_TMP)
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref_post.out.tex # eliminate leading paths
	$(CPP2TEXINFO_WREFS) -i $(srcdir)/test.h -o test_ref.out.texinfo $(CTAGS_COMMAND_TMP)
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref.out.texinfo # eliminate leading paths
	$(CPP2DOCBOOK_WREFS) -i $(srcdir)/test.h -o test_ref.out.docbook $(CTAGS_COMMAND_TMP)
	$(CPP2XHTML_WREFS) -i $(srcdir)/test.h -o test_ref.out.xhtml $(CTAGS_COMMAND_TMP)
	sed -itesttmp -e 's/test\_ref\.out\.xhtml/test\_ref\.xhtml/g' test_ref.out.xhtml
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref.out.xhtml # eliminate leading paths
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_ref.html test_ref.out.html
	$(DIFF) $(srcdir)/test_refs.h.html test_refs_tmp.h.html
	$(DIFF) $(srcdir)/test_refs.cpp.html test_refs_tmp.cpp.html
	$(DIFF) $(srcdir)/test_ref.tex test_ref.out.tex
	$(DIFF) $(srcdir)/test_ref.texinfo test_ref.out.texinfo
	$(DIFF) $(srcdir)/test_ref_post.tex test_ref_post.out.tex
	$(DIFF) $(srcdir)/test_ref.docbook test_ref.out.docbook
	$(DIFF) $(srcdir)/test_ref.xhtml test_ref.out.xhtml
	rm -f test_refs_tmp.* *testtmp $(TEMP_TAGFILE)
endif

check_show:
	$(PROGEXE) --show-regex=$(top_srcdir)/src/c_comment.lang > c_comment.out.show
	tr -d '\r' < c_comment.out.show > temp.output && cp -f temp.output c_comment.out.show
	$(PROGEXE) --show-regex=$(srcdir)/namedgroups_state.lang > namedgroups_state.out.show
	tr -d '\r' < namedgroups_state.out.show > temp.output && cp -f temp.output namedgroups_state.out.show
	@echo expect no output from diff
	$(DIFF) $(srcdir)/c_comment.show c_comment.out.show
	$(DIFF) $(srcdir)/namedgroups_state.show namedgroups_state.out.show

check_langelems:
	$(PROGEXE) $(DATADIROPTION) --show-lang-elements=$(top_srcdir)/src/cpp.lang > cpp.out.langelems
	tr -d '\r' < cpp.out.langelems > temp.output && cp -f temp.output cpp.out.langelems
	@echo expect no output from diff
	$(DIFF) $(srcdir)/cpp.langelems cpp.out.langelems

check_list:
	$(PROGEXE) $(DATADIROPTION) --lang-list > lang.out.list
	tr -d '\r' < lang.out.list > temp.output && cp -f temp.output lang.out.list
	$(PROGEXE) $(DATADIROPTION) --outlang-list > outlang.out.list
	tr -d '\r' < outlang.out.list > temp.output && cp -f temp.output outlang.out.list
	@echo expect no output from diff
	$(DIFF) $(srcdir)/lang.list lang.out.list
	$(DIFF) $(srcdir)/outlang.list outlang.out.list

check_stop:
	$(PROGNAME) --lang-def=$(srcdir)/test_string_stop.lang -i $(srcdir)/test_string_stop.java -o test_string_stop.java.out.html
	$(JAVA2HTML) -i $(srcdir)/test_java_stop.java -o test_java_stop.java.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_string_stop.java.html test_string_stop.java.out.html
	$(DIFF) $(srcdir)/test_java_stop.java.html test_java_stop.java.out.html

check_vardecl:
	$(JAVA2HTML) -i $(srcdir)/test_vardecl.java -o test_vardecl.java.out.html
	$(CPP2HTML) -i $(srcdir)/test_vardecl.cc -o test_vardecl.cc.out.html
	@echo expect no output from diff
	$(DIFF) $(srcdir)/test_vardecl.java.html test_vardecl.java.out.html
	$(DIFF) $(srcdir)/test_vardecl.cc.html test_vardecl.cc.out.html

check_newlines: 
	$(PROGEXE) --show-regex=$(srcdir)/test_newlines.lang > test_newlines.out
	$(PROGEXE) --show-regex=$(srcdir)/test_nonewlines.lang > test_nonewlines.out
	@echo expect no output from diff
	$(DIFF) test_newlines.out test_nonewlines.out


clean_ref: 
	rm -f $(OUTPUTWREFS)

OUTPUTDIR=$(top_builddir)/tests/output_dir
OUTPUTTODIR= --output-dir=$(OUTPUTDIR)

check-output-dir:
	rm -f $(OUTPUTDIR)/test.java.html $(OUTPUTDIR)/test.h.html
	$(PROGEXE) $(DATADIROPTION) $(OUTPUTTODIR) $(srcdir)/test.java $(srcdir)/test.h
	test -f $(OUTPUTDIR)/test.java.html
	test -f $(OUTPUTDIR)/test.h.html

source_highlightdoc_DATA = test.php3.html test.pl.html test.pm.html \
test.py.html test.rb.html test.js.html test.lua.html test.ml.html \
test.sml.html test.log.html access.log.html auth.log.html error.log.html syslog.log.html test.htm.html test.java.tex.html \
syslog.style.html \
log.lang.html c.lang.html default.style.html \
test_linerange_sep.html \
test.java.html \
test_regexrange4.html \
test_refs.h.html test_refs.cpp.html

VALGRINDTESTS = $(top_builddir)/tests/valgrind_tests.sh
VALGRINDTEST = $(top_builddir)/tests/valgrind_test.sh

check-valgrind:
	$(VALGRINDTEST) $(PROGEXE) --help
	$(VALGRINDTEST) $(PROGEXE) --version
	$(VALGRINDTEST) $(JAVA2HTML) -i $(srcdir)/test.java -o test.java.out.html
# lua uses @{1} so we want to test it
	$(VALGRINDTEST) $(LUA2HTML) -i $(srcdir)/test.lua -o test.lua.out.html
	$(VALGRINDTEST) $(PROGNAME_CSSSTYLE) -i $(srcdir)/test.java -o test.css.java.html
	$(VALGRINDTEST) $(CPP2HTML) --gen-references=inline -i $(srcdir)/test.h -o test_ref.out.html
	$(VALGRINDTEST) $(FAILSAFE) -i $(srcdir)/test.unknown -s cpp -o test.unknown_out
	$(VALGRINDTEST) $(NAMEDGROUPS) -i $(srcdir)/test.ngroups -o test.ngroups.out.html
	$(VALGRINDTEST) $(FAILSAFE) -i $(srcdir)/test.unknown -o test.unknown_out
	cp -f $(srcdir)/test_refs.h test_refs_tmp.h
	cp -f $(srcdir)/test_refs.cpp test_refs_tmp.cpp
	$(CTAGS_CMD) -o test_refs_tmp.tags test_refs_tmp.h test_refs_tmp.cpp
	$(VALGRINDTEST) $(CPP2HTML) --gen-references=inline --ctags-file=my_test_ref.tags --line-number test_refs_tmp.h test_refs_tmp.cpp
	rm -f test_refs_tmp.*

CLEANFILES = *.out.html *.out.txt *.out.tex *.err_out *.unknown_out *.out.debug *.out.texinfo *_tmp.* *.out.show myscript* myimplicitxml* myimplicitphp* *.css.java.html *.nf_css.java.html *.css_xhtml.java.html *.css_doc.java.html *.out.docbook *.out.xhtml *.out.langelems *.out.list test_newlines.out test_nonewlines.out temp.output *.out.fodt *.out.doc.fodt *.out.mediawiki

clean_html:
	rm -f *.h.html *.java.html *.cc.html *.pas.html *.pl.html *.pm.html *.php3.html *.py.html *.chlog.html *.chlog_css.html *.l.html test_xhtml*.html test_notfixed.html test_css.html test_css_nodoc.html test_header.html *.rb.html *.js.html *.java.txt *.java.tex *.h.docbook *.java.texinfo *.lua.html *.ml.html *.sml.html test_*_lines.html *.log.html *.y.html *.simple.html *.ngroups.html *.tex.html *.lgt.html *.diff.html *.lang.html *.htm.html *.style.html *.cs.html *.xml.html *.sh.html *.url.html *.txt.html *.unknown.html *.tcl.html *.bib.html *.makefile.html *.css.html *.ps.html *.sl.html *.isolate.html *.backref.html *.c.html *.wdefault.html *.wodefault.html *.properties.html *.desktop.html *.lsm.html *.spec.html *.hx.html *.fortran.html *.fixed-fortran.html *.hx.html *.m4.html *.scala.html *.adb.html *.conf.html *.xorg.html

DISTCLEANFILES=my_test_ref_tmp.tags $(TEMP_TAGFILE)

#DISTCLEANFILES=test_ref.xhtml test_ref.tags test_ref.tags tags test_ref.tex test_ref_post.tex test_ref.texinfo syslog.style.html test_ref.docbook
