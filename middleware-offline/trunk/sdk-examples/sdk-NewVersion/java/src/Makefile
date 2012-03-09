all: build createFilesToSign run 

createFilesToSign:
	echo "File Teste 1 " > teste.txt
	echo "File Teste 2 " > teste2.txt

build:
	javac Utils.java
	javac -cp .:../pteid-pkg/jar/pteidlibJava.jar ExampleSDK.java
	#javac -cp .:./pteidlibJava.jar ExampleSDK.java
	


#For Windows:  javac -cp .:./pteid35libJava.jar ExampleSDK.java
	
run:
	java -Djava.library.path=../pteid-pkg/lib/ -cp .:../pteid-pkg/jar/pteidlibJava.jar ExampleSDK
	#java -Djava.library.path=/usr/local/lib/pteid_jni:/usr/local/lib/ -cp .:./pteidlibJava.jar ExampleSDK
# For windows:	java -Djava.library.path=.;/C:\WINDOWS\system32 -cp .;./pteid35libJava.jar ExampleSDK
