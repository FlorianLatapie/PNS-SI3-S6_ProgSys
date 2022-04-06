#
#  Makefile 	-- Makefile pour le TD système sur malloc
#
# Copyright © 2020 Erick Gallesio - Polytech Nice-Sophia <eg@unice.fr>
#
#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date:  8-Apr-2020 16:59
# Last file update: 16-Apr-2020 14:02 (lavirott)
#

CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 -g -Wno-unused-variable

# Les sources C (i.e. tous les fichiers C sauf mymalloc.c)
SRC=$(sort $(filter-out mymalloc.c,$(wildcard *.c)))

# Les fichiers à produire
EXE=$(SRC:.c=.exe)
HTML=$(EXE:.exe=.html)

# Règles implicites surles exécutables
%.exe: %.c mymalloc.o
	$(CC) $(CFLAGS) -o $@ $*.c mymalloc.o

# Règles implicites sur les fichier HTML produits
%.html: %.exe
	@chmod a+x ./villoc/to-html
	@chmod a+x ./villoc/villoc.py
	./villoc/to-html $?

# ======================================================================
all:  $(EXE) $(HTML)

clean:
	rm -f $(LIB) $(EXE) $(HTML) *.o *~

install:

distclean: clean
