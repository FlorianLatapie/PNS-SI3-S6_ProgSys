#!/bin/sh
#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de fichiers et répertoires
#---------------------------------------------------------------------------------
# Jean-Paul Rigault (2005/03/25)
# Stéphane Lavirotte (2017/03/17)
# --------------------------------------------------------------------------------
# Test de la copie simple de fichiers
#---------------------------------------------------------------------------------

# Répertoire et commande de test
Tests=${1-Tests}
mycp=${2-../mycp1.exe}

# Mise en place des répertoires de test
./set_tst_dir.sh $Tests

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

# Tests communs à mycp1 et mycp2
#-------------------------------

cd $Tests

# Copies
echo "#------"
echo "Test de mycp1.exe dans le répertoire $Tests"

echo " - Test sur des actions correctes:"
$mycp foo foobar
isTestOK $?
$mycp bar barfoo
isTestOK $?
$mycp foo bar
isTestOK $?
$mycp foo BAZ/foo1
isTestOK $?
$mycp foobar barfoo BAZ
isTestOK $?

ls -lR .

# Copies impossibles
echo " - Test sur des actions incorrectes:"
$mycp BAZ BAR
isTestOK $? 1
$mycp foobar barfoo FOOBAR
isTestOK $? 1

exit 0
