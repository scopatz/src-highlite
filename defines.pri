MAJOR_VERSION = 3
VERSION = $${MAJOR_VERSION}.1.7

# better to avoid both builds (especially on windows)
CONFIG-=debug_and_release

CONFIG -= qt
CONFIG += console warn_on
CONFIG -= thread

# -------------------------------------------------
# Auto select compiler
# -------------------------------------------------
win32-g++:      COMPILER = mingw
win32-msvc*:    COMPILER = msvc
linux-g++:      COMPILER = gcc

DEFINES += ABSOLUTEDATADIR=\\\"/usr/local/share/source-highlight/\\\" \
    VERSION=\\\"3.1.7\\\" \
    LIBRARY_VERSION=\\\"4.0.0\\\" \
    PACKAGE=\\\"source-highlight\\\" \
    RELATIVEDATADIR=\\\"../share/source-highlight\\\"

LIBRARY_NAME = source-highlight
LIBRARY_LIB = $${LIBRARY_NAME}

CONFIG(static) {
    BUILDING_STATIC_LIBRARY=1
}

contains(COMPILER, mingw) {
    isEmpty(BUILDING_STATIC_LIBRARY) {
        LIBRARY_LIB=$${LIBRARY_NAME}$${MAJOR_VERSION}
    }
}

contains(COMPILER, msvc) {
    isEmpty(BUILDING_STATIC_LIBRARY) {
        CONFIG+=static
    }
}

!isEmpty(BOOST_REGEX) {
# remove the library found with pkg-config with the one explicitly specified
ADDITIONAL_LIBRARIES += -l$$BOOST_REGEX
} else {
    ADDITIONAL_LIBRARIES += -lboost_regex
}

contains(COMPILER, msvc) {
    # Special cases for MSVC
    DEFINES += USE_MSVC
    DEFINES +=  _CRT_SECURE_NO_WARNINGS
}

contains(COMPILER, mingw) {
    # Special cases for mingw
    DEFINES += USE_MINGW
}
