// création d'un named pipe en shell 
// cd /tmp ; mkfifo my_named_pipe ;

// q1 : En faisant ls -l, qu’est-ce qui distingue le fichier my_named_pipe des autres fichiers ?
// r1 : Le fichier my_named_pipe est un fichier de type pipe. on le remarque grace à la ligne qui commence par "p"

// q2 : QD’après vos connaissances actuelles, que faudrait-il faire pour avoir un système de chat bidirectionnel, c’est-à-dire que chaque processus soit à la fois lecteur et écrivain ?
// r2 : On crée un tube nommé, on lance les deux processus, on écrit dans le tube et on lit dans le meme tube.

// q3 : Que se passe-t-il s’il y a plusieurs lecteurs sur un tube nommé (vous constateriez le même comportement avec des tubes anonymes) ? Expliquez le phénomène observé à partir de vos connaissances.
// r3 : 

/*
A l’aide de la commande Shell mkfifo, créez un tube nommé my_named_pipe dans /tmp. Un premier programme
ecrivain.exe écrira dans un tube nommé et un programme lecteur.exe consommera les données injectées par
ecrivain.exe. Le nom du tube nommé utilisé par l’écrivain et le lecteur sera passé en paramètre au lancement des
programmes.
*/
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    assert(argc == 2);
    
    int fichier = open(argv[1], O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    char string[] = "abcdefghijklmnopqrstuvwxyz";
    write(fichier, string, strlen(string));
    close(fichier);

    return 0;
}
