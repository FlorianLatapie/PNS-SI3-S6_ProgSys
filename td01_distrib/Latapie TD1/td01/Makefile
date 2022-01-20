CC=gcc
CFLAGS=-Wall -std=gnu99 -g
SRC=$(wildcard *.c)
EXE=$(SRC:.c=)

all: $(EXE)
clean:
	rm -f $(EXE) *~
test: all
	./debugSimple
