/* ---------------------------------------------------------------------------------
 * Primitives de POSIX.1 : Signaux
 * ---------------------------------------------------------------------------------
 * Jean-Paul Rigault (2005/04/12)
 * Stéphane Lavirotte (2018/04/14)
 * ---------------------------------------------------------------------------------
 * Diverses manières d'ignorer un signal
 * ---------------------------------------------------------------------------------
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <assert.h>

/* Temps d'attente */
#define wait_time 5

/* Fonctions de capture des signaux (handler)
 * -----------------------------------------
 */

/* Capture informative */
void on_sig(int sig)
{
    if (sig == SIGINT) {
        printf("Signal capturé : SIGINT\n"
               "\t(si ce signal n'avait pas été capturé, le processus serait mort)\n");
    } else
        printf("Signal capturé : %d\n", sig);
}

void null_handler(int sig)
{
}

/* Fonction mettant le processus en attente
 * ----------------------------------------
 */
void process_wait(int tnum)
{
    printf("Test %d: début d'attente de %d secondes : entrez des '^C' (SIGINT)\n"
           "\t(pour terminer ce programme, entrez '^\\')\n", tnum, wait_time);

    sleep(wait_time);

    printf("Fin d'attente\n");
}

/* Programme principal
 * -------------------
 */
int main()
{
    struct sigaction sigact;
    sigset_t sigmask;
    sigset_t sigint_mask;

    /* Préparation commune de sigact */
    sigemptyset(&sigmask);
    sigact.sa_mask = sigmask;

    /* Test 1 : on ignore SIGINT */
    printf("On ignore SIGINT\n");
    sigact.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sigact, NULL);
    process_wait(1);
    putchar('\n');

    /* Test 2 : on trappe SIGINT et on le masque, puis on attend, puis on démasque */
    printf("On masque SIGINT\n");
    sigact.sa_handler = on_sig;
    sigaction(SIGINT, &sigact, NULL);
    sigemptyset(&sigint_mask);
    sigaddset(&sigint_mask, SIGINT);
    sigprocmask(SIG_BLOCK, &sigint_mask, NULL);
    process_wait(2);
    /* On démasque SIGINT */
    printf("On démasque SIGINT\n");
    sigprocmask(SIG_UNBLOCK, &sigint_mask, NULL);
    putchar('\n');

    /* Test 3 : on capture SIGINT avec un handler vide */
    sigact.sa_handler = null_handler;
    sigaction(SIGINT, &sigact, NULL);
    process_wait(3);
    putchar('\n');

    /* Test 4 : on capture SIGINT sans handler */
    sigact.sa_handler = NULL;
    sigaction(SIGINT, &sigact, NULL);
    process_wait(4);
    putchar('\n');

    /* Si vous avez fait un ^C et que ce message ne s'affiche pas, c'est que le
       programme a été interrompu par la réception du signal .*/
    printf("Fin du programme.");

    return 0;
}
