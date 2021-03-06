######################################################################
# Automatically generated by qmake (2.01a) Fri Dec 21 12:05:07 2007
######################################################################


include(../_Builds/eidcommon.mak)

TEMPLATE = lib
#TARGET = $${JAVALIB}
VERSION = $${JAVALIB_MAJ}.$${JAVALIB_MIN}.$${JAVALIB_REV}

message("Compile $$TARGET")

###
### Installation setup
###
target.path = $${INSTALL_DIR_LIB}
INSTALLS += target

CONFIG -= warn_on qt

## destination directory
DESTDIR = ../lib

LIBS += -L../lib  \
		-l$${COMMONLIB} \
		-l$${DLGLIB} \
		-l$${CARDLAYERLIB} \
		-l$${APPLAYERLIB} \
		-l$${EIDLIB}

macx: INCLUDEPATH += /System/Library/Frameworks/JavaVM.framework/Headers/
macx: LIB += -Wl,-framework -Wl,Java

DEPENDPATH += .
INCLUDEPATH += . ../applayer ../common ../cardlayer ../eidlib
INCLUDEPATH += $${PCSC_INCLUDE_DIR}

# Input

SOURCES += GeneratedFiles/eidlibJava_Wrapper.cpp
