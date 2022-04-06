/*
 * test-limit.c  -- Test aux limites en écrivant en début et fin de zone allouée
 *
 * Alloue et écrit des valeurs aux extrémités des zones allouées.
 *
 * Hélène Collavizza (2020/04/10)
 */
#include "mymalloc.h"

int main()
{
    char *t1, *t2, *t3;
    t1 = mymalloc(300);
    *t1 = '1';
    *(t1 + 299) = '1';
    t2 = mymalloc(300);
    *t2 = '2';
    *(t2 + 299) = '2';
    myfree(t1);
    t3 = mymalloc(100);
    *t3 = '3';
    *(t3 + 99) = '3';
    return 0;
}