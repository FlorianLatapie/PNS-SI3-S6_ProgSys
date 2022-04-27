#
#  Makefile 	-- Makefile du répertoire lib du Td10
#

JAVA_H=/usr/lib/jvm/java-17-openjdk-amd64/
CC=g++
CXXFLAGS=-fpic -Wall  -I$(JAVA_H)/include/ -I$(JAVA_H)/include/linux

SRC=$(sort $(wildcard *.cpp))
LIBS=$(addprefix lib, $(SRC:.cpp=.so))

lib%.so: %.o
	$(CC) -Wl,-soname,$@ -shared -o $@ $<

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

# ----------------------------------------------------------------------
all: $(LIBS)

clean:
	rm -f *~ $(LIBS)

install:

distclean: clean
