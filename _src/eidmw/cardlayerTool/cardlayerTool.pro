######################################################################
# Automatically generated by qmake (2.01a) Thu Dec 13 13:30:34 2007
######################################################################


include(../_Builds/eidcommon.mak)
	
TEMPLATE = app
TARGET = $${CARDLAYERTOOL}
VERSION = $${CARDLAYERTOOL_MAJ}.$${CARDLAYERTOOL_MIN}.$${CARDLAYERTOOL_REV}


message("Compile $$TARGET")

###
### Installation setup
###
target.path = $${INSTALL_DIR_BIN}
INSTALLS += target


###
### Compiler setup
###

CONFIG += debug
CONFIG -= warn_on qt

## destination directory for the compiler
DESTDIR = ../bin

DEPENDPATH += .  

LIBS = -L../lib -l$${COMMONLIB} -lpthread -lfreeimagePTEiD

## link to openssl
macx: LIBS += -L/Developer/SDKs/MacOSX10.4u.sdk/usr/lib 
LIBS += -lcrypto
	
macx: USE_PRIVACYFB =

isEmpty(EMULATE_CARDLAYER) {

  LIBS +=	-l$${CARDLAYERLIB} 

  unix:!macx: LIBS += -lpcsclite
  macx: LIBS += -Wl,-framework -Wl,PCSC 	

} else {
  LIBS += -l$${CARDLAYEREMULIB} 
}
 
LIBS +=	-l$${DLGLIB}
unix:!macx:LIBS += -Wl,-R,"'\$\$ORIGIN/$${LINK_RELATIVE_PATH}'"

INCLUDEPATH += .  $${PCSC_INCLUDE_DIR} ../common

# Input
HEADERS += 

SOURCES += cardlayertool.cpp \
           dumpcontents.cpp \
           testcardlayer.cpp
