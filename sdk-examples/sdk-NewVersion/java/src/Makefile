all: utils oficial auto-generate-new-version new 


utils:
	javac Utils.java

oficial:
	javac -cp .:./pteidlibj.jar OfficialSDK.java

run-oficial:
	java -Djava.library.path=/usr/local/lib/pteid_jni:/usr/local/lib/ -cp .:./pteidlibj.jar OfficialSDK

auto-generate-new-version:
	./createJavaFile_new-versionSDK.java.sh

new:
	javac -cp .:./pteidlibj.jar:./pteid35libJava.jar NewVersionSDK.java

run-new:
	java -Djava.library.path=/usr/local/lib/pteid_jni:/usr/local/lib/ -cp .:./pteidlibj.jar:./pteid35libJava.jar NewVersionSDK
