include(defines.pri)

TEMPLATE = subdirs

CONFIG += ordered recursive

SUBDIRS = lib src

OTHER_FILES = TODO.txt \
    COPYING \
    AUTHORS \
    INSTALL \
    README \
    THANKS

message(Compiler       : $${COMPILER})
message(Compiler Binary: $$QMAKE_CXX)

isEmpty(BUILDING_STATIC_LIBRARY) {
    message("dynamic library")
} else {
    message("static library")
}

message( "Libraries: " )
message( "specified by user  : " $$ADDITIONAL_LIBRARIES )

contains(COMPILER, msvc) {
    isEmpty(BUILDING_STATIC_LIBRARY) {
        warning("on msvc only static version of the library can be currently built")
    }
}
