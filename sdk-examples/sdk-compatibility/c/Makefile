SOURCES_NEW := testNewversionCSDK.c ccerrors.c
CFLAGS_NEW := -O2 -I/usr/local/include -w
LDFLAGS_NEW = -lpteidlib -lpteidapplayer -lrt -L/usr/local/lib
TARGET_NEW = testNewversionCSDK

SOURCES_OFICIAL := testOficialCSDK.c ccerrors.c
CFLAGS_OFICIAL := -O2 -I/usr/local/include -w
LDFLAGS_OFICIAL = -lpteid -lrt -L/usr/local/lib
TARGET_OFICIAL = testOficialCSDK




all: new oficial

new: 
	g++ -c $(CFLAGS_NEW) $(SOURCES_NEW)
	g++ -o $(TARGET_NEW) $(LDFLAGS_NEW) testNewversionCSDK.o ccerrors.o
oficial:
	g++ -c $(CFLAGS_OFICIAL)   $(SOURCES_OFICIAL)
	g++ -o $(TARGET_OFICIAL) $(LDFLAGS_OFICIAL) testOficialCSDK.o ccerrors.o

clean:
	rm -fv *.o $(TARGET_NEW) $(TARGET_OFICIAL) commonTests.h.gch
