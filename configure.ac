# Copyright (C) 1999-2005 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

dnl Process this file with autoconf to produce a configure script.
AC_INIT(reconf)

dnl for automake
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(source-highlight,2.3)

AC_SUBST(source_highlightdatadir)
AC_SUBST(source_highlightdocdir)

source_highlightdatadir=$datadir/source-highlight
source_highlightdocdir=$datadir/doc/source-highlight

dnl Checks for C compiler.
AC_PROG_CC

dnl add options for non GNU compilers
AC_NONGNU_FLAGS

dnl Test for a gotcha in the Sun Forte Developer and, more recently the
dnl Sun ONE Studio, C++ compiler that causes an undef at link time if
dnl the code uses templates and "libx.a" archives are built using the
dnl standard `ar' technique.  `CC' creates a subdirectory set starting
dnl with one named "SunWC_cache" to build additional "*.o" files for the
dnl instantiated templates(?).  The normal way 'ar' is used doesn't work
dnl when generating archive ("libx.a") libraries and `CC' itself must be
dnl used.  The following is a hack provided by Paul Townsend <aab@purdue.edu>.
dnl
AC_MSG_CHECKING( checking whether to use ar cru or CC -xar -o )
cat <<EOF >conftest.c
int conftest(void){return 0;}
EOF
${CXX} -xar -o conftest.a conftest.c >/dev/null 2>&1
if test $? == 0; then
  ar_to_use="\$(CXX) -xar -o"
else
  ar_to_use="\$(AR) cru"
fi
AC_SUBST(ar_to_use)dnl
AC_MSG_RESULT( $ar_to_use )
rm -fr conftest.*

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([stddef.h])

dnl If on SCO UNIX, add `-lintl' to output variable `LIBS'
AC_SCO_INTL

dnl for Cygwin32 environment
dnl AM_CYGWIN32 (obsolete)
dnl AC_CYGWIN
AC_EXEEXT

dnl Checks for C++ compiler.
AC_PROG_CXX
AC_LANG_CPLUSPLUS
AC_PROG_AWK

AC_PROG_INSTALL

dnl check for ranlib, for building common code
AC_PROG_RANLIB

dnl test for --enable-warnings command line option
AC_ARG_ENABLE( warnings, [  --enable-warnings       enable compiler warnings], AC_COMPILE_WARNINGS )

dnl check for STL
AC_CXX_HAVE_STL

dnl check for sstream.h
AC_CXX_HAVE_SSTREAM

dnl check for ios_base
AC_CXX_HAVE_IOS_BASE

dnl check for Boost regular expression library
AX_BOOST_REGEX
AC_CHECK_HEADERS([boost/shared_ptr.hpp])

dnl test for ch-root feature
AC_SUBST(CHROOT_INPUT_DIR)

AC_ARG_ENABLE( input-chroot,   [  --enable-input-chroot=DIR     change the root input dir], if test $enableval = yes || test $enableval = no; then echo "configure: error: you must specify a path for --enable-input-chroot" 1>&2; exit 1; else CHROOT_INPUT_DIR=$enableval; fi, CHROOT_INPUT_DIR= )

AC_DEFINE_UNQUOTED(CHROOT_INPUT_DIR, "$CHROOT_INPUT_DIR")

dnl for txtc (Text-to-C compiler)
LF_PROG_TXTC

dnl for yacc or bison
AC_PROG_YACC

dnl for lex or flex
AM_PROG_LEX

dnl Checks for libraries.
dnl Replace `main' with a function in -lfl:
AC_CHECK_LIB(fl, main)

dnl check for Electric Fence library, but do not link it automatically
AC_HAVE_LIBRARY(libefence.a, [LIBS="$LIBS"])

dnl if (f)lex library is not present (yywrap won't be found) we provide
dnl a simple implementation (see yywrap.cc) which will be included in
dnl added objs and linked against the program (see src/Makefile.am)
dnl this works with flex generated files (I don't know about others)
AC_REPLACE_FUNCS(yywrap)

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(unistd.h)

dnl Checks for library functions.
AC_CHECK_FUNCS(strdup)

dnl check for getopt in standard library
adl_FUNC_GETOPT_LONG

dnl needed by readtags.c
AC_TYPE_OFF_T

dnl this is only for developers who change src/cmdline.ggo file
dnl GNU gengetopt can be found at http://www.gnu.org/software/gengetopt
AC_PATH_PROGS(GENGETOPT, gengetopt)
AM_CONDITIONAL(NO_GENGETOPT, test -z "$ac_cv_path_GENGETOPT" )

dnl this is only for developers who use double dispatch
dnl doublecpp can be found at http://www.lorenzobettini.it/software/doublecpp
AC_PATH_PROGS(DOUBLECPP, doublecpp)
AM_CONDITIONAL(NO_DOUBLECPP, test -z "$ac_cv_path_DOUBLECPP" )

dnl this is for testing purpose and development
AC_PATH_PROGS(VALGRIND, valgrind)

dnl this is only for developers who use change command line options
AC_PATH_PROGS(HELP2MAN, help2man)
AM_CONDITIONAL(NO_HELP2MAN, test -z "$ac_cv_path_HELP2MAN" )

dnl this is for generating references
AC_PATH_PROGS(CTAGS, ctags)
AM_CONDITIONAL(NO_CTAGS, test -z "$ac_cv_path_CTAGS" )

dnl *******************
dnl added by me
dnl *******************


dnl set some flags if it's bison
AC_SUBST(YFLAGS)dnl
YFLAGS="$YFLAGS -d"
AC_MSG_CHECKING( checking if it's bison )
if test "$ac_cv_prog_YACC" = "bison -y"; then
YFLAGS="$YFLAGS -o y.tab.c -l"
AC_MSG_RESULT( $ac_cv_prog_YACC )
else
YFLAGS="$YFLAGS -l"
AC_MSG_RESULT( no: it's $YACC )
fi

dnl CXXFLAGS="-DSOURCE_HIGHLIGHT_DATA_DIR=\\\"$source_highlightdatadir\\\" $CXXFLAGS"

AC_PATH_PROGS(TAR, tar gtar)

AC_PATH_PROGS(TEXI2HTML, texi2html)

AH_TEMPLATE(CHROOT_INPUT_DIR)
AH_BOTTOM([#include "cxxconfig.h"])

dnl compute relative paths
dnl adl_COMPUTE_STANDARD_RELATIVE_PATHS
adl_COMPUTE_RELATIVE_PATHS([bindir:datadir:bin_to_data])
source_highlight_lang_dir="$bin_to_data/source-highlight"
adl_NORMALIZE_PATH([source_highlight_lang_dir], prefix)
source_highlight_absolute_lang_dir=$source_highlightdatadir
adl_NORMALIZE_PATH([source_highlight_absolute_lang_dir], prefix)

AC_DEFINE_UNQUOTED([RELATIVEDATADIR], ["$source_highlight_lang_dir"],
                   [Define to the source-highlight
                   data directory relative to installation path.])
AC_DEFINE_DIR([ABSOLUTEDATADIR], [datadir/source-highlight],
                   [Define to the source-highlight
                   data directory absolute to installation path.])

AC_OUTPUT(
[Makefile
txtc.sh
src/Makefile
src/java2html
src/cpp2html
src/src-hilite-lesspipe.sh
doc/Makefile
src/includes/Makefile
src/lib/Makefile
tests/Makefile
tests/valgrind_tests.sh
tests/valgrind_test.sh
source-highlight.spec],
[chmod +x tests/valgrind_tests.sh
 chmod +x tests/valgrind_test.sh]
)

if test "$ax_cv_boost_regex" = "yes"; then
  if test -z "$BOOST_REGEX_LIB"; then
    AC_MSG_ERROR([

ERROR! Boost::regex library is installed, but you
must specify the suffix with --with-boost-regex at configure
for instance, --with-boost-regex=boost_regex-gcc-1_31])
  else
    echo ""
    echo "Good - your configure finished. Start make now"
    echo ""
  fi
else
  AC_MSG_ERROR([

ERROR! Boost::regex library not installed.
Please install it (download at http://www.boost.org/)])
fi

if test -z "$ac_cv_path_HELP2MAN"; then
   AC_MSG_WARN([

help2man is not installed so the man page will not
be updated in case command line options are changed.
This is important for maintainers only, though.])
fi

if test -z "$ac_cv_path_CTAGS"; then
   AC_MSG_WARN([

ctags is not installed so you won't be able to
generate references (--gen-references).])
fi