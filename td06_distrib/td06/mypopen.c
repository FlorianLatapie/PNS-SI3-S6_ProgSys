/*
Le but de cet exercice est d’implémenter un équivalent de la fonction popen en lecture seule. D’après la page de
manuel (man 3 popen), cette fonction permet de récupérer les données produites par un processus dans le processus
appelant. Vous réaliserez une fonction mypopen simplifiée qui créera un tube, invoquera un Shell (execXX) pour
exécuter une commande passée en paramètre et retournera le descripteur de fichier permettant d’accéder aux données produites par la commande exécutée. Votre programme principal utilisera cette fonction pour afficher les données produites par la commande et se terminera en affichant le nombre de caractères total lus dans le tube.
*/
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void lecture(int fd) {
    char buff[1];
    while (read(fd, buff, 1)) {
        write(STDOUT_FILENO, buff, sizeof(buff));
    }
    printf("\n");
}

int mypopen(char *commande)
{
    int p[2];
    pipe(p);
    switch (fork())
    {
    case -1:
        perror("Erreur fork");
        abort();
    case 0:
        dup2(p[1], STDOUT_FILENO);
        execl("/bin/sh", "sh", "-c", commande, NULL);
        break;
    default:
        wait(NULL);
        close(p[1]);
    }
    return p[0];
}

int main()
{
    lecture(mypopen("ls -la"));
    return 0;
}
