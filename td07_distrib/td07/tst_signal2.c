/*
Écrire un programme, tst_signal.exe, qui capture, grâce à la primitive d’Ansi C signal(), les signaux SIGSEGV
et SIGINT :
− lors de la réception d’un des signaux, le programme doit afficher un message indiquant quel est le signal qui
a été capturé ;
− par ailleurs, la réception de 5 signaux SIGINT consécutifs doit provoquer la terminaison du programme.
Après avoir mis en place la capture des signaux, le programme principal entrera dans une boucle infinie, du type
while (true) {} pendant laquelle vous aurez tout le loisir d’envoyer des SIGINT et des SIGSEGV (voir la note ciaprès).
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int nb_SIGINT = 0;

void on_signal(int sig)
{
    if (sig == SIGINT)
    {
        nb_SIGINT++;
    }

    printf("signal %d\nnb_SIGINT = %d\n", sig, nb_SIGINT);

    if (nb_SIGINT == 5)
    {
        exit(0);
    }
}

int main()
{
    nb_SIGINT = 0;
    signal(SIGSEGV, on_signal);
    signal(SIGINT, on_signal);
    sleep(5);
    return 0;
}