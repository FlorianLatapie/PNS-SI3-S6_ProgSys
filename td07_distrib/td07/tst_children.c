/*
Écrire un programme (tst_children.exe) qui lance deux processus fils, envoie le signal SIGUSR1 à son fils cadet,
et attend la terminaison de ses deux fils. A la réception de ce signal, le fils cadet envoie le signal SIGUSR2 au fils ainé
et se termine, en émettant un message. Sur réception de SIGUSR2, le fils ainé se termine également, avec un message.
Pour envoyer le signal kill, vous utiliserez la fonction Posix kill, bien entendu (vous ne ferez pas l’exec de la
commande Unix kill qui elle-même a été implémentée grâce à la fonction Posix kill).
*/
#include <signal.h>

int main(int argc, char const *argv[])
{
    int pid = fork();
    if (pid == 0)
    {
        int pid2 = fork();
        if (pid2 == 0)
        {
            kill(getppid(), SIGUSR2);
            exit(0);
        }
        else
        {
            kill(pid2, SIGUSR1);
            exit(0);
        }
    }
    else
    {
        int status;
        wait(&status);
        wait(&status);
    }
    return 0;
}
