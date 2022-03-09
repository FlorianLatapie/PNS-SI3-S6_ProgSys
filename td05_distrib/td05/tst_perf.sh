#! /bin/sh -v
#---------------------------------------------------------------------------------
# Primitives de POSIX.1 : Manipulations de fichiers et répertoires
#---------------------------------------------------------------------------------
# Jean-Paul Rigault --- ESSI --- Mars 2005
# $Id: tst_perf.sh,v 1.2 2005/04/11 07:42:17 jpr Exp $
# --------------------------------------------------------------------------------
# Etude de l'influence de la taille du buffer sur la copie
#---------------------------------------------------------------------------------

Tests=$1; 
mycp=$2; 
shift 2

# Création du répertoire de test
if [ ! -d $Tests ]
then
    mkdir $Tests    
fi

cd $Tests

# Mise en place d'un gros fichier. Sur mon système /etc/termcap 
# fait environ 700 koctets. Le fichier fera donc environ 7 Mo

cat /etc/termcap >> big_file
for i in 1 2 3 4 5 6 7 8 9 10
do
    cat /etc/termcap >> big_file
done  

# Copie

for bsize in $*
do
    echo -n $bsize " "
    $mycp -b $bsize big_file other_big_file |
                         grep 'Temps système' | awk -F':' '{print $3}' 
    echo "Taille $bsize terminé" 1>&2
done > plot.raw

ed - << EOF
a
set data style linespoints
set xlabel "Taille du buffer en octets"
set ylabel "Débit par rapport au temps système Mo/s" font "Helvetica-Oblique"
set encoding iso_8859_1
set terminal postscript eps color
set output "plot.eps"
plot "plot.raw"
.
w plot.gp
q
EOF

gnuplot plot.gp
