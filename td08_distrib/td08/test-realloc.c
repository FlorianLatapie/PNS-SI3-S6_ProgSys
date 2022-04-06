/*
 * test-realloc.c  -- Un test de réallocation de mémoire déjà allouée
 *
 * Alloue et libère des zones mémoires puis réalloue certaines zones pour tester l'aglo realloc
 *
 * Stéphane Lavirotte (2020/04/16)
 */
#include <stdio.h>
#include <strings.h>
//#include <stdlib.h>
#include "mymalloc.h"

int main()
{
    void *ptr1 = mymalloc(128);
    void *ptr2 = mymalloc(256);
    void *ptr3 = mymalloc(128);
    void *ptr4 = mymalloc(512);
    myfree(ptr2);

    // Test realloc
    ptr1 = myrealloc(ptr1, 256);  // Etend une zone alors qu'il y a de la place après (>)
    ptr4 = myrealloc(ptr4, 1024); // Etend une zone alors qu'il y a de la place après
    ptr3 = myrealloc(ptr3, 256);  // Nécessite de bouger la zone et donc fait un appel à sbrk
    ptr1 = myrealloc(ptr1, 544);  // Cela rentre toujours dans la place libre (==) avec le déplacement du précédent

    return 0;
}
