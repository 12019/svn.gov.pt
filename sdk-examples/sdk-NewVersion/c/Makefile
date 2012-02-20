SOURCES := ExampleSDK.c 
CFLAGS := -O2 -I/usr/local/include -w
LDFLAGS = -lpteidlib -lpteidapplayer -lrt -L/usr/local/lib
TARGET = ExampleSDK

all: clean build 

build: 
	g++ -c $(CFLAGS) $(SOURCES)
	g++ -o $(TARGET) $(LDFLAGS) ExampleSDK.o

clean:
	rm -fv *.o $(TARGET)
