#---------------------------------------------------------------------------------
# Génération des exécutables et bibliothèques
#---------------------------------------------------------------------------------

# Définition des éléments d'une règle: 
#  Une règle se définie de la manière suivante:
#   cible: dépendances
#   <TAB>commandes
#
# 	%' sert de "joker" dans la cible et les dépendances (mais pas dans les commandes)
#   Dans les commandes on peut utiliser les variables suivantes:
#		$@ est le nom de la cible (partie gauche de la règle)
#		$^ est la liste des dépendances (partie droite de la règle)

## Version de base des programmes compilés
BASIC_EXE=$(EXE:.exe=-basicExe.exe)

tri_%-basicExe.exe: main.o %.o timer.o utils.o unused.o
	$(CC) -o $@ $^

####
# Exercice 3:
STATIC_EXE=$(EXE:.exe=-staticExe.exe)

tri_%-staticExe.exe: main.o %.o timer.o utils.o unused.o
#	TODO: écrire la règle permettant de créer un exécutable n'utilisant aucune bibliothèque
	$(CC) -static -o $@ $^

####
# Exercice 4:
STATIC_LIB=$(EXE:.exe=-staticLib.exe)

tri_%-staticLib.exe: main.o timer.o utils.o libTri_%-staticLib.a
	$(CC) -o $@ $^

libTri_%-staticLib.a: %.o unused.o
#	TODO: écrire la règle permettant de créer une bibilothèque avec lien statique
	ar -r $@ $^
	ranlib $@

####
# Exercice 5:
DYNAMIC_LIB=$(EXE:.exe=-dynamicLib.exe)

tri_%-dynamicLib.exe: main.o timer.o utils.o libTri_%-dynamicLib.so
	$(CC) -fpic -o $@ $^

libTri_%-dynamicLib.so: %.o unused.o
#	TODO: écrire la règle permettant de créer une bibliothqèue dynamique
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ 

####
# Exercice 7:
DYNAMIC_LOAD=tri.exe

# Attention, c'est la première règle sans % et donc cela deviendra la règle par défaut quand elle sera activée
# pour compiler tous les programmes, il faudra faire: make all
 tri.exe: main_dynload.o load_library.o timer.o utils.o
#	TODO: écrire la règle permettrant de créer une bibliothèque que l'on charge explicitement
	$(CC) -rdynamic -o $@ $^ -ldl

####
# Exercice 8:
DYNAMIC_LOAD=tri2.exe
tri2.exe: main_dynload2.o load_library.o timer.o utils.o
	$(CC) -rdynamic -o $@ $^ -ldl
	

#---------------------------------------------------------------------------------
# DO NOT EDIT below this line
#---------------------------------------------------------------------------------

CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 -g -fpic

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

EXE=tri_bubble.exe tri_insertion.exe tri_merge.exe tri_quick.exe # tri.exe tri_shell.exe

# Si .SECONDARY est défini, permet d'éviter d'effacer les .o générés (ils ne sont plus considérés comme intermédiaires)
.SECONDARY: $(OBJS)

# Variable contenant le nom de tous les programmes à générer
PROGS=$(BASIC_EXE) $(STATIC_EXE) $(STATIC_LIB) $(DYNAMIC_LIB) $(DYNAMIC_LOAD) $(DYNAMIC_LOAD2) 

# Cible générale: génère l'ensemble des programmes spécifiés dans la variable PROGS
all: $(PROGS)

# Nettoyage des sources: efface tous les fichiers générés par la compilation et les scories
clean:
	rm -f *.a *.so *.exe *.o *~ \#*

#---------------------------------------------------------------------------------
# Tests
#---------------------------------------------------------------------------------

test: all
	@echo "*** Début des tests des programmes générés"
	@for sortProg in $(PROGS) ; do \
		echo "Lancement du programme: $$sortProg" ;\
		./$$sortProg -v -s 10; \
		echo ;\
	done
	@echo "*** Fin des tests"
