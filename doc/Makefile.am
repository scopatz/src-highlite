# Copyright (C) 1999, 2000, 2001, 2002  Lorenzo Bettini <http://www.lorenzobettini.it>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

STD_STYLE = --style-file $(top_srcdir)/src/default.style
DATADIR_OPTION = --data-dir $(top_srcdir)/src/

SRCHILITEEXE = $(top_builddir)/src/$(PACKAGE)$(EXEEXT)
SRCHILITEPROG = $(SRCHILITEEXE) $(DATADIR_OPTION)

JAVA2HTML_PROG = $(SRCHILITEPROG) -s java -f html 

PROGNAME = $(JAVA2HTML_PROG) $(STD_STYLE) 

CPP2HTML = $(SRCHILITEPROG) -s cpp -f html $(STD_STYLE)

CPP2HTML_WREFS = $(CPP2HTML) --title="Contains references to tags" --gen-references=inline --ctags="ctags --excmd=n --tag-relative=yes -o my_test_ref.tags"

CHANGELOG2HTML = $(SRCHILITEPROG) -s changelog -f html $(STD_STYLE)

FLEX2HTML = $(SRCHILITEPROG) -s flex -f html $(STD_STYLE)

OUTPUT_HERE = --output-dir=$(top_builddir)/doc

info_TEXINFOS = source-highlight.texinfo

source-highlight.texinfo: $(GENERATEDINFOS)

# help-output.texinfo: $(top_srcdir)/src/lib/cmdline.ggo
#	$(SRCHILITEEXE) --help | sed -e 's/@/@@/' > $@

if NO_GENGETOPT
help-output.texinfo: $(top_srcdir)/src/lib/cmdline.ggo
	touch $@
else
help-output.texinfo: $(top_srcdir)/src/lib/cmdline.ggo
	$(GENGETOPT) --show-help -i $(top_srcdir)/src/lib/cmdline.ggo --set-package="source-highlight" --set-version="" > $@
endif

lang-list.texinfo: $(top_srcdir)/src/lang.map
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ --lang-list | sed -e 's/@/@@/' > $@

outlang-list.texinfo: $(top_srcdir)/src/outlang.map
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ --outlang-list | sed -e 's/@/@@/' > $@

test.java.texinfo: $(top_srcdir)/tests/test.java
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test.java --style-file=$(top_srcdir)/src/texinfo.style -n > $@

test_ref.h.texinfo: $(top_srcdir)/tests/test.h
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test.h --style-file=$(top_srcdir)/src/texinfo.style -n --gen-references=postline > $@

debug.java.texinfo: $(top_srcdir)/tests/debug.java
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/debug.java --style-file=$(top_srcdir)/src/texinfo.style -n > $@

%.lang.texinfo: $(top_srcdir)/src/%.lang
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

%.outlang.texinfo: $(top_srcdir)/src/%.outlang
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

%.lang.texinfo: $(top_srcdir)/tests/%.lang
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

%.lang.texinfo: $(srcdir)/%.lang
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

%.style.texinfo: $(top_srcdir)/src/%.style
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

%.diff.texinfo: %.diff
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

%.cpp.texinfo: $(top_srcdir)/tests/%.cpp
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $< --style-file=$(top_srcdir)/src/texinfo.style -o $@

test_extreme_comment_wrong.texinfo: $(top_srcdir)/tests/test_extreme_comment.cpp
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test_extreme_comment.cpp --style-file=$(top_srcdir)/src/texinfo.style -o $@ --lang-def=extreme_comment.lang

test_extreme_comment_1.texinfo: $(top_srcdir)/tests/test_extreme_comment.cpp
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test_extreme_comment.cpp --style-file=$(top_srcdir)/src/texinfo.style -o $@ --lang-def=extreme_comment2.lang

test_extreme_comment_wrong2.texinfo: $(top_srcdir)/tests/test_extreme_comment2.cpp
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test_extreme_comment2.cpp --style-file=$(top_srcdir)/src/texinfo.style -o $@ --lang-def=extreme_comment2.lang

test_extreme_comment_2.texinfo: $(top_srcdir)/tests/test_extreme_comment2.cpp
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test_extreme_comment2.cpp --style-file=$(top_srcdir)/src/texinfo.style -o $@ --lang-def=extreme_comment3.lang

test_extreme_comment_3.texinfo: $(top_srcdir)/tests/test_extreme_comment3.cpp
	$(SRCHILITEEXE) --data-dir=$(top_srcdir)/src/ -f texinfo -i $(top_srcdir)/tests/test_extreme_comment3.cpp --style-file=$(top_srcdir)/src/texinfo.style -o $@ --lang-def=extreme_comment3.lang

%.show.texinfo: %.lang
	$(SRCHILITEEXE) --show-regex=$< > $@
	sed -i -e 's/@/@@/g' $@

AM_MAKEINFOHTMLFLAGS=--no-split

GENERATEDINFOS = help-output.texinfo lang-list.texinfo outlang-list.texinfo test.java.texinfo debug.java.texinfo default.style.texinfo texinfo.style.texinfo test_ref.h.texinfo langdef.lang.texinfo style.lang.texinfo cpp.lang.texinfo csharp.lang.texinfo c_comment.lang.texinfo c_string.lang.texinfo symbols.lang.texinfo function.lang.texinfo example-u.diff.texinfo example-c.diff.texinfo example-n.diff.texinfo diff.lang.texinfo test_extreme_comment.cpp.texinfo extreme_comment.lang.texinfo test_extreme_comment_wrong.texinfo extreme_comment2.lang.texinfo test_extreme_comment_1.texinfo test_extreme_comment_wrong2.texinfo extreme_comment3.lang.texinfo test_extreme_comment_2.texinfo test_extreme_comment_3.texinfo comment-show.show.texinfo comment-show.lang.texinfo html_common.outlang.texinfo javadoc.outlang.texinfo

EXTRA_DIST = colors.html source-highlight.html \
             Hello.java \
             Hello.css Hello2.css mono-alt.css mono.css cpp2html.css \
             xhtml.css \
             header.html footer.html \
             test_refs.h.html test_refs.cpp.html \
             test_refs.h test_refs.cpp \
             gpl.texinfo flex_scanner.ll \
             example-u.diff example-c.diff example-n.diff \
             source-highlight.1 index.html \
	     comment-show.lang \
	     SimpleClass.java SimpleClass-doc.html UsageExample.java

source_highlightdoc_DATA = colors.html source-highlight.html \
    Hello.java Hello1.html Hello2.html Hello3.html Hello4.html Hello5.html \
    Hello.java.html Hello_h_f.html Hello_lines.html Hello_xhtml.html \
    Hello_xhtml2.html \
    Hello.css Hello2.css mono-alt.css mono.css cpp2html.css xhtml.css \
    startapp.cc.html cmdline.h.html test_refs.h.html test_refs.cpp.html \
    flex_scanner.ll.html \
    header.html footer.html \
    langdef.lang.html \
    index.html \
    SimpleClass.java SimpleClass.html SimpleClass-doc.html \
    UsageExample.java UsageExample.html

# man page
man_MANS = source-highlight.1

# the dependence on config.h is to ensure the correct version number
# in the generated man file
if NO_HELP2MAN
source-highlight.1: $(top_srcdir)/src/lib/cmdline.ggo $(top_builddir)/config.h
	touch $@
else
source-highlight.1: $(top_srcdir)/src/lib/cmdline.ggo $(top_builddir)/config.h
	$(HELP2MAN) $(SRCHILITEEXE) > $@
endif

# note that $(srcdir) actually points to doc dir

langdef.lang.html: $(top_srcdir)/src/langdef.lang
	$(SRCHILITEPROG) $(STD_STYLE) -i $(top_srcdir)/src/langdef.lang -o langdef.lang.html

startapp.cc.html: $(top_srcdir)/src/startapp.cc
	$(CPP2HTML) --doc $(OUTPUT_HERE) $(top_srcdir)/src/startapp.cc

#ChangeLog.html: $(top_srcdir)/ChangeLog
#	$(CHANGELOG2HTML) --doc $(OUTPUT_HERE) $(top_srcdir)/ChangeLog

flex_scanner.ll.html: $(srcdir)/flex_scanner.ll
	$(FLEX2HTML) --doc $(OUTPUT_HERE) $(srcdir)/flex_scanner.ll

# cmdline.c.html: $(top_srcdir)/src/lib/cmdline.c
#	$(CPP2HTML) --doc $(OUTPUT_HERE) --css="$(srcdir)/cpp2html.css" --header="$(srcdir)/header.html" --footer="$(srcdir)/footer.html" $(top_srcdir)/src/lib/cmdline.c

cmdline.h.html: $(top_srcdir)/src/lib/cmdline.h
	$(CPP2HTML) --doc $(OUTPUT_HERE) --css="$(srcdir)/mono.css" $(top_srcdir)/src/lib/cmdline.h

BUILD_HELLO1 = $(PROGNAME) -i $(srcdir)/Hello.java -o Hello1.html
BUILD_HELLO2 = $(PROGNAME) --input $(srcdir)/Hello.java --output Hello2.html --doc
BUILD_HELLO3 = $(PROGNAME) -i $(srcdir)/Hello.java -o Hello3.html --title "Happy Java with java2html :-)" --tab 3
BUILD_HELLO4 = $(PROGNAME) < $(srcdir)/Hello.java > Hello4.html --title "and what about CSS :-)" --css "Hello.css"
BUILD_HELLO5 = $(PROGNAME) < $(srcdir)/Hello.java > Hello5.html --title "Wooo... this is quite dark ;-D" --css "mono-alt.css"
BUILD_HELLO_HTML = $(PROGNAME) --doc $(OUTPUT_HERE) $(srcdir)/Hello.java
BUILD_HELLO_W_HEADER_FOOTER = $(JAVA2HTML_PROG) --css="cpp2html.css" --doc -i $(srcdir)/Hello.java -o Hello_h_f.html --header="$(srcdir)/header.html" --footer="$(srcdir)/footer.html"
BUILD_HELLO_LINES = $(PROGNAME) --line-number --doc -i $(srcdir)/Hello.java -o Hello_lines.html
BUILD_HELLO_XHTML = $(SRCHILITEPROG) -s java -f xhtml --doc -i $(srcdir)/Hello.java -o Hello_xhtml.html --css $(srcdir)/xhtml.css
BUILD_HELLO_XHTML2 = $(SRCHILITEPROG) -s java -f xhtml --doc -i $(srcdir)/Hello.java -o Hello_xhtml2.html $(STD_STYLE)
BUILD_REFS = $(CPP2HTML_WREFS) --ctags-file=my_test_ref.tags --line-number $(srcdir)/test_refs.h $(srcdir)/test_refs.cpp && sed -r 's/\"([^[:blank:]]*)\/([[:alnum:]\._]*\#[[:alnum:]\._]+)\"/\"\2\"/g' -i test_refs.h.html test_refs.cpp.html # eliminate leading paths

SimpleClass.html: $(srcdir)/SimpleClass.java
	$(PROGNAME) --input $(srcdir)/SimpleClass.java --output SimpleClass.html --doc

UsageExample.html: $(srcdir)/UsageExample.java
	$(PROGNAME) --input $(srcdir)/UsageExample.java --output UsageExample.html --doc

test_refs.h.html: test_refs.h
	$(BUILD_REFS)

test_refs.cpp.html: test_refs.h.html

Hello1.html: $(srcdir)/Hello.java
	$(BUILD_HELLO1)

Hello2.html: $(srcdir)/Hello.java
	$(BUILD_HELLO2)

Hello3.html: $(srcdir)/Hello.java
	$(BUILD_HELLO3)

Hello4.html: $(srcdir)/Hello.java
	$(BUILD_HELLO4)

Hello5.html: $(srcdir)/Hello.java
	$(BUILD_HELLO5)

Hello.java.html: $(srcdir)/Hello.java
	$(BUILD_HELLO_HTML)

Hello_h_f.html: $(srcdir)/Hello.java header.html footer.html
	$(BUILD_HELLO_W_HEADER_FOOTER)

Hello_lines.html: $(srcdir)/Hello.java
	$(BUILD_HELLO_LINES)

Hello_xhtml.html: $(srcdir)/Hello.java
	$(BUILD_HELLO_XHTML)

Hello_xhtml2.html: $(srcdir)/Hello.java
	$(BUILD_HELLO_XHTML2)
check:
	$(BUILD_HELLO1)
	$(BUILD_HELLO2)
	$(BUILD_HELLO3)
	$(BUILD_HELLO4)
	$(BUILD_HELLO5)
	$(BUILD_HELLO_HTML)
	$(BUILD_HELLO_W_HEADER_FOOTER)
	$(BUILD_HELLO_LINES)
	$(BUILD_HELLO_XHTML)
	$(BUILD_HELLO_XHTML2)

HTML_GENERATED_FILES = Hello1.html Hello2.html Hello3.html Hello4.html \
Hello5.html Hello.java.html Hello_h_f.html startapp.cc.html \
cmdline.h.html Hello_lines.html Hello_xhtml.html Hello_xhtml2.html \
flex_scanner.ll.html test_refs.h.html test_refs.cpp.html SimpleClass.html \
UsageExample.html

html-clean:
	rm -f $(HTML_GENERATED_FILES)

texinfo-clean:
	rm -f $(GENERATEDINFOS)

DISTCLEANFILES = $(HTML_GENERATED_FILES) source-highlight.1 $(GENERATEDINFOS) tags langdef.lang.html