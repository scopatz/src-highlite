# Copyright (C) 1999, 2000, 2001 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SUBDIRS = m4 gl lib src doc tests

EXTRA_DIST = \
	source-highlight.spec.in \
	source-highlight.spec \
	TODO.txt \
	CREDITS gl/m4/gnulib-cache.m4 \
	completion/source-highlight \
        _sstream \
        source-highlight.pro defines.pri

source_highlightdoc_DATA = \
	ChangeLog \
	COPYING \
	NEWS \
	THANKS \
	INSTALL \
	README \
	TODO.txt \
	CREDITS

if USE_BASH_COMPLETION
bash_completion_DATA = completion/source-highlight
else
bash_completion_DATA = 
endif

ACLOCAL_AMFLAGS = -I m4 -I gl/m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = source-highlight.pc

DISTCHECK_CONFIGURE_FLAGS=--with-doxygen
