include(../defines.pri)

TEMPLATE = app

# enable reading of this meta information in the applications that use the static library:
CONFIG += link_prl

TARGET = source-highlight-settings

SOURCES = source-highlight-settings.cpp

INCLUDEPATH += . ../../lib ../lib $$INCPATH
DEPENDPATH += ../lib ../../lib .

LIBS += -L../lib -l$$LIBRARY_LIB $$ADDITIONAL_LIBRARIES

DESTDIR = ../bin

target.path = /bin

INSTALLS += target
