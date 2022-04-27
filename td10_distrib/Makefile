#
# Makefile du Td10 de ProgSys SI4
#

LIBDIR=./lib
JC=javac
JFLAGS=-g

# ----------------------------------------------------------------------
# Code Java
SRC=$(sort $(wildcard *.java))
OBJ=$(SRC:.java=.class)
INC=$(filter-out $(LIBDIR)/exo1.h, \
                 $(addprefix $(LIBDIR)/, $(SRC:.java=.h)))

# ----------------------------------------------------------------------
# Code C/C++
JAVA_H=/usr/lib/jvm/java-17-openjdk-amd64/
CPP=g++
CXXFLAGS= -Wall  -I$(JAVA_H)/include/ \
          -I$(JAVA_H)/include/linux \
          -L$(JAVA_H)/lib/server

CPP_SRC=$(sort $(wildcard *.cpp))
EXE=$(CPP_SRC:.cpp=.exe)

# ----------------------------------------------------------------------
# Règles implicites
%.class: %.java
	$(JC) $(JFLAGS) $<

%.exe: %.cpp
	$(CPP) $(CXXFLAGS) -o $@ $^ -ljvm


$(LIBDIR)/%.h: %.java
	$(JC) -h $(LIBDIR) $<

# ----------------------------------------------------------------------
all: $(OBJ) $(INC) $(EXE)
	$(MAKE) -C $(LIBDIR) all

clean:
	rm -f \#* *~ $(OBJ) $(INC) $(EXE)
	$(MAKE) -C $(LIBDIR) clean
