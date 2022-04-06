/*
 * my-malloc.h  -- Implementation de malloc, free, calloc, realloc
 *
 * Implémentation first-fit pour malloc
 *
 * Erick Gallesio (2020/04/10)
 * Stéphane Lavirotte (2017/04/11)
 */

#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_

#include <stdlib.h>

// Les fonctions à définir
void *mymalloc(size_t size);
void  myfree(void *ptr);
void *mycalloc(size_t nmemb, size_t size);
void *myrealloc(void *ptr, size_t size);

// Par sécurité, on ré-associce les fonctions standard sur les notres
#define malloc(sz)       mymalloc(sz)
#define free(p)          myfree(p)
#define calloc(n, sz)    mycalloc(n, sz)
#define realloc(p, sz)   myrealloc(p, sz)

#endif /* _MY_MALLOC_H_ */
