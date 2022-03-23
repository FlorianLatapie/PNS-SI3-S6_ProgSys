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

#---------------------------------------------------------------------------------
# Tests divers
#---------------------------------------------------------------------------------
FIFO=my_named_pipe

# Attention, la création du fichier spécial ne fonctionnera pas sur un dossier partagé si le système de fichiers
#   sous-jacent ne supporte les fichiers spéciaux de type Posix FIFO
# Dans ce cas, faire la création dans /tmp par exemple.
fifo:
	@if [ ! -p "$(FIFO)" ] ; then mkfifo $(FIFO) ; ls -l $(FIFO) ; fi

test: all
	./tst_redir.sh
#	./tube_anonyme1.exe
#	./tube_anonyme2.exe
#	./tube_anonyme_multi.exe
#	./popen.exe
#	./tst_pipes.exe
#	./erastosthene.exe 100

ecrit: ecrivain.exe fifo
	./ecrivain.exe $(FIFO)

lit: lecteur.exe fifo
	./lecteur.exe $(FIFO)


