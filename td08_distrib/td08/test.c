/*
 * test.c        -- Un programme simple de test de malloc
 *
 * Erick Gallesio (2015/05/11)
 * Stéphane Lavirotte (2017/04/11)
 */

#include <stdio.h>
#include <strings.h>
#include "mymalloc.h"

#define N     10        /* nombre d'allocations par défaut */
#define SZMAX 200       /* taille maximum à allouer par défaut */

/* Boucle d'allocation n fois max (au maximum) caractères puis désallocation */
void do_alloc_free(int n, int max)
{
    void *tab[n];
    int i;

    /* boucle d'allocation */
    for (i = 0; i < n; i ++) {
        //int size = rand() % max;        /* tirer un nombre dans l'intervalle [0, max-1] */
        int size = ((rand() % 12) + 1) * 16; /* tirer un nombre multiple de 16 {16, 32, 48, 64, 80, ...,  192} */
        tab[i] = mymalloc(size);
        if (tab[i] == NULL)
            printf("**NOT OK @%d (size = %d)**\n", i, size);

        /* remplir la zone de zeros pour tester en écriture */
        bzero(tab[i], size);
    }

    /* boucle de libération de la mémoire:  */
    /*      - Etape 1: on libère un élément sur deux, histoire de morceler la mémoire */
    for (i = 0; i < n; i += 2) {
        if (tab[i] != NULL) myfree(tab[i]);
    }

    /*      - Etape 2: on alloue dans les nouveaux trous */
    for (i = 0; i < n; i += 2) {
        int size = rand() % max;        /* tirer un nombre dans l'intervalle [0, max-1] */
        tab[i] = mymalloc(size);
        if (tab[i] == NULL)
            printf("**NOT OK (2nd allocation loop) @%d (size = %d)**\n", i, size);
    }

    /*       - Etape 3: On libère le tout */
    for (i = 0; i < n; i++) {
        if (tab[i] != NULL) myfree(tab[i]);
    }
}

int main(int argc, char *argv[])
{
    int n = N;
    int szmax = SZMAX;

    switch (argc) {
    case 1:
        break;
    case 2:
        n = atoi(argv[1]);
        break;
    case 3:
        n     = atoi(argv[1]);
        szmax = atoi(argv[2]);
        break;
    default:
        fprintf(stderr, "Usage: %s [nloop [szmax]]\n", *argv);
        exit(1);
    }
    do_alloc_free(n, szmax);
    return 0;
}
