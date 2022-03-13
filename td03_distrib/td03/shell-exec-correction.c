/* ------------------------------------------------------------------------------------
 * Primitives de POSIX.1
 * ------------------------------------------------------------------------------------
 * Jean-Paul Rigault --- ESSI --- Mars 2005
 * d'après une correction d'Erick Gallesio (ESSI)
 * $Id: shell-exec.c,v 1.1 2005/03/31 14:31:31 jpr Exp $
 * ------------------------------------------------------------------------------------
 * Simulation de l'exécution des commandes par le shell
 *
 * Cette version utilise directement execXX()
 * ------------------------------------------------------------------------------------
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char *home;

    /* Exécution de "who" */
    switch (fork()) {
    case -1: /* Erreur */
        perror("fork");
        abort();

    case 0: /* Processus fils qui exécute la commande */

        execlp("who", "who", 0);
        /* On ne doit pas passer ici */
        perror("exit who");
        exit(1);

    default: /* Le père attend */
        wait(0);
        break;
    }

    /* Exécution de "cd" directemnt :
     * On ne peut pas faire comme ci-dessus avec fork()/exec() car
     *
     *	1. il n'existe pas de /bin/cd ou autre exécutable adéquat...
     *	2. ... car, s'il existait, le changement de répertoire se produirait
     *	   uniquement dans le processus fils, et serait donc sans effet sur
     *	   les commandes suivantes.
     *
     * 'cd' est donc une de ces commandes *internes* (built-in) que le shell
     * doit exécuter directement (sans fork()). C'est le cas de toutes les
     * commandes qui modifient les attributs du processus.
     */
    home = getenv("HOME");
    if (home == 0 || strcmp(home, "") == 0) {
        fprintf(stderr, "Cannot locate home directory\n");
        exit(1);
    }
    if (chdir(getenv("HOME")) < 0) {
        perror("chdir");
        exit(1);
    }

    /* Exécution de "ls -ls" :
     * on revient au schéma normal
     */
    switch (fork()) {
    case -1:
        perror("fork");
        abort();

    case 0: /* Processus fils qui exécute la commande */

        execlp("ls", "ls", "-ls", 0);
        /* On ne doit pas passer ici */
        perror("exit ls");
        exit(1);

    default: /* Le père attend */

        wait(0);
        break;
    }

    /* Fin du programme */
    exit(0);

}


