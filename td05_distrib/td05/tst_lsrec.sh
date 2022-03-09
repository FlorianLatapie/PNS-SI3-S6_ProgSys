#!/bin/sh
#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de fichiers et répertoires
#---------------------------------------------------------------------------------
# Jean-Paul Rigault (2005/03/25)
# Stéphane Lavirotte (2017/03/17)
# --------------------------------------------------------------------------------
# Test de lsrec (liste récursive)
#---------------------------------------------------------------------------------

# Mise en place des répertoires de test
./set_tst_dir.sh Tests

echo "#------"
echo "Test de lsrec.exe dans le répertoire de test créé"
./lsrec.exe Tests
