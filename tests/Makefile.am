# Copyright (C) 1999, 2000, 2001, 2002 Lorenzo Bettini <http://www.lorenzobettini.it>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

STD_STYLE = --style-file $(top_srcdir)/src/default.style
STD_STYLE_HTML = -f html $(STD_STYLE)
DATADIROPTION = --data-dir $(top_srcdir)/src/

PROGEXE = $(top_builddir)/src/$(PACKAGE)$(EXEEXT)

# we disable the generation of the version of source-highlight
# so that the version does not interfere with the diffing
PROGNAME = $(PROGEXE) --gen-version $(DATADIROPTION)

CHECKLANG = $(top_builddir)/src/$(PACKAGE)$(EXEEXT) --check-lang

JAVA2HTML = $(PROGNAME) -s java $(STD_STYLE_HTML) 

JS2HTML = $(PROGNAME) -s javascript $(STD_STYLE_HTML) 

JAVA2XHTML = $(PROGNAME) -s java -f xhtml $(STD_STYLE) --doc --lang-def=$(srcdir)/../src/java.lang

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

FAILSAFE = $(PROGNAME) --failsafe

SIMPLE = $(PROGEXE) --gen-version --outlang-def=$(srcdir)/simple.outlang --lang-def=$(srcdir)/simple.lang $(STD_STYLE)

DEBUGLANG = $(PROGNAME) -s java $(STD_STYLE_HTML) --debug-lang

WRONGFILES = wrong_exp.lang wrong_var.lang
WRONGFILESOUT = wrong_exp.err wrong_var.err missing_langmap.err missing_extension.err
WRONGSTYLES = wrong_dircolor.style
WRONGSTYLESOUT = wrong_dircolor.err
# missing_langmap2.err

OUTPUTWREFS=test_ref.html test_refs.h.html test_refs.cpp.html test_ref.tex test_ref_post.tex test_ref.texinfo

EXTRA_DIST = test.java test.java.html test.js test.js.html test.h test.h.html \
test_comments.cc test_comments.cc.html test_comments.java \
test_comments.java.html test_template.cc test_template.cc.html \
test.pl test.pl.html header.html footer.html test_header.html \
test_java_lines.html test_cpp_lines.html test_pl_lines.html \
test.pm test_comments.pm test.pm.html test_comments.pm.html \
test_perl_lines.html \
test.php3 test.php3.html test_php3_lines.html \
test.py test.py.html test_python_lines.html \
test_comments.py test_comments.py.html test_py_comments_lines.html \
test_xhtml.html test_css.html test_css_nodoc.html \
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
test.diff test.diff.html \
test2.diff test2.diff.html \
test3.diff test3.diff.html \
test.simple test.simple.html \
test.unknown \
syslog.style \
test.tex test.tex.html \
test.lgt test.lgt.html \
$(OUTPUTWREFS) \
test_refs.h test_refs.cpp \
changelog.css \
simple.lang simple.outlang \
log.lang.html cpp.lang.html \
default.style.html \
lang.map \
debug.debug debug.java \
test_extreme_comment.cpp test_extreme_comment2.cpp test_extreme_comment3.cpp \
test.cs test.cs.html \
$(WRONGFILES) \
$(WRONGFILESOUT) \
$(WRONGSTYLES) $(WRONGSTYLESOUT) \
valgrind_tests.sh.in valgrind_test.sh.in suppressions.supp \
erasedir.sed erasedir2.sed \
c_comment.show

%.show: $(top_srcdir)/src/%.lang
	$(PROGEXE) --show-regex=$< > $@

%.cc.html: %.cc
	$(CPP2HTML) -i $< -o $@

%.cs.html: %.cs
	$(CSHARP2HTML) -i $< -o $@

%.h.html: %.h
	$(CPP2HTML) -i $< -o $@

%.java.html: %.java
	$(JAVA2HTML) -i $< -o $@

%.debug: %.java
	$(DEBUGLANG) -i $< -o /dev/null > $@

%.js.html: %.js
	$(JS2HTML) $< 

%.java.txt: %.java
	$(JAVA2ESC) --line-number $< 

%.java.tex: %.java
	$(JAVA2TEX) --line-number -i $< -o $@

%.java.texinfo: %.java
	$(JAVA2TEXINFO) --line-number -i $< -o $@

%.pl.html: %.pl
	$(PROLOG2HTML) $<

%.pm.html: %.pm
	$(PERL2HTML) $<

%.php3.html: %.php3
	$(PHP32HTML) $<

%.py.html: %.py
	$(PYTHON2HTML) $<

%.chlog.html: %.chlog
	$(CHANGELOG2HTML) $<

%.chlog_css.html: %.chlog
	$(CHANGELOG2HTMLCSS) -i $< > $@

%.l.html: %.l
	$(FLEX2HTML) $<

%.y.html: %.y
	$(BISON2HTML) $<

%.rb.html: %.rb
	$(RUBY2HTML) $<

%.lua.html: %.lua
	$(LUA2HTML) $<

%.ml.html: %.ml
	$(CAML2HTML) $<

%.sml.html: %.sml
	$(SML2HTML) $<

%.log.html: %.log
	$(LOG2HTML) $<

%.tex.html: %.tex
	$(LATEX2HTML) $<

%.lgt.html: %.lgt
	$(LOGTALK2HTML) $<

%.diff.html: %.diff
	$(DIFF2HTML) $<

%.pas.html: %.pas
	$(PROGNAME) $<

%.htm.html: %.htm
	$(PROGNAME) $< --title="html output formatted in html"

%.lang.html: $(top_srcdir)/src/%.lang
	$(LANG2HTML) -i $< -o $@

%.style.html: $(top_srcdir)/src/%.style
	$(STYLE2HTML) -i $< -o $@

%.htm: %.java
	$(JAVA2HTML) -i $< --title="Java formatted in html" > $@
	echo "" >> $@
	echo "<!-- this is an" >> $@
	echo "     added HTML comment" >> $@
	echo "     at the end of the file -->" >> $@

%.simple.html: %.simple
	$(SIMPLE) -i $< -o $@

%.err: %.lang
	$(CHECKLANG) $< 2> $@ || true

%.err: %.style
	$(PROGEXE) --lang-def=$(srcdir)/simple.lang --style=$< --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null 2> $@ || true

PROG_NOLANGDEF=$(PROGEXE) --outlang-def=$(srcdir)/simple.outlang $(STD_STYLE) --data-dir=$(srcdir)/
PROG_NOOUTLANGDEF=$(PROGEXE) --lang-def=$(srcdir)/simple.lang $(STD_STYLE)

missing_langmap.err: test.simple
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple -o test.err_out 2> missing_langmap.err || true;
	sed -r -i -f $(srcdir)/erasedir2.sed missing_langmap.err
#missing_langmap2.err: test.simple
#	$(PROG_NOOUTLANGDEF) -i $(srcdir)/test.simple -o test.err_out 2> missing_langmap2.err || true;
#	sed -r -i -f $(srcdir)/erasedir2.sed missing_langmap2.err
missing_extension.err: test.simple
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple 2> missing_extension.err || true;
	sed -r -i -f $(srcdir)/erasedir2.sed missing_extension.err

CPP2HTML_WHEADERS = $(CPP2HTML) --header=$(srcdir)/header.html --footer=$(srcdir)/footer.html --title="Header and footer test"

CPP2HTML_WREFS = $(CPP2HTML) --title="Contains references to tags" --gen-references=inline --ctags="ctags --excmd=n --tag-relative=yes -o my_test_ref.tags"

CPP2LATEX_WREFS = $(CPP2TEX) --title="Contains references to tags" --gen-references=postline --line-number --ctags=""

CPP2LATEX_WREFSPOST = $(CPP2TEX) --title="Contains references to tags" --gen-references=postdoc --line-number --ctags=""

CTAGS_CMD=$(CTAGS) --excmd=n --tag-relative=yes 

test_header.html: test.h
	$(CPP2HTML_WHEADERS) -i test.h -o $@

test_ref.tags: test.h
	$(CTAGS_CMD) -o test_ref.tags $(srcdir)/test.h

test_ref.html: test.h
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags -i $(srcdir)/test.h -o test_ref.html

test_ref.tex: test_ref.tags 
	$(CPP2LATEX_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.tex

test_ref_post.tex: test_ref.tags 
	$(CPP2LATEX_WREFSPOST) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref_post.tex

test_ref.texinfo: test_ref.tags 
	$(CPP2TEXINFO_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.texinfo

test_refs.h.html: test_refs.h test_refs.cpp
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags --line-number $(srcdir)/test_refs.h $(srcdir)/test_refs.cpp 
	sed -r 's/\"([^[:blank:]]*)\/([[:alnum:]\._]*\#[[:alnum:]\._]+)\"/\"\2\"/g' -i test_refs.h.html test_refs.cpp.html # eliminate leading paths

test_refs.cpp.html: test_refs.h.html

test_java_lines.html: test.java
	$(JAVA2HTML) --line-number-ref -i test.java -o $@

test_xhtml.html: test.java
	$(JAVA2XHTML) < $(srcdir)/test.java > $@

test_css.html: test.java
	$(JAVA2HTMLCSS) < test.java > $@

test_css_nodoc.html: test.java
	$(JAVA2HTMLCSSNODOC) < test.java > $@

test_cpp_lines.html: test.h
	$(CPP2HTML) --line-number -i test.h -o $@

test_pl_lines.html: test.pl
	$(PROLOG2HTML) --line-number -i test.pl -o $@

test_perl_lines.html: test.pm
	$(PERL2HTML) --line-number -i test.pm -o $@

test_php3_lines.html: test.php3
	$(PHP32HTML) --line-number -i test.php3 -o $@

test_python_lines.html: test.py
	$(PYTHON2HTML) --line-number -i test.py -o $@

test_py_comments_lines.html: test_comments.py
	$(PYTHON2HTML) --line-number -i test_comments.py -o $@

check: check_java2html check_cpp2html check_csharp2html \
check_prolog2html check_logtalk2html \
check_perl2html \
check_php32html check_python2html check_changelog check_flex check_bison \
check_ruby check_lua check_ml check_sml check_log check_pascal check_html \
check_latex \
check_diff \
check_simple \
check_lang \
check_wrong check_failsafe check_missing \
check_debug \
check_ref \
check_show

check_java2html: test.java.html test.js.html test.java.txt test.java.tex test.java.texinfo test_xhtml.html test_css.html test_css_nodoc.html test_comments.java.html test_java_lines.html 
	$(JAVA2HTML) -i $(srcdir)/test.java -o test.java.out.html
	$(JS2HTML) < $(srcdir)/test.js > test.js.out.html
	$(JAVA2XHTML) < $(srcdir)/test.java > test_xhtml.out.html
	$(JAVA2HTMLCSS) < $(srcdir)/test.java > test_css.out.html
	$(JAVA2HTMLCSSNODOC) < $(srcdir)/test.java > test_css_nodoc.out.html
	$(JAVA2HTML) -i $(srcdir)/test_comments.java -o test_comments.java.out.html
	$(JAVA2HTML) -n --line-number-ref -i $(srcdir)/test.java -o test_java_lines.out.html
	$(JAVA2ESC) -n -i $(srcdir)/test.java -o test.java.out.txt
	$(JAVA2TEX) -n -i $(srcdir)/test.java -o test.java.out.tex
	$(JAVA2TEXINFO) -n -i $(srcdir)/test.java -o test.java.out.texinfo
	@echo expect no output from diff
	diff $(srcdir)/test.java.html test.java.out.html
	diff $(srcdir)/test.js.html test.js.out.html
	diff $(srcdir)/test_xhtml.html test_xhtml.out.html
	diff $(srcdir)/test_css.html test_css.out.html
	diff $(srcdir)/test_css_nodoc.html test_css_nodoc.out.html
	diff $(srcdir)/test_comments.java.html test_comments.java.out.html
	diff $(srcdir)/test_java_lines.html test_java_lines.out.html
	diff $(srcdir)/test.java.txt test.java.out.txt
	diff $(srcdir)/test.java.tex test.java.out.tex
	diff $(srcdir)/test.java.texinfo test.java.out.texinfo

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

check_log: test.log.html
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

check_html: test.htm.html
	$(PROGNAME) -i $(srcdir)/test.htm --title="html output formatted in html" > test.htm.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.htm.html test.htm.out.html

check_latex: test.tex.html test.java.tex.html
	$(PROGNAME) -i $(srcdir)/test.tex  > test.tex.out.html
	$(PROGNAME) -i $(srcdir)/test.java.tex  > test.java.tex.out.html
	@echo expect no output from diff
	diff $(srcdir)/test.tex.html test.tex.out.html
	diff $(srcdir)/test.java.tex.html test.java.tex.out.html

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

%.err_out: %.lang
	$(CHECKLANG) ./$< 2> $@ || true; 
	sed -r -i -f $(srcdir)/erasedir.sed $@ 

%.err_out: %.style
	$(PROGEXE) --lang-def=$(srcdir)/simple.lang --style=$(srcdir)/$< --data-dir=$(top_srcdir)/src < $(srcdir)/test.java > /dev/null 2> $@ || true;
	sed -r -i -f $(srcdir)/erasedir.sed $@ 

check_wrong: 
	rm -f *.err_out
	$(MAKE) wrong_exp.err_out
	$(MAKE) wrong_var.err_out
	$(MAKE) wrong_dircolor.err_out
	@echo expect no output from diff
	diff $(srcdir)/wrong_exp.err wrong_exp.err_out
	diff $(srcdir)/wrong_var.err wrong_var.err_out
	diff $(srcdir)/wrong_dircolor.err wrong_dircolor.err_out

#$(PROG_NOOUTLANGDEF) -i $(srcdir)/test.simple -o test.err_out --data-dir=/tmp 2> missing_langmap2.err_out || true
#sed -r -i -f $(srcdir)/erasedir2.sed missing_langmap2.err_out
#diff $(srcdir)/missing_langmap2.err missing_langmap2.err_out

check_missing: 
	rm -f *.err_out
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple -o test.err_out 2> missing_langmap.err_out || true
	$(PROG_NOLANGDEF) -i $(srcdir)/test.simple 2> missing_extension.err_out || true
	@echo expect no output from diff
	sed -r -i -f $(srcdir)/erasedir2.sed missing_langmap.err_out
	sed -r -i -f $(srcdir)/erasedir2.sed missing_extension.err_out
	diff $(srcdir)/missing_langmap.err missing_langmap.err_out
	diff $(srcdir)/missing_extension.err missing_extension.err_out

check_failsafe:
	rm -f *.unknown_out
	$(FAILSAFE) -i $(srcdir)/test.unknown -o test.unknown_out
	@echo expect no output from diff
	diff $(srcdir)/test.unknown test.unknown_out

check_debug: debug.debug
	rm -f *.out.debug
	$(DEBUGLANG) -i $(srcdir)/debug.java -o /dev/null > debug.out.debug
	@echo expect no output from diff
	diff $(srcdir)/debug.debug debug.out.debug

check_ref: $(OUTPUTWREFS)
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags -i $(srcdir)/test.h -o test_ref.out.html
	sed -i -e 's/test\_ref\.out\.html/test\_ref\.html/g' test_ref.out.html
	sed -i -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.html # eliminate leading paths
	rm -f test_refs_tmp.*
	cp -f $(srcdir)/test_refs.h test_refs_tmp.h
	cp -f $(srcdir)/test_refs.cpp test_refs_tmp.cpp
	$(CTAGS_CMD) -o test_refs_tmp.tags test_refs_tmp.h test_refs_tmp.cpp
	$(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags --line-number test_refs_tmp.h test_refs_tmp.cpp --verbose
	sed -i -e 's/\_tmp\.h/\.h/g' test_refs_tmp.h.html test_refs_tmp.cpp.html
	sed -i -e 's/\_tmp\.cpp/\.cpp/g' test_refs_tmp.h.html test_refs_tmp.cpp.html
	$(CPP2LATEX_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.out.tex
	sed -i -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.tex # eliminate leading paths
	$(CPP2LATEX_WREFSPOST) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref_post.out.tex
	sed -i -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref_post.out.tex # eliminate leading paths
	$(CPP2TEXINFO_WREFS) --ctags-file=test_ref.tags -i $(srcdir)/test.h -o test_ref.out.texinfo
	sed -i -r 's/([.\/[:alnum:]]+)\/(test\.h\:[[:alnum:]\._]+)/\2/g' test_ref.out.texinfo # eliminate leading paths
	@echo expect no output from diff
	diff $(srcdir)/test_ref.html test_ref.out.html
	diff $(srcdir)/test_refs.h.html test_refs_tmp.h.html
	diff $(srcdir)/test_refs.cpp.html test_refs_tmp.cpp.html
	diff $(srcdir)/test_ref.tex test_ref.out.tex
	diff $(srcdir)/test_ref.texinfo test_ref.out.texinfo
	diff $(srcdir)/test_ref_post.tex test_ref_post.out.tex
	rm -f test_refs_tmp.*

check_show: $(srcdir)/c_comment.show
	$(PROGEXE) --show-regex=$(top_srcdir)/src/c_comment.lang > c_comment.out.show
	@echo expect no output from diff
	diff $(srcdir)/c_comment.show c_comment.out.show

clean_ref: 
	rm -f $(OUTPUTWREFS)

source_highlightdoc_DATA = test.php3.html test.pl.html test.pm.html \
test.py.html test.rb.html test.js.html test.lua.html test.ml.html \
test.sml.html test.log.html access.log.html auth.log.html error.log.html syslog.log.html test.htm.html test.java.tex.html \
syslog.style \
log.lang.html cpp.lang.html default.style.html

VALGRINDTESTS = $(top_builddir)/tests/valgrind_tests.sh
VALGRINDTEST = $(top_builddir)/tests/valgrind_test.sh

check-valgrind:
	$(VALGRINDTEST) $(PROGEXE) --help
	$(VALGRINDTEST) $(PROGEXE) --version
	$(VALGRINDTEST) $(JAVA2HTML) -i $(srcdir)/test.java -o test.java.out.html
	$(VALGRINDTEST) $(CPP2HTML) --gen-references=inline -i $(srcdir)/test.h -o test_ref.out.html
	$(VALGRINDTEST) $(FAILSAFE) -i $(srcdir)/test.unknown -o test.unknown_out
	cp -f $(srcdir)/test_refs.h test_refs_tmp.h
	cp -f $(srcdir)/test_refs.cpp test_refs_tmp.cpp
	$(CTAGS_CMD) -o test_refs_tmp.tags test_refs_tmp.h test_refs_tmp.cpp
	$(VALGRINDTEST) $(CPP2HTML) --gen-references=inline --ctags-file=my_test_ref.tags --line-number test_refs_tmp.h test_refs_tmp.cpp
	rm -f test_refs_tmp.*

CLEANFILES = *.out.html *.out.txt *.out.tex *.err_out *.unknown_out *.out.debug *.out.texinfo *_tmp.* *.out.show

clean_html:
	rm -f *.h.html *.java.html *.cc.html *.pas.html *.pl.html *.pm.html *.php3.html *.py.html *.chlog.html *.chlog_css.html *.l.html test_xhtml.html test_css.html test_css_nodoc.html test_header.html *.rb.html *.js.html *.java.txt *.java.tex *.java.texinfo *.lua.html *.ml.html *.sml.html test_*_lines.html *.log.html *.y.html *.simple.html *.tex.html *.lgt.html *.diff.html *.lang.html *.htm.html *.style.html *.cs.html

DISTCLEANFILES=test_ref.html test_ref.tags my_test_ref.tags tags test_ref.tex test_ref_post.tex test_ref.texinfo