if [ -z "$1" ]; then
    echo -e "Aucun argument donné\nUsage: ./run_exo.sh <exo_number>"
else
    make
    echo -e "\n--- lancement du programme" exo$1 "---\n"
    java -Djava.library.path=./lib exo$1
fi
