######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 2 11:59:42 2008
######################################################################


include(../_Builds/eidcommon.mak)

TEMPLATE = app
TARGET = $${COMMONTEST}
VERSION = $${COMMONTEST_MAJ}.$${COMMONTEST_MIN}.$${COMMONTEST_REV}

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

DEFINES += EIDMW_CMN_EXPORT 
## About !macx see _Builds/pteidcommon.mak.max
unix:!macx: DEFINES += USING_DL_OPEN

## destination directory for the compiler
DESTDIR = ../bin

DEPENDPATH += .
INCLUDEPATH += .  $${PCSC_INCLUDE_DIR}

BUILD_TESTS=yes ## needed by ../_Builds/eidtests.mak
include(../_Builds/eidtests.mak)

LIBS += -lpthread -ldl -L../lib -l$${COMMONLIB}

QMAKE_CFLAGS_DEBUG += -O

SOURCES += \
          ByteArrayTest.cpp \
          commontest.cpp \
          ConfigTest.cpp \
          DataFileTest.cpp \
          HashTest.cpp \
          LogBaseTest.cpp \
          LogTest.cpp \
          MutexTest.cpp \
          SocketTest.cpp \
          ThreadTest.cpp \
           TLVTest.cpp \
          UtilTest.cpp \

unix:!macx: SOURCES += DynamicLibTest.cpp \