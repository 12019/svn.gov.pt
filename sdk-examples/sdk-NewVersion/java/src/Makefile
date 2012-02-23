all: build run 

build:
	javac Utils.java
	javac -cp .:./pteid35libJava.jar ExampleSDK.java
#For Windows:  javac -cp .:./pteid35libJava.jar ExampleSDK.java
	
run:
	java -Djava.library.path=/usr/local/lib/pteid_jni:/usr/local/lib/ -cp .:./pteid35libJava.jar ExampleSDK
# For windows:	java -Djava.library.path=.;/C:\WINDOWS\system32 -cp .;./pteid35libJava.jar ExampleSDK
