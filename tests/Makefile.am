# Copyright (C) 1999-2007 Lorenzo Bettini <http://www.lorenzobettini.it>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

STD_STYLE = --style-file $(top_srcdir)/src/default.style
STD_CSS_STYLE = --style-css-file $(top_srcdir)/src/default.css
STD_STYLE_HTML = -f html $(STD_STYLE)
DATADIROPTION = --data-dir $(top_srcdir)/src/

PROGEXE = $(top_builddir)/src/$(PACKAGE)$(EXEEXT)

# we disable the generation of the version of source-highlight
# so that the version does not interfere with the diffing
PROGNAME = $(PROGEXE) --gen-version $(DATADIROPTION)
PROGNAME_CSSSTYLE = $(PROGEXE) --gen-version $(DATADIROPTION) $(STD_CSS_STYLE)
PROGNAME_DOCBOOK = $(PROGEXE) --gen-version $(DATADIROPTION) -f docbook --doc --title="listing in docbook" --tab=8

CHECKLANG = $(top_builddir)/src/$(PACKAGE)$(EXEEXT) --check-lang

CHECKOUTLANG = $(top_builddir)/src/$(PACKAGE)$(EXEEXT) --check-outlang

JAVA2HTML = $(PROGNAME) -s java $(STD_STYLE_HTML) 

JAVA2HTMLDOC = $(JAVA2HTML) --title="This is the title"

JS2HTML = $(PROGNAME) -s javascript $(STD_STYLE_HTML) 

URL2HTML = $(PROGNAME) --lang-def=url.lang $(STD_STYLE_HTML) 

JAVA2XHTML = $(PROGNAME) -s java -f xhtml $(STD_STYLE) --lang-def=$(srcdir)/../src/java.lang

JAVA2XHTMLDOC = $(JAVA2XHTML) --doc

JAVA2XHTMLCSS = $(JAVA2XHTML) --css ../doc/mono.css --no-doc

JAVA2XHTMLCSSDOC = $(JAVA2XHTML) --css ../doc/mono.css

JAVA2HTMLNOTFIXED = $(PROGNAME) -s java --outlang-def=$(srcdir)/../src/html_notfixed.outlang $(STD_STYLE) --doc --lang-def=$(srcdir)/../src/java.lang

JAVA2XHTMLNOTFIXED = $(PROGNAME) -s java --outlang-def=$(srcdir)/../src/xhtml_notfixed.outlang $(STD_STYLE) --doc --lang-def=$(srcdir)/../src/java.lang

JAVA2ESC = $(PROGNAME) -s java -f esc --style-file=$(top_srcdir)/src/esc.style --doc --lang-def=$(srcdir)/../src/java.lang

JAVA2TEX = $(PROGNAME) --doc -s java -f latexcolor $(STD_STYLE) --title="formatted with source-highlight"

CPP2TEX = $(PROGNAME) --doc -s cpp -f latexcolor $(STD_STYLE) 

JAVA2TEXINFO = $(PROGNAME) -s java -f texinfo --style-file $(top_srcdir)/src/texinfo.style

CPP2TEXINFO_WREFS = $(PROGNAME) -s cpp -f texinfo --style-file $(top_srcdir)/src/texinfo.style --gen-references=postline --line-number --ctags=""

# this refers to an "absolute" path (../doc/) without using the automake
# variables.  However this way the generated files will always be the
# same so tests won't fail.  You may have some problems if you want to
# view the generated file, test_css.html, and you are building in a
# different directory.  However this is not the spirit of the test :-)
# the important thing is that the generated file is always the same.
JAVA2HTMLCSS = $(PROGNAME) -s java -f html --css ../doc/mono.css --lang-def=$(srcdir)/../src/java.lang

JAVA2HTMLCSSNODOC = $(PROGNAME) -s java -f html --css ../doc/mono.css --no-doc --lang-def=$(srcdir)/../src/java.lang

CPP2HTML = $(PROGNAME) -s cpp $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/cpp.lang

CSHARP2HTML = $(PROGNAME) -s csharp $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/csharp.lang

PROLOG2HTML = $(PROGNAME) -s prolog $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/prolog.lang

PERL2HTML = $(PROGNAME) -s perl $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/perl.lang

PHP32HTML = $(PROGNAME) -s php3 $(STD_STYLE_HTML) --lang-def=$(srcdir)/../src/php.lang

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

TXT2HTML = $(PROGNAME) -s style $(STD_STYLE_HTML) --lang-def=default.lang

FAILSAFE = $(PROGNAME) --failsafe

INFER = $(PROGNAME) --infer-lang

# language inference is performed implicitly if everything else failed
INFERIMPLICIT = $(PROGNAME)

SIMPLE = $(PROGEXE) --gen-version --outlang-def=$(srcdir)/simple.outlang --lang-def=$(srcdir)/simple.lang $(STD_STYLE)

TESTISOLATE = $(PROGNAME) --lang-def=$(srcdir)/test_isolate.lang

TESTBACKREF = $(PROGNAME) --lang-def=$(srcdir)/test_backref.lang

# for testing named groups
NAMEDGROUPS = $(PROGEXE) --gen-version --lang-def=$(srcdir)/namedgroups.lang $(STD_STYLE) $(DATADIROPTION)
NAMEDGROUPS_STATE = $(PROGEXE) --gen-version --lang-def=$(srcdir)/namedgroups_state.lang $(STD_STYLE) $(DATADIROPTION)

DEBUGLANG = $(PROGNAME) -s java $(STD_STYLE_HTML) --debug-lang=dump

WRONGFILES = wrong_exp.lang wrong_var.lang wrong_trans.outlang wrong_syntax.lang wrong_namedgroups.lang wrong_namedgroups_subexps.lang wrong_namedgroups_subexps2.lang wrong_backref.lang wrong_backref2.lang wrong_dyn_backref.lang wrong_dyn_backref2.lang
WRONGFILESOUT = wrong_exp.err wrong_var.err wrong_trans.err missing_langmap.err missing_extension.err wrong_syntax.err wrong_namedgroups.err wrong_namedgroups_subexps.err wrong_namedgroups_subexps2.err wrong_backref.err wrong_backref2.err wrong_dyn_backref.err wrong_dyn_backref2.err
WRONGSTYLES = wrong_dircolor.style
WRONGSTYLESOUT = wrong_dircolor.err
# missing_langmap2.err

OUTPUTWREFS=test_ref.html test_refs.h.html test_refs.cpp.html test_ref.tex test_ref_post.tex test_ref.texinfo test_ref.docbook

EXTRA_DIST = test.java test.java.html test.java.doc.html \
test.js test.js.html test.h test.h.html \
test_comments.cc test_comments.cc.html test_comments.java \
test_comments.java.html test_template.cc test_template.cc.html \
test.pl test.pl.html header.html footer.html test_header.html \
test_java_lines.html test_cpp_lines.html test_pl_lines.html \
test.pm test_comments.pm test.pm.html test_comments.pm.html \
test_perl_lines.html \
test.php3 test.php3.html test_php3_lines.html \
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
test2.htm test2.htm.html \
test.diff test.diff.html \
test2.diff test2.diff.html \
test3.diff test3.diff.html \
test.simple test.simple.html \
test.unknown test.unknown.html \
syslog.style \
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
log.lang.html cpp.lang.html \
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
valgrind_tests.sh.in valgrind_suppressions.sh.in \
valgrind_test.sh.in suppressions.supp \
erasedir.sed erasedir2.sed erasedir3.sed \
namedgroups.lang namedgroups_state.lang \
test.ngroups test.ngroups.html \
test_state.ngroups test_state.ngroups.html \
c_comment.show namedgroups_state.show \
cpp.langelems \
test.h.docbook \
test.sl test.sl.html

SUFFIXES = .cs .cs.html .h .h.html .cc .cc.html .java .java.html .java.doc.html .css.java.html .css_xhtml.java.html .css_doc.java.html .nf_css.java.html .debug .js.html .java.txt .java.tex .java.texinfo .h.docbook .pl .pl.html .pm .pm.html .php3 .php3.html .py .py.html .chlog .chlog.htm .chlog_css.html .l .l.html .y .y.html .rb .rb.html .lua .lua.html .ml .ml.html .sml .sml.html .log .log.html .tex .tex.html .lgt .lgt.html .diff .diff.html .pas .pas.html .htm .htm.html .xml .xml.html .sh .sh.html .url .url.html .txt .txt.html .unknown .unknown.html .style .style.html .ps .ps.html .sl .sl.html .simple .simple.html .isolate .isolate.html .backref .backref.html _state.ngroups _state.ngroups.html .ngroups .ngroups.html .lang .err .outlang .err_out .show

c_comment.show: $(top_srcdir)/src/c_comment.lang
	$(PROGEXE) --show-regex=$(top_srcdir)/src/c_comment.lang > $@

.lang.show:
	$(PROGEXE) --show-regex=$< > $@

cpp.langelems: $(top_srcdir)/src/cpp.lang
	$(PROGEXE) $(DATADIROPTION) --show-lang-elements=$(top_srcdir)/src/cpp.lang > $@

.cc.cc.html:
	$(CPP2HTML) -i $< -o $@

.cs.cs.html:
	$(CSHARP2HTML) -i $< -o $@

.h.h.html:
	$(CPP2HTML) -i $< -o $@

.java.java.html:
	$(JAVA2HTML) -i $< -o $@

.java.java.doc.html:
	$(JAVA2HTMLDOC) -i $< -o $@

# these are files processed using a css as the style file
.java.css.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@

# these are files processed using a css as the style file
.java.css_xhtml.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@ -f xhtml

# these are files processed using a css as the style file
.java.css_doc.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@ --title="This is the title"

# these are files processed using a css as the style file and a non fixed html
.java.nf_css.java.html:
	$(PROGNAME_CSSSTYLE) -i $< -o $@ --outlang-def=$(srcdir)/../src/html_notfixed.outlang

debug.java.html: debug.java
	$(DEBUGLANG) -i $(srcdir)/debug.java -o debug.java.html > /dev/null

.java.debug:
	$(DEBUGLANG) -i $< -o debug.java.html > $@

.js.js.html:
	$(JS2HTML) $< 

.java.java.txt:
	$(JAVA2ESC) --line-number $< 

.java.java.tex:
	$(JAVA2TEX) --line-number=" " -i $< -o $@

.java.java.texinfo:
	$(JAVA2TEXINFO) --line-number -i $< -o $@

.h.h.docbook:
	$(PROGNAME_DOCBOOK) --line-number -i $< -o $@

.pl.pl.html:
	$(PROLOG2HTML) $<

.pm.pm.html:
	$(PERL2HTML) $<

.php3.php3.html:
	$(PHP32HTML) $<

.py.py.html:
	$(PYTHON2HTML) $<

.chlog.chlog.htm:
	$(CHANGELOG2HTML) $<

.chlog.chlog_css.html:
	$(CHANGELOG2HTMLCSS) -i $< > $@

.l.l.html:
	$(FLEX2HTML) $<

.y.y.html:
	$(BISON2HTML) $<

.rb.rb.html:
	$(RUBY2HTML) $<

.lua.lua.html:
	$(LUA2HTML) $<

.ml.ml.html:
	$(CAML2HTML) $<

.sml.sml.html:
	$(SML2HTML) $<

.log.log.html:
	$(LOG2HTML) $<

.tex.tex.html:
	$(LATEX2HTML) $<

.lgt.lgt.html:
	$(LOGTALK2HTML) $<

.diff.diff.html:
	$(DIFF2HTML) $<

.pas.pas.html:
	$(PROGNAME) $<

.htm.htm.html:
	$(PROGNAME) $< --title="html output formatted in html"

.xml.xml.html:
	$(PROGNAME) $< --title="xml formatted in html"

.sh.sh.html:
	$(PROGNAME) $< 

.url.url.html:
	$(URL2HTML) $< 

.txt.txt.html:
	$(TXT2HTML) $< 

.unknown.unknown.html:
	$(FAILSAFE) $< 

log.lang.html: $(top_srcdir)/src/log.lang
	$(LANG2HTML) -i $(top_srcdir)/src/log.lang -o $@

cpp.lang.html: $(top_srcdir)/src/cpp.lang
	$(LANG2HTML) -i $(top_srcdir)/src/cpp.lang -o $@

default.style.html: $(top_srcdir)/src/default.style
	$(STYLE2HTML) -i $(top_srcdir)/src/default.style -o $@

.style.style.html:
	$(STYLE2HTML) -i $< -o $@

.ps.ps.html:
	$(PROGNAME) -i $< -o $@

.java.htm:
	$(JAVA2HTML) -i $< --title="Java formatted in html" > $@
	echo "" >> $@
	echo "<!-- this is an" >> $@
	echo "     added HTML comment" >> $@
	echo "     at the end of the file -->" >> $@

.sl.sl.html:
	$(PROGNAME) -i $< -o $@ --title="S-LANG test"

.simple.simple.html:
	$(SIMPLE) -i $< -o $@

.isolate.isolate.html:
	$(TESTISOLATE) -i $< -o $@

.backref.backref.html:
	$(TESTBACKREF) -i $< -o $@

_state.ngroups_state.ngroups.html:
	$(NAMEDGROUPS_STATE) -i $< -o $@

.ngroups.ngroups.html:
	$(NAMEDGROUPS) -i $< -o $@

.lang.err:
	$(CHECKLANG) ./$< 2> $@ || true;
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

.outlang.err:
	$(CHECKOUTLANG) $< 2> $@ || true

.style.err:
	$(PROGEXE) --lang-def=$(srcdir)/simple.lang --style=$< --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null 2> $@ || true

PROG_NOLANGDEF=$(PROGEXE) --outlang-def=$(srcdir)/simple.outlang $(STD_STYLE) --data-dir=$(srcdir)/
PROG_NOOUTLANGDEF=$(PROGEXE) --lang-def=$(srcdir)/simple.lang $(STD_STYLE)

missing_langmap.err: test.simple
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple -o test.err_out 2> missing_langmap.err || true;
	sed -itesttmp -f $(srcdir)/erasedir2.sed missing_langmap.err && rm -f *testtmp

missing_extension.err: test.simple
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple 2> missing_extension.err || true;
	sed -itesttmp -f $(srcdir)/erasedir2.sed missing_extension.err && rm -f *testtmp

CPP2HTML_WHEADERS = $(CPP2HTML) --header=$(srcdir)/header.html --footer=$(srcdir)/footer.html

CPP2HTML_WREFS = $(CPP2HTML) --title="Contains references to tags" --gen-references=inline --ctags="$(CTAGS) --excmd=number --tag-relative=yes -o my_test_ref.tags"

CPP2LATEX_WREFS = $(CPP2TEX) --title="Contains references to tags" --gen-references=postline --line-number --ctags=""

CPP2LATEX_WREFSPOST = $(CPP2TEX) --title="Contains references to tags" --gen-references=postdoc --line-number --ctags=""

CPP2DOCBOOK_WREFS = $(PROGNAME_DOCBOOK) --gen-references=postline --line-number --ctags=""

CTAGS_CMD=$(CTAGS) --excmd=number --tag-relative=yes 

test_header.html: test.h
	$(CPP2HTML_WHEADERS) -i test.h -o $@

test_ref.tags: test.h
	$(CTAGS_CMD) -o test_ref.tags $(srcdir)/test.h

test_ref.html: test.h
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags -i $(srcdir)/test.h -o test_ref.html

test_ref.tex: test_ref.tags 
	$(CPP2LATEX_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.tex

test_ref.docbook: test_ref.tags 
	$(CPP2DOCBOOK_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.docbook

test_ref_post.tex: test_ref.tags 
	$(CPP2LATEX_WREFSPOST) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref_post.tex

test_ref.texinfo: test_ref.tags 
	$(CPP2TEXINFO_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.texinfo

# -r 's/\"([^[:blank:]]*)\/([[:alnum:]\._]*\#[[:alnum:]\._]+)\"/\"\2\"/g' -i
test_refs.h.html: test_refs.h test_refs.cpp
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags --line-number $(srcdir)/test_refs.h $(srcdir)/test_refs.cpp 
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_refs.h.html test_refs.cpp.html  && rm -f *testtmp # eliminate leading paths

test_refs.cpp.html: test_refs.h.html

test_java_lines.html: test.java
	$(JAVA2HTML) --line-number-ref -i test.java -o $@

test_xhtml.html: test.java
	$(JAVA2XHTML) < $(srcdir)/test.java > $@

test_xhtml_doc.html: test.java
	$(JAVA2XHTMLDOC) < $(srcdir)/test.java > $@

test_xhtml_css.html: test.java
	$(JAVA2XHTMLCSS) < $(srcdir)/test.java > $@

test_xhtml_css_doc.html: test.java
	$(JAVA2XHTMLCSSDOC) < $(srcdir)/test.java > $@

test_notfixed.html: test.java
	$(JAVA2HTMLNOTFIXED) < $(srcdir)/test.java > $@

test_xhtml_notfixed.html: test.java
	$(JAVA2XHTMLNOTFIXED) < $(srcdir)/test.java > $@

test_css.html: test.java
	$(JAVA2HTMLCSS) < test.java > $@

test_css_nodoc.html: test.java
	$(JAVA2HTMLCSSNODOC) < test.java > $@

test_cpp_lines.html: test.h
	$(CPP2HTML) --line-number -i test.h -o $@

test_pl_lines.html: test.pl
	$(PROLOG2HTML) --line-number -i test.pl -o $@

test2.pl.html: test2.pl
	$(INFER) -i test2.pl -o $@

test.tcl.html: test.tcl
	$(INFER) -i test.tcl -o $@

test.sql.html: test.sql
	$(PROGNAME) -i test.sql -o $@

test.bib.html: test.bib
	$(PROGNAME) -i test.bib -o $@

test.makefile.html: test.makefile
	$(PROGNAME) -i test.makefile -o $@

test.css.html: test.css
	$(PROGNAME) -i test.css -o $@

test_perl_lines.html: test.pm
	$(PERL2HTML) --line-number -i test.pm -o $@

test_php3_lines.html: test.php3
	$(PHP32HTML) --line-number -i test.php3 -o $@

test_python_lines.html: test.py
	$(PYTHON2HTML) --line-number -i test.py -o $@

test_py_comments_lines.html: test_comments.py
	$(PYTHON2HTML) --line-number -i test_comments.py -o $@

check: check_java2html check_java2xhtml check_cpp2html check_csharp2html \
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
check_txt \
check_sql \
check_bib \
check_infer \
check_wrong check_failsafe check_missing \
check_debug \
check_ref \
check_show \
check_makefile \
check_css \
check_ps \
check_docbook \
check_namedgroups \
check_slang

remove_css_html_files:
	rm -f *.css.java.html *.nf_css.java.html

remove_css_xhtml_files:
	rm -f *.css_xhtml.java.html

remove_css_doc_files:
	rm -f *.css_doc.java.html

check_java2html: remove_css_html_files remove_css_doc_files test.java.html test.java.doc.html test.js.html test.java.txt test.java.tex test.java.texinfo test_notfixed.html test_css.html test_css_nodoc.html test_comments.java.html test_java_lines.html test.css.java.html test.nf_css.java.html test.css_doc.java.html
	$(JAVA2HTML) -i $(srcdir)/test.java -o test.java.out.html
	$(JAVA2HTMLDOC) -i $(srcdir)/test.java -o test.java.doc.out.html
	$(JS2HTML) < $(srcdir)/test.js > test.js.out.html
	$(JAVA2HTMLNOTFIXED) < $(srcdir)/test.java > test_notfixed.out.html
	$(JAVA2HTMLCSS) < $(srcdir)/test.java > test_css.out.html
	$(JAVA2HTMLCSSNODOC) < $(srcdir)/test.java > test_css_nodoc.out.html
	$(JAVA2HTML) -i $(srcdir)/test_comments.java -o test_comments.java.out.html
	$(JAVA2HTML) -n --line-number-ref -i $(srcdir)/test.java -o test_java_lines.out.html
	$(JAVA2ESC) -n -i $(srcdir)/test.java -o test.java.out.txt
	$(JAVA2TEX) --line-number=" " -i $(srcdir)/test.java -o test.java.out.tex
	$(JAVA2TEXINFO) -n -i $(srcdir)/test.java -o test.java.out.texinfo
	@echo expect no output from diff
	diff $(srcdir)/test.java.html test.java.out.html
	diff $(srcdir)/test.java.doc.html test.java.doc.out.html
	diff $(srcdir)/test.js.html test.js.out.html
	diff $(srcdir)/test_notfixed.html test_notfixed.out.html
	diff $(srcdir)/test_css.html test_css.out.html
	diff $(srcdir)/test_css_nodoc.html test_css_nodoc.out.html
	diff $(srcdir)/test_comments.java.html test_comments.java.out.html
	diff $(srcdir)/test_java_lines.html test_java_lines.out.html
	diff $(srcdir)/test.java.txt test.java.out.txt
	diff $(srcdir)/test.java.tex test.java.out.tex
	diff $(srcdir)/test.java.texinfo test.java.out.texinfo
	diff $(srcdir)/test.java.html test.css.java.html
	diff $(srcdir)/test_notfixed.html test.nf_css.java.html
	diff $(srcdir)/test.java.doc.html test.css_doc.java.html

check_java2xhtml: remove_css_xhtml_files test_xhtml.html test_xhtml_notfixed.html test_xhtml_doc.html test_xhtml_css.html test_xhtml_css_doc.html test.css_xhtml.java.html
	$(JAVA2XHTML) < $(srcdir)/test.java > test_xhtml.out.html
	$(JAVA2XHTMLNOTFIXED) < $(srcdir)/test.java > test_xhtml_notfixed.out.html
	$(JAVA2XHTMLDOC) < $(srcdir)/test.java > test_xhtml_doc.out.html
	$(JAVA2XHTMLCSS) < $(srcdir)/test.java > test_xhtml_css.out.html
	$(JAVA2XHTMLCSSDOC) < $(srcdir)/test.java > test_xhtml_css_doc.out.html
	@echo expect no output from diff
	diff $(srcdir)/test_xhtml.html test_xhtml.out.html
	diff $(srcdir)/test_xhtml_notfixed.html test_xhtml_notfixed.out.html
	diff $(srcdir)/test_xhtml_doc.html test_xhtml_doc.out.html
	diff $(srcdir)/test_xhtml_css.html test_xhtml_css.out.html
	diff $(srcdir)/test_xhtml_css_doc.html test_xhtml_css_doc.out.html
	diff $(srcdir)/test_xhtml.html test.css_xhtml.java.html

check_cpp2html: test.h.html test_comments.cc.html test_template.cc.html test_header.html test_cpp_lines.html
	$(CPP2HTML) -i $(srcdir)/test.h > test.h.out.html
	$(CPP2HTML) -i $(srcdir)/test_comments.cc > test_comments.cc.out.html
	$(CPP2HTML) -i $(srcdir)/test_template.cc > test_template.cc.out.html
	$(CPP2HTML_WHEADERS) -i $(srcdir)/test.h -o test_header.out.html
	$(CPP2HTML) -n -i $(srcdir)/test.h -o test_cpp_lines.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.h.html test.h.out.html
	diff $(srcdir)/test_comments.cc.html test_comments.cc.out.html
	diff $(srcdir)/test_template.cc.html test_template.cc.out.html
	diff $(srcdir)/test_header.html test_header.out.html
	diff $(srcdir)/test_cpp_lines.html test_cpp_lines.out.html

check_csharp2html: test.cs.html 
	$(CSHARP2HTML) -i $(srcdir)/test.cs > test.cs.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.cs.html test.cs.out.html

check_prolog2html: test.pl.html test_pl_lines.html
	$(PROLOG2HTML) < $(srcdir)/test.pl > test.pl.out.html
	$(PROLOG2HTML) -n -i $(srcdir)/test.pl -o test_pl_lines.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.pl.html test.pl.out.html
	diff $(srcdir)/test_pl_lines.html test_pl_lines.out.html

check_logtalk2html: test.lgt.html
	$(LOGTALK2HTML) < $(srcdir)/test.lgt > test.lgt.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.lgt.html test.lgt.out.html

check_perl2html: test.pm.html test_comments.pm.html test_perl_lines.html
	$(PERL2HTML) < $(srcdir)/test.pm > test.pm.out.html
	$(PERL2HTML) < $(srcdir)/test_comments.pm > test_comments.pm.out.html
	$(PERL2HTML) -n -i $(srcdir)/test.pm -o test_perl_lines.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.pm.html test.pm.out.html
	diff $(srcdir)/test_comments.pm.html test_comments.pm.out.html 
	diff $(srcdir)/test_perl_lines.html test_perl_lines.out.html

check_php32html: test.php3.html test_php3_lines.html
	$(PHP32HTML) < $(srcdir)/test.php3 > test.php3.out.html
	$(PHP32HTML) -n -i $(srcdir)/test.php3 -o test_php3_lines.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.php3.html test.php3.out.html
	diff $(srcdir)/test_php3_lines.html test_php3_lines.out.html

check_python2html: test.py.html test_python_lines.html test_comments.py.html test_py_comments_lines.html
	$(PYTHON2HTML) < $(srcdir)/test.py > test.py.out.html
	$(PYTHON2HTML) < $(srcdir)/test_comments.py > test_comments.py.out.html
	$(PYTHON2HTML) -n -i $(srcdir)/test.py -o test_python_lines.out.html
	$(PYTHON2HTML) -n -i $(srcdir)/test_comments.py -o test_py_comments_lines.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.py.html test.py.out.html
	diff $(srcdir)/test_comments.py.html test_comments.py.out.html
	diff $(srcdir)/test_python_lines.html test_python_lines.out.html
	diff $(srcdir)/test_py_comments_lines.html test_py_comments_lines.out.html

check_changelog: test.chlog.html test.chlog_css.html
	$(CHANGELOG2HTML) < $(srcdir)/test.chlog > test.chlog.out.html
	$(CHANGELOG2HTMLCSS) -i $(srcdir)/test.chlog > test.chlog_css.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.chlog.html test.chlog.out.html
	diff $(srcdir)/test.chlog_css.html test.chlog_css.out.html

check_flex: test.l.html
	$(FLEX2HTML) < $(srcdir)/test.l > test.l.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.l.html test.l.out.html

check_bison: test.y.html
	$(BISON2HTML) < $(srcdir)/test.y > test.y.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.y.html test.y.out.html

check_ruby: test.rb.html test_comments.rb.html
	$(RUBY2HTML) < $(srcdir)/test.rb > test.rb.out.html
	$(RUBY2HTML) < $(srcdir)/test_comments.rb > test_comments.rb.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.rb.html test.rb.out.html
	diff $(srcdir)/test_comments.rb.html test_comments.rb.out.html

check_lua: test.lua.html
	$(LUA2HTML) < $(srcdir)/test.lua > test.lua.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.lua.html test.lua.out.html

check_ml: test.ml.html
	$(CAML2HTML) < $(srcdir)/test.ml > test.ml.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.ml.html test.ml.out.html

check_sml: test.sml.html
	$(SML2HTML) < $(srcdir)/test.sml > test.sml.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.sml.html test.sml.out.html

check_log: test.log.html access.log.html auth.log.html error.log.html syslog.log.html
	$(LOG2HTML) < $(srcdir)/test.log > test.log.out.html
	$(LOG2HTML) < $(srcdir)/access.log > access.log.out.html
	$(LOG2HTML) < $(srcdir)/auth.log > auth.log.out.html
	$(LOG2HTML) < $(srcdir)/error.log > error.log.out.html
	$(LOG2HTML) < $(srcdir)/syslog.log > syslog.log.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.log.html test.log.out.html
	diff $(srcdir)/access.log.html access.log.out.html
	diff $(srcdir)/auth.log.html auth.log.out.html
	diff $(srcdir)/error.log.html error.log.out.html
	diff $(srcdir)/syslog.log.html syslog.log.out.html

check_diff: test.diff.html test2.diff.html test3.diff.html
	$(DIFF2HTML) < $(srcdir)/test.diff > test.diff.out.html
	$(DIFF2HTML) < $(srcdir)/test2.diff > test2.diff.out.html
	$(DIFF2HTML) < $(srcdir)/test3.diff > test3.diff.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.diff.html test.diff.out.html
	diff $(srcdir)/test2.diff.html test2.diff.out.html
	diff $(srcdir)/test3.diff.html test3.diff.out.html

check_pascal: test.pas.html
	$(PROGNAME) -i $(srcdir)/test.pas > test.pas.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.pas.html test.pas.out.html

check_html: test.htm.html test2.htm.html
	$(PROGNAME) -i $(srcdir)/test.htm --title="html output formatted in html" > test.htm.out.html
	$(PROGNAME) -i $(srcdir)/test2.htm --title="html output formatted in html" > test2.htm.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.htm.html test.htm.out.html
	diff $(srcdir)/test2.htm.html test2.htm.out.html

check_xml: test.xml.html
	$(PROGNAME) -i $(srcdir)/test.xml --title="xml formatted in html" > test.xml.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.xml.html test.xml.out.html

check_sh: test.sh.html test2.sh.html
	$(PROGNAME) -i $(srcdir)/test.sh > test.sh.out.html
	$(PROGNAME) -i $(srcdir)/test2.sh > test2.sh.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.sh.html test.sh.out.html
	diff $(srcdir)/test2.sh.html test2.sh.out.html

check_slang: test.sl.html
	$(PROGNAME) -i $(srcdir)/test.sl -o test.sl.out.html --title="S-LANG test"
	@echo expect no output from diff
	diff $(srcdir)/test.sl.html test.sl.out.html

check_url: test.url.html
	$(URL2HTML) -i $(srcdir)/test.url > test.url.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.url.html test.url.out.html

check_txt: test.txt.html
	$(TXT2HTML) -i $(srcdir)/test.txt > test.txt.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.txt.html test.txt.out.html

myscript: test.sh
	cp $(srcdir)/test.sh $@

check_infer: test2.pl.html myscript test.sh.html test.tcl.html
	rm -f myscript.html
	$(INFER) -i $(srcdir)/test2.pl > test2.pl.out.html
	$(INFER) -i $(srcdir)/test.tcl > test.tcl.out.html
	$(INFERIMPLICIT) -i myscript > myscript.html
	@echo expect no output from diff
	diff $(srcdir)/test2.pl.html test2.pl.out.html
	diff $(srcdir)/test.tcl.html test.tcl.out.html
	diff $(srcdir)/test.sh.html myscript.html

check_latex: test.tex.html test.java.tex.html
	$(PROGNAME) -i $(srcdir)/test.tex  > test.tex.out.html
	$(PROGNAME) -i $(srcdir)/test.java.tex  > test.java.tex.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.tex.html test.tex.out.html
	diff $(srcdir)/test.java.tex.html test.java.tex.out.html

check_docbook: test.h.docbook
	$(PROGNAME_DOCBOOK) -i $(srcdir)/test.h --line-number > test.h.out.docbook
	@echo expect no output from diff
	diff $(srcdir)/test.h.docbook test.h.out.docbook

check_sql: test.sql.html
	$(PROGNAME) -i $(srcdir)/test.sql > test.sql.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.sql.html test.sql.out.html

check_bib: test.bib.html
	$(PROGNAME) -i $(srcdir)/test.bib > test.bib.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.bib.html test.bib.out.html

check_makefile: test.makefile.html
	$(PROGNAME) -i $(srcdir)/test.makefile > test.makefile.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.makefile.html test.makefile.out.html

check_css: test.css.html
	$(PROGNAME) -i $(srcdir)/test.css > test.css.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.css.html test.css.out.html

check_ps: test.ps.html
	$(PROGNAME) -i $(srcdir)/test.ps > test.ps.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.ps.html test.ps.out.html

check_lang: log.lang.html cpp.lang.html default.style.html
	$(LANG2HTML) -i $(top_srcdir)/src/log.lang -o log.lang.out.html
	$(LANG2HTML) -i $(top_srcdir)/src/cpp.lang -o cpp.lang.out.html
	$(STYLE2HTML) -i $(top_srcdir)/src/default.style -o default.style.out.html
	@echo expect no output from diff
	diff $(srcdir)/log.lang.html log.lang.out.html
	diff $(srcdir)/cpp.lang.html cpp.lang.out.html
	diff $(srcdir)/default.style.html default.style.out.html

check_simple: test.simple.html
	$(SIMPLE) -i $(srcdir)/test.simple -o test.simple.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.simple.html test.simple.out.html

check_isolate: test.isolate.html
	$(TESTISOLATE) -i $(srcdir)/test.isolate -o test.isolate.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.isolate.html test.isolate.out.html

check_backref: test.backref.html test2.backref.html
	$(TESTBACKREF) -i $(srcdir)/test.backref -o test.backref.out.html
	$(TESTBACKREF) -i $(srcdir)/test2.backref -o test2.backref.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.backref.html test.backref.out.html
	diff $(srcdir)/test2.backref.html test2.backref.out.html

check_namedgroups: test.ngroups.html test_state.ngroups.html
	$(NAMEDGROUPS) -i $(srcdir)/test.ngroups -o test.ngroups.out.html
	$(NAMEDGROUPS_STATE) -i $(srcdir)/test_state.ngroups -o test_state.ngroups.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.ngroups.html test.ngroups.out.html
	diff $(srcdir)/test_state.ngroups.html test_state.ngroups.out.html

.lang.err_out:
	$(CHECKLANG) ./$< 2> $@ || true; 
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

.outlang.err_out:
	$(CHECKOUTLANG) ./$< 2> $@ || true; 
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

.style.err_out:
	$(PROGEXE) --lang-def=$(srcdir)/simple.lang --style=$(srcdir)/$< --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null 2> $@ || true;
	sed -itesttmp -f $(srcdir)/erasedir.sed $@ && rm -f *testtmp

check_wrong: $(WRONGFILESOUT) $(WRONGSTYLESOUT)
	rm -f *.err_out
	$(MAKE) wrong_exp.err_out
	$(MAKE) wrong_syntax.err_out
	$(MAKE) wrong_var.err_out
	$(MAKE) wrong_trans.err_out
	$(MAKE) wrong_dircolor.err_out
	$(MAKE) wrong_namedgroups.err_out
	$(MAKE) wrong_namedgroups_subexps.err_out
	$(MAKE) wrong_namedgroups_subexps2.err_out
	$(MAKE) wrong_backref.err_out
	$(MAKE) wrong_backref2.err_out
	$(MAKE) wrong_dyn_backref.err_out
	$(MAKE) wrong_dyn_backref2.err_out
	@echo expect no output from diff
	diff $(srcdir)/wrong_exp.err wrong_exp.err_out
	diff $(srcdir)/wrong_syntax.err wrong_syntax.err_out
	diff $(srcdir)/wrong_var.err wrong_var.err_out
	diff $(srcdir)/wrong_trans.err wrong_trans.err_out
	diff $(srcdir)/wrong_dircolor.err wrong_dircolor.err_out
	diff $(srcdir)/wrong_namedgroups.err wrong_namedgroups.err_out
	diff $(srcdir)/wrong_namedgroups_subexps.err wrong_namedgroups_subexps.err_out
	diff $(srcdir)/wrong_namedgroups_subexps2.err wrong_namedgroups_subexps2.err_out
	diff $(srcdir)/wrong_backref.err wrong_backref.err_out
	diff $(srcdir)/wrong_backref2.err wrong_backref2.err_out
	diff $(srcdir)/wrong_dyn_backref.err wrong_dyn_backref.err_out
	diff $(srcdir)/wrong_dyn_backref2.err wrong_dyn_backref2.err_out

#$(PROG_NOOUTLANGDEF) -i $(srcdir)/test.simple -o test.err_out --data-dir=/tmp 2> missing_langmap2.err_out || true
#sed -r -i -f $(srcdir)/erasedir2.sed missing_langmap2.err_out
#diff $(srcdir)/missing_langmap2.err missing_langmap2.err_out

check_missing: missing_extension.err missing_langmap.err
	rm -f *.err_out
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple -o test.err_out 2> missing_langmap.err_out || true
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple 2> missing_extension.err_out || true
	@echo expect no output from diff
	sed -itesttmp -f $(srcdir)/erasedir2.sed missing_langmap.err_out
	sed -itesttmp -f $(srcdir)/erasedir2.sed missing_extension.err_out
	diff $(srcdir)/missing_langmap.err missing_langmap.err_out
	diff $(srcdir)/missing_extension.err missing_extension.err_out
	rm -f *testtmp

check_failsafe: test.unknown.html
	$(FAILSAFE) -i $(srcdir)/test.unknown -o test.unknown.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.unknown.html test.unknown.out.html

check_debug: debug.debug debug.java.html
	rm -f *.out.debug
	$(DEBUGLANG) -i $(srcdir)/debug.java -o debug.java.out.html > debug.out.debug
	@echo expect no output from diff
	diff $(srcdir)/debug.debug debug.out.debug
	diff $(srcdir)/debug.java.html debug.java.out.html

# disable reference tests
if NO_CTAGS
check_ref:
	@echo warning: tests with references are disable
	@echo because we could not find a usable ctags program
else
# sed -i -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.html # eliminate leading paths
check_ref: $(OUTPUTWREFS)
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags -i $(srcdir)/test.h -o test_ref.out.html
	sed -itesttmp -e 's/test\_ref\.out\.html/test\_ref\.html/g' test_ref.out.html
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref.out.html # eliminate leading paths
	rm -f test_refs_tmp.* *testtmp
	cp -f $(srcdir)/test_refs.h test_refs_tmp.h
	cp -f $(srcdir)/test_refs.cpp test_refs_tmp.cpp
	$(CTAGS_CMD) -o test_refs_tmp.tags test_refs_tmp.h test_refs_tmp.cpp
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags --line-number test_refs_tmp.h test_refs_tmp.cpp --verbose
	sed -itesttmp -e 's/\_tmp\.h/\.h/g' test_refs_tmp.h.html test_refs_tmp.cpp.html
	sed -itesttmp -e 's/\_tmp\.cpp/\.cpp/g' test_refs_tmp.h.html test_refs_tmp.cpp.html
	$(CPP2LATEX_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.out.tex
	sed -itesttmp -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.tex # eliminate leading paths
	$(CPP2LATEX_WREFSPOST) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref_post.out.tex
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref_post.out.tex # eliminate leading paths
	$(CPP2TEXINFO_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.out.texinfo
	sed -itesttmp -f $(srcdir)/erasedir3.sed test_ref.out.texinfo # eliminate leading paths
	$(CPP2DOCBOOK_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.out.docbook
	@echo expect no output from diff
	diff $(srcdir)/test_ref.html test_ref.out.html
	diff $(srcdir)/test_refs.h.html test_refs_tmp.h.html
	diff $(srcdir)/test_refs.cpp.html test_refs_tmp.cpp.html
	diff $(srcdir)/test_ref.tex test_ref.out.tex
	diff $(srcdir)/test_ref.texinfo test_ref.out.texinfo
	diff $(srcdir)/test_ref_post.tex test_ref_post.out.tex
	diff $(srcdir)/test_ref.docbook test_ref.out.docbook
	rm -f test_refs_tmp.* *testtmp
endif

check_show: namedgroups_state.show
	$(PROGEXE) --show-regex=$(top_srcdir)/src/c_comment.lang > c_comment.out.show
	$(PROGEXE) --show-regex=$(srcdir)/namedgroups_state.lang > namedgroups_state.out.show
	@echo expect no output from diff
	diff $(srcdir)/c_comment.show c_comment.out.show
	diff $(srcdir)/namedgroups_state.show namedgroups_state.out.show

check_langelems: cpp.langelems
	$(PROGEXE) $(DATADIROPTION) --show-lang-elements=$(top_srcdir)/src/cpp.lang > cpp.out.langelems
	@echo expect no output from diff
	diff $(srcdir)/cpp.langelems cpp.out.langelems

clean_ref: 
	rm -f $(OUTPUTWREFS)

source_highlightdoc_DATA = test.php3.html test.pl.html test.pm.html \
test.py.html test.rb.html test.js.html test.lua.html test.ml.html \
test.sml.html test.log.html access.log.html auth.log.html error.log.html syslog.log.html test.htm.html test.java.tex.html \
syslog.style.html \
log.lang.html cpp.lang.html default.style.html

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

CLEANFILES = *.out.html *.out.txt *.out.tex *.err_out *.unknown_out *.out.debug *.out.texinfo *_tmp.* *.out.show myscript* *.css.java.html *.nf_css.java.html *.css_xhtml.java.html *.css_doc.java.html *.out.docbook

clean_html:
	rm -f *.h.html *.java.html *.cc.html *.pas.html *.pl.html *.pm.html *.php3.html *.py.html *.chlog.html *.chlog_css.html *.l.html test_xhtml*.html test_notfixed.html test_css.html test_css_nodoc.html test_header.html *.rb.html *.js.html *.java.txt *.java.tex *.h.docbook *.java.texinfo *.lua.html *.ml.html *.sml.html test_*_lines.html *.log.html *.y.html *.simple.html *.ngroups.html *.tex.html *.lgt.html *.diff.html *.lang.html *.htm.html *.style.html *.cs.html *.xml.html *.sh.html *.url.html *.txt.html *.unknown.html *.tcl.html *.bib.html *.makefile.html *.css.html *.ps.html *.sl.html *.isolate.html *.backref.html

DISTCLEANFILES=test_ref.html test_ref.tags my_test_ref.tags tags test_ref.tex test_ref_post.tex test_ref.texinfo syslog.style.html test_ref.docbook