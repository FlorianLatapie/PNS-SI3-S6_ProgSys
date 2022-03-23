#!/bin/sh

EXE=./redir.exe

echo "Affichage du contenu de /etc/passwd préfixé d'un numéro pour chaque ligne"
$EXE R /etc/passwd cat -n

echo
echo "Envoie le contenu de la commande date dans le fichier d.txt"
$EXE W date.txt date
echo "Affiche le contenu du fichier date.txt"
cat date.txt
rm -f date.txt

echo
echo "Redirige le contenu du fichier /etc/passwd préfixé d'un numéro pour chaque ligne dans le fichier out.txt"
$EXE W out.txt cat -n /etc/passwd
echo "Affiche le contenu du fichier out.txt"
cat out.txt
rm -f out.txt