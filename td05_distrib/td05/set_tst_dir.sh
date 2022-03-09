#!/bin/sh
#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de fichiers et répertoires
#---------------------------------------------------------------------------------
# Jean-Paul Rigault (2005/03/25)
# Stéphane Lavirotte (2017/03/17)
# --------------------------------------------------------------------------------
# Mise en place du répertoire de test pour tst_lsrec.sh et tst_mycp[12].sh
#---------------------------------------------------------------------------------

# Répertoire de test
Tests=${1-Tests}

# Création du répertoire de test
if [ -d "$Tests" ]
then
	echo "Efface le dossier de test existant"
    rm -rf "$Tests"
fi
mkdir "$Tests"

# Mise en place de fichiers et de répertoires
cp util.h "$Tests"/foo
cp util.c "$Tests"/bar
mkdir "$Tests"/BAZ
cp util.h "$Tests"/BAZ/foo
mkdir "$Tests"/BAZ/QUX
cp util.h "$Tests"/BAZ/QUX/foo
cp util.c "$Tests"/BAZ/QUX/bar

# Affichage du contenu (avec le vrai ls)
echo "Affiche le contenu (avec le vrai ls pour référence)"
ls -laR "$Tests"

exit 0


