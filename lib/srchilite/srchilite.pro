include(../../defines.pri)

TEMPLATE = lib

# save information about the library:
CONFIG += create_prl

TARGET = $$LIBRARY_NAME

LIBS += $$ADDITIONAL_LIBRARIES

HEADERS = parsestyles.h \
	stringdef.h langelem.h \
	statelangelem.h langelems.h langdefparserfun.h outlangdefparserfun.h \
	tostringcollection.h regexpreprocessor.h \
	langdefscanner.h outlangdefscanner.h parsestruct.h langmap.h statestartlangelem.h \
	stringlistlangelem.h delimitedlangelem.h vardefinitions.h textstyle.h \
	textstyles.h textstylebuilder.h doctemplate.h substfun.h \
	parserinfo.h readtags.h fileinfo.h linebuffer.h preformatter.h \
	langelemsprinter.h languageinfer.h stopwatch.h stylekey.h \
	namedsubexpslangelem.h refposition.h \
	highlightrule.h highlighttoken.h highlightrulefactory.h highlightstate.h \
	regexhighlightrule.h regexrulefactory.h \
	highlightstateprinter.h sourcehighlighter.h matchingparameters.h \
	formatter.h formattermanager.h \
	highlightstatebuilder.h highlightbuilderexception.h \
	wordtokenizer.h ctagscollector.h formatterparams.h ctagsformatter.h \
	sourcefilehighlighter.h linenumgenerator.h \
	textstyleformatter.h formatterfactory.h textstyleformatterfactory.h \
	langdefmanager.h sourcehighlight.h \
	textstyleformattercollection.h \
	ioexception.h parserexception.h stringtable.h \
	eventgenerator.h highlightevent.h highlighteventlistener.h \
	debuglistener.h ctagsmanager.h bufferedoutput.h lineranges.h regexranges.h \
	colors.h \
             keys.h styleparser.h stylecssparser.h \
             fileutil.h \
             chartranslator.h \
             docgenerator.h \
             srcuntabifier.h colormap.h \
             langdefparser.h outlangdefparser.h \
             stylefileparser.h \
             settings.h \
             versions.h \
             verbosity.h \
             sourcehighlightutils.h utils.h \
             instances.h

SOURCES += \
	fileutil.cc \
	substfun.cpp \
	stopwatch.cpp utils.cpp \
	ioexception.cpp \
	settings.cpp \
	versions.cpp \
	verbosity.cpp \
        sourcehighlight.cpp styleparser.cc \
        stylescanner.cc outlangdefparser.cc \
        stylecssparser.cc stylecssscanner.cc outlangdefscanner.cc \
	debuglistener.cpp langmap.cpp stylefileparser.cpp \
	langelem.cpp statelangelem.cpp \
	langelems.cpp statestartlangelem.cpp stringlistlangelem.cpp \
	delimitedlangelem.cpp langelemsprinter.cpp \
	namedsubexpslangelem.cpp stringdef.cpp \
	highlightrule.cpp highlighttoken.cpp \
	highlightstate.cpp highlightrulefactory.cpp highlightstateprinter.cpp \
	sourcehighlighter.cpp sourcefilehighlighter.cpp \
	linenumgenerator.cpp lineranges.cpp regexranges.cpp \
	formatter.cpp formattermanager.cpp \
	textstyle.cpp textstyleformatter.cpp bufferedoutput.cpp \
	preformatter.cpp wordtokenizer.cpp ctagscollector.cpp readtags.c ctagsformatter.cpp \
	srcuntabifier.cpp textstyleformatterfactory.cpp \
	docgenerator.cc doctemplate.cpp chartranslator.cc \
	textstylebuilder.cpp fileinfo.cpp ctagsmanager.cpp \
	regexhighlightrule.cpp regexrulefactory.cpp \
	regexpreprocessor.cpp \
	highlightstatebuilder.cpp \
	highlightbuilderexception.cpp langdefmanager.cpp \
        $$PWD/langdefparser.cc $$PWD/langdefscanner.cc \
	languageinfer.cpp \
	parserexception.cpp \
	stringtable.cpp vardefinitions.cpp \
	sourcehighlightutils.cpp \
	instances.cpp \
        langelemsprinter_dbtab.cc \
        highlightstatebuilder_dbtab.cc

contains(COMPILER, msvc) {
# custom implementation of dirent.h functions
SOURCES += ../compat/compat_dirent.cpp
INCLUDEPATH += ../compat
DEPENDPATH += ../compat
}

DESTDIR = ../../lib

target.path = /lib

headers.files = $$HEADERS
headers.path = /include/srchilite

INSTALLS += target headers

