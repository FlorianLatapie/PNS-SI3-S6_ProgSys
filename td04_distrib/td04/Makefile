#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de processus
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# Variables
#---------------------------------------------------------------------------------

# Compilateur et options
# ----------------------
CC=gcc
CFLAGS=-std=gnu99 -Wall -g 

ALL=$(wildcard *.c)
SRC=$(subst timer.c,,${ALL})
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

multiple_%.exe: timer.o multiple_%.o
	$(CC) -o $@ $^ -lpthread

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $<  -lpthread

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
	@rm -f secret_file.txt

#---------------------------------------------------------------------------------
# Installations diverses
#---------------------------------------------------------------------------------

install: all 
	@echo "*** Rien à installer ***"
