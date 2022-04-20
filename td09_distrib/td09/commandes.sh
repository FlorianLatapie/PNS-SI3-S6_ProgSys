g++ -c -fpic -Wall HelloWorld.cpp -I /usr/lib/jvm/java-17-openjdk-amd64/include -I /usr/lib/jvm/java-17-openjdk-amd64/include/linux

g++ -Wl,-soname,libHelloWorld.so -shared -o libHelloWorld.so HelloWorld.o

javac -h . HelloWorld.java

java HelloWorld