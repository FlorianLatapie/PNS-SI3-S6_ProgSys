/*
 * test-simple.c  -- Un test simple d'allocation pour mettre en évidence l'algo utilisé
 *
 * Alloue et libère des zones mémoires pour mettre en évidence l'algorithme utilisé (first fit)
 *
 * Stéphane Lavirotte (2020/04/07)
 */
#include <stdio.h>
#include <strings.h>
#include "mymalloc.h"

int main()
{
    void *ptr1 = mymalloc(128);
    void *ptr2 = mymalloc(256);
    void *ptr3 = mymalloc(128);
    void *ptr4 = mymalloc(512);
    myfree(ptr2);

    void *ptr5 = mymalloc(384);
    void *ptr6 = mymalloc(128);
    void *ptr7 = mymalloc(64);
    return 0;
}
