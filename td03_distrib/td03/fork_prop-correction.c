/* ------------------------------------------------------------------------------------
* Primitives de POSIX.1
* ------------------------------------------------------------------------------------
* Jean-Paul Rigault --- ESSI --- Mars 2005
* d'après une correction d'Erick Gallesio (ESSI)
* $Id: fork_prop.c,v 1.1 2005/03/31 14:31:31 jpr Exp $
* ------------------------------------------------------------------------------------
* Propriétés des processus fils
*
* Ce programme met en évidence les points suivants :
*
*	- un processus fils a les mêmes uid/gid réels/effectifs que son père
*	- un processus fils hérite des fichiers ouverts par son père avec partage
*	  du pointeur d'E/S : bien que le père et du fils s'exécutent en parallèle,
*	  leurs écritures élémentaires (chaque appel à write) n'entrent pas en
*	  conflit, mais se mettent sagement à la suite les unes des autres
*	  (en revanche on ne maitrise pas l'ordre)
*	- un processus fils hérite aussi des répertoires ouverts par son père
* 	- un processus orphelin est adopté par le processu de pid 1
*
* ------------------------------------------------------------------------------------
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

char msg_parent[] = "Parent\n";
char msg_child[] = "Child\n";

int main()
{
    int fd;
    DIR *dirp;
    struct dirent *dentry;

    /* Affichage des uid/gid du père */
    printf("Père : uid = %d euid = %d gid = %d egid = %d\n",
           getuid(), geteuid(), getgid(), getegid());

    /* Ouverture d'un répertoire */
    if ((dirp = opendir(".")) == NULL) perror("opendir()");

    /* Ouverture d'un fichier et écriture d'un message */
    fd = open("foo", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    write(fd, msg_parent, strlen(msg_parent));

    switch (fork()) {
    case -1: /* Erreur */
        perror("fork");
        abort();

    case 0: /* Processus fils */

        /* Affichage des uid/gid du fils */
        printf("Fils : uid = %d euid = %d gid = %d egid = %d\n",
               getuid(), geteuid(), getgid(), getegid());

        /* Lecture du répertoire ouvert par le père */
        if ((dentry = readdir(dirp)) == NULL) perror("readdir()");
        else printf("Lu correctement répertoire %s\n", dentry->d_name);

        /* Écriture d'un message dans le fichier hérité du père :*/
        write(fd, msg_child, strlen(msg_child));

        /* On attend que le père se termine */
        sleep(2);

        /* Écriture d'un message dans le fichier hérité du père  */
        write(fd, msg_child, strlen(msg_child));

        /* Affichage du pid du père (ce fils est devenu orphelin) */
        printf("PID du fils orphelin : %d", getppid());

        /* Fin du fils */
        exit(0);

    default: /* Suite du processus père */

        /* On attend afin que le fils puisse commencer à s'exécuter */
        sleep(1);

        /* Écriture d'un message dans le fichier commun */
        write(fd, msg_parent, strlen(msg_parent));
        printf("Imprimer le contenu du fichier foo\n");

        /* Le père se termine, rendant le fils orphelin */
        exit(0);
    }
    /*NOTREACHED*/
}


