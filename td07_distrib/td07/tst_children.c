/*
Écrire un programme (tst_children.exe) qui lance deux processus fils, envoie le signal SIGUSR1 à son fils cadet,
et attend la terminaison de ses deux fils. A la réception de ce signal, le fils cadet envoie le signal SIGUSR2 au fils ainé
et se termine, en émettant un message. Sur réception de SIGUSR2, le fils ainé se termine également, avec un message.
Pour envoyer le signal kill, vous utiliserez la fonction Posix kill, bien entendu (vous ne ferez pas l’exec de la
commande Unix kill qui elle-même a été implémentée grâce à la fonction Posix kill).
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

static pid_t pidAine;
static pid_t pidCadet;

void cadet(int signal)
{
    printf("Cadet : réception du signal SIGUSR1 (%d)\nEnvoi du signal SIGUSR2 au fils ainé\n", signal);
    kill(pidAine, SIGUSR2);
    printf("Cadet : fin du processus\n");
    exit(0);
}

void aine(int signal)
{
    printf("Réception du signal SIGUSR2 (%d)\n", signal);
    printf("Aine : fin du processus\n");
    exit(0);
}

int main()
{
    struct sigaction sigact = {
        .sa_handler = SIG_IGN};

    pidAine = fork();

    switch (pidAine)
    {
    case -1:
        perror("fork");
        break;
    case 0:
        sigact.sa_handler = aine;
        sigaction(SIGUSR2, &sigact, NULL);
        while (1)
            ;
    }

    pidCadet = fork();
    switch (pidCadet)
    {
    case -1:
        perror("fork");
        break;
    case 0:
        sigact.sa_handler = cadet;
        sigaction(SIGUSR1, &sigact, NULL);
        while (1)
            ;
    }
    sleep(1);
    printf("SIGUSR1 --> fils cadet\n");
    kill(pidCadet, SIGUSR1);
    wait(NULL);
    wait(NULL);
    printf("Fin du programme\n");
    return 0;
}
