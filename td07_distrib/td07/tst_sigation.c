/*
Réalisez le même programme, mais cette fois-ci en utilisant la primitive Posix sigaction() au lieu de signal().
Nous nommerons tst_sigaction.exe ce second programme.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int nb_SIGINT = 0;

void on_signal(int sig)
{
    printf("signal %d\nnb_SIGINT = %d\n", sig, nb_SIGINT);

    if (sig == SIGINT)
    {
        nb_SIGINT++;
    }

    if (nb_SIGINT == 5)
    {
        exit(0);
    }
}

int main()
{
    nb_SIGINT = 0;

    struct sigaction sigact = {
        .sa_handler = on_signal
    };

    sigaction(SIGSEGV, &sigact, NULL);
    sigaction(SIGINT, &sigact, NULL);

    for (;;)
    {
    }

    return 0;
}