######################################################################
# Automatically generated by qmake (2.01a) Thu Dec 13 13:25:01 2007
######################################################################


include(../_Builds/eidcommon.mak)

TEMPLATE = lib
TARGET = $${PKCS11LIB}
VERSION = $${PKCS11LIB_MAJ}.$${PKCS11LIB_MIN}.$${PKCS11LIB_REV}

message("Compile $$TARGET")

###
### Installation setup
###
target.path = $${INSTALL_DIR_LIB}
INSTALLS += target

CONFIG -= warn_on qt

## destination directory
DESTDIR = ../lib
DEPENDPATH += . 
LIBS += -L../lib -l$${COMMONLIB} -l$${CARDLAYERLIB} -l$${DLGLIB}
macx: LIBS += -Wl,-framework -Wl,PCSC

##macx: USE_PRIVACYFB =

isEmpty(EMULATE_CARDLAYER) {

  LIBS +=	-l$${CARDLAYERLIB} 

##  isEmpty(USE_PRIVACYFB){
##    unix:!macx: LIBS += -lpcsclite
##    macx: LIBS += -Wl,-framework -Wl,PCSC 	
##  } else {
##    unix:!macx: LIBS += -l$${PRIVACYFB} 
##    ## declare this library explicitly as prerequisite for the target
##    ## otherwise the update of the target is not performed when 
##    ## lib$${PRIVACYFB}.a is newer.
##    unix:!macx: PRE_TARGETDEPS += ../lib/lib$${PRIVACYFB}.a	
##  }

} else {
  LIBS += -l$${CARDLAYEREMULIB} 
}

INCLUDEPATH += . ../common ../cardlayer
INCLUDEPATH += $${PCSC_INCLUDE_DIR}

QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -fno-strict-aliasing
QMAKE_CFLAGS += -fno-strict-aliasing

DEFINES += 
unix:!macx:  DEFINES += __UNIX__
#macx:  DEFINES += __OLD_PCSC_API__

# Input
HEADERS += asn1.h \
	cal.h \
	cert.h \
	log.h \
	p11.h \
	phash.h \
	util.h \
	pteid_p11.h \
	include/rsaref220/unix.h \
	include/rsaref220/pkcs11.h \
	include/rsaref220/pkcs11t.h \
	include/rsaref220/pkcs11f.h

SOURCES += asn1.c \
	cert.c \
	encrypt.c \
	general.c \
	log.c \
	object.c \
	p11.c \
	session.c \
	sign.c \
	util.cpp \
	cal.cpp \
	phash.cpp
