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

# Pour tester la compilation avec la norme Ansi C des signaux
# CFLAGS=-Wall -Wextra -ansi -g

SRC=$(wildcard *.c)
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

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<

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
	@rm -rf *~ $(FIFO)

test: