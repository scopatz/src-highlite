include(../defines.pri)
TEMPLATE = app

# enable reading of this meta information in the applications that use the static library:
CONFIG += link_prl

TARGET = source-highlight
SOURCES = cmdline.c \
    source-highlight.cc

INCLUDEPATH += . \
    ../../lib \
    ../lib \
    $$INCPATH
DEPENDPATH += ../lib \
    ../../lib \
    .
LIBS += -L../lib \
    -l$$LIBRARY_LIB $$ADDITIONAL_LIBRARIES
DESTDIR = ../bin

contains(COMPILER, msvc) {
# custom implementation of getopt functions
SOURCES += ../lib/compat/getopt.c ../lib/compat/getopt1.c
INCLUDEPATH += ../lib/compat
DEPENDPATH += ../lib/compat
}

target.path = /bin

sourcehighlightdata.files = *.lang \
    *.outlang \
    *.style \
    *.css \
    *.map \
    *.defaults
sourcehighlightdata.path = /share/source-highlight
INSTALLS += target \
    sourcehighlightdata
