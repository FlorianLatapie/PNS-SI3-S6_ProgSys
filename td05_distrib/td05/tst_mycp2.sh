#!/bin/sh
#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de fichiers et répertoires
#---------------------------------------------------------------------------------
# Jean-Paul Rigault (2005/03/25)
# Stéphane Lavirotte (2017/03/17)
# --------------------------------------------------------------------------------
# Test de la copie de fichiers avec options -v, -i et -r.
#---------------------------------------------------------------------------------

#
# Répertoire et commande de test
Tests=${1-Tests}
mycp=${2-../mycp2.exe}

isTestOK() {
	retVal=$1
	testVal="0"
	if [ "$2" != "" ]; then testVal="$2" ; fi

	if [ "$retVal" = "$testVal" ]
	then
		echo "Test OK."
	else 
		echo "Test NOT ok."
	fi
}

# Tests communs à mycp1 et mycp2 (non régression)
#------------------------------------------------

./tst_mycp1.sh $Tests ../mycp2.exe

# Tests spécifiques à mycp2 
#--------------------------

cd $Tests

# Copies
$mycp -i foo bar
isTestOK $?
$mycp -v foo bar
isTestOK $?
$mycp -v -i foo bar
isTestOK $?
$mycp -r foobar barfoo BAZ QUX
isTestOK $?
$mycp -r -i -v foobar barfoo BAZ QUX
isTestOK $?

exit 0
