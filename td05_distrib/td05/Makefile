#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de processus
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# Variables
#---------------------------------------------------------------------------------

# Compilateur et options
# ----------------------
CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra -g 

ALL=$(wildcard *.c)
SRC=$(subst util.c,,${ALL})
OBJ=$(SRC:.c=.o)
EXE=$(SRC:.c=.exe)

#---------------------------------------------------------------------------------
# Cibles principales
#---------------------------------------------------------------------------------

# Exécutables
# -----------

all: $(EXE)

# Règle par défaut pour construire foo.exe à partir d'un seul fichier foo.o
# -------------------------------------------------------------------------

%.exe: %.o util.o
	$(CC) $(CFLAGS) -o $@ $^

# Règle existant par défaut pour générer un .o à partir d'un .c (donc pas la peine de la réécrire)
#%.o: %.c
#	$(CC) $(CFLAGS) -o $@ -c $<

# Nettoyages
# ----------

# Nettoyage léger
clean:
	@rm -f \#* *.o $(EXE)

# Nettoyage en profondeur
mrproper: clean
	@rm -rf *~ foo Tests

#---------------------------------------------------------------------------------
# Tests divers
#---------------------------------------------------------------------------------

test: all 
	./tst_lsrec.sh
#	./tst_mycp1.sh
#	./tst_mycp2.sh
