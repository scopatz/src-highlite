# Copyright (C) 1999-2009 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AM_CPPFLAGS = \
	-I$(top_srcdir)/gl \
	-I$(top_builddir)/gl \
	-I$(top_srcdir)/src \
	-I$(srcdir)/.. \
	$(BOOST_CPPFLAGS) \
	-D DATADIR="\"$(top_srcdir)/src/\""
AM_LDFLAGS = $(BOOST_LDFLAGS) -no-install

LDADD = $(top_builddir)/gl/libgnu.la $(LIBDIR)/libsource-highlight.la

#LIBDIR = $(top_builddir)/lib/srchilite/
LIBDIR = ../srchilite/

check_PROGRAMS = source-highlight-console infoformatter styleformatter

source_highlight_console_SOURCES = source-highlight-console-main.cpp
infoformatter_SOURCES = infoformatter-main.cpp infoformatter.h
styleformatter_SOURCES = styleformatter-main.cpp styleformatter.h styleformatterfactory.h

source_highlightlibexample_DATA = $(source_highlight_console_SOURCES) \
	$(infoformatter_SOURCES) $(styleformatter_SOURCES)
