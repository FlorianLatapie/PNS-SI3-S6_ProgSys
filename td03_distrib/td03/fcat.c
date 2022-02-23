/* ------------------------------------------------------------------------------------
* Primitives de POSIX.1
* ------------------------------------------------------------------------------------
* Jean-Paul Rigault --- ESSI --- Mars 2005
* d'après une correction d'Erick Gallesio (ESSI)
* $Id: fcat.c,v 1.3 2005/04/09 18:47:50 jpr Exp $
* ------------------------------------------------------------------------------------
* Utilisateur réel et effectif et "set user's bit"
*
* Cet exécutable peut être testé avec le fichier d'essai exo5-test.txt pour
* lequel la Makefile installe des droits restreints (et adéquats)
* ------------------------------------------------------------------------------------
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* Indiquer ici l'UID de l'utilisateur qui a le privilège de lire vos fichiers */
const uid_t PRIV_UID = 25502;

/* Taille du buffer de lecture */
#define MAX_BUFF 1024

int main(int argc, char *argv[])
{
    int ruid;
    int fd;
    int n;
    char buff[MAX_BUFF];

    /* Il est assez délicat dans le cas général --- c'est-à-dire sans savoir a
    * priori ou est le fichier binaire exécutable --- mais pas impossible (à
    * faire à titre d'exercice) de vérifier que le programme a bien été
    * installé avec le "set user bit" ; on se contente donc ici de ce message
    */
    fprintf(stderr, "Attention : vérifiez que ce programme %s est installé\n"
            "avec le \"set user's bit\" "
            "sinon cela ne marchera pas !\n\n", argv[0]);

    /* Il est encore plus délicat de vérifier si ce programme réside sur un
    * volume où l'on peut utiliser le set user bit
    */
    fprintf(stderr, "Attention : le programme %s doit être installé sur un système\n"
            "de fichiers où le \"set user's bit\" est accepté\n"
            "(voir options de mount) sinon cela ne marchera pas !\n\n", argv[0]);

    /* On vérifie que l'UID *réel* du processus est celui de l'utilisateur
    * privilégié
    */
    ruid = getuid();
    if (ruid != PRIV_UID) {
        fprintf(stderr, "Erreur : vous n'êtes pas autorisé à utiliser ce programmme\n");
        fprintf(stderr, "votre uid est %d, celui autorisé est %d\n", ruid, PRIV_UID);
        exit(1);
    }

    /* On envoie un message disant que le changement d'identité est possible ;
    * ici à cause du set user bit, luid effectif doit être celui du
    * propriétaire de cet exécutable (celui qui accorde l'accès) */

    fprintf(stderr, "L'UID %d peut accéder aux fichiers lisibles par l'UID %d\n\n",
            ruid, geteuid());

    /* On lit le nom du fichier à consulter depuis les paramètres de la ligne
    * de commande
    */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fichier\n", argv[0]);
        exit(1);
    }

    /* On ouvre le fichier et on imprime le contenu ; quand l'utilisateur
    * effectif est le propriétaire du fichier à lire, et qu'il a lui-même le
    * droit de lire, ceci doit marcher
    */
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("open");
        exit(1);
    }

    printf("============== Début de fichier ====================\n");
    while ((n = read(fd, buff, MAX_BUFF)) > 0) write(1, buff, n);
    printf("============== Fin de fichier ====================\n");

    /* Fin du programme */
    exit(0);
}
