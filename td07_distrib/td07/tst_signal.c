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

static int nb_SIGSEGV = 0;

void on_SIGSEGV(int sig)
{
    nb_SIGSEGV++;
    printf("SIGSEGV %d\nnb_SIGSEGV = %d\n", sig, nb_SIGSEGV);

    if (nb_SIGSEGV == 5)
    {
        exit(0);
    }
}

void on_SIGINT(int sig)
{
    printf("SIGINT %d\n", sig);
}

int main()
{
    nb_SIGSEGV = 0;
    signal(SIGSEGV, on_SIGSEGV);
    signal(SIGINT, on_SIGINT);
    for (;;)
    {
    }

    return 0;
}