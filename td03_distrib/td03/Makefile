#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de processus
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# Variables
#---------------------------------------------------------------------------------

# Compilateur et options
# ----------------------
CC=gcc
CFLAGS=-std=c99 -Wall -g 

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXE=$(SRC:.c=.exe)

EXTRA=setuid_extra

#---------------------------------------------------------------------------------
# Cibles principales
#---------------------------------------------------------------------------------

# Exécutables
# -----------

all: $(EXE) $(EXTRA)

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
	@rm -f secret_file.txt

setuid_extra: fcat.exe secret_file
	@chmod u+s fcat.exe

secret_file:
	@touch secret_file.txt
	@echo "Ceci est le contenu\ndu fichier secret\n" > secret_file.txt
	@chmod u+rw,og-rwx secret_file.txt

#---------------------------------------------------------------------------------
# Installations diverses
#---------------------------------------------------------------------------------

install: all 
	@echo "*** Rien à installer ***"
