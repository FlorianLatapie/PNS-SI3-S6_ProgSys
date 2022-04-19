/*
 * my-malloc.c  -- Implementation de malloc, free, calloc, realloc
 *
 * Implémentation first-fit pour malloc
 *
 * Erick Gallesio (2020/04/10)
 * Stéphane Lavirotte (2020/04/16)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

// ======================================================================
//
//    Définition des fonctions. NE PAS MODIFIER CETTE PREMIERE PARTIE.
//
// ======================================================================

// Les fonctions internes à implémenter
void *internal_malloc(size_t size);
void internal_free(void *ptr);
void *internal_calloc(size_t nmemb, size_t size);
void *internal_realloc(void *ptr, size_t size);

// Les fonctions externes: ces fonctions appellent les fonctions internes
//  que vous avez à écrire en y ajoutant une trace qui est utilisée par
//  to-html et villoc.py pour générer les .html
void *mysbrk(intptr_t increment)
{
  void *ret, *old, *tmp;
  static int first_call = 1;

  if (first_call)
  {
    old = sbrk(0);
    fprintf(stderr, "SYS_brk(0)                    =  %p\n", old);
    first_call = 0;
  }

  ret = sbrk(increment);
  tmp = ret + increment;
  fprintf(stderr, "SYS_brk(%p)                    = %p\n", tmp, tmp);
  return ret;
}

void *mymalloc(size_t size)
{
  void *ret = internal_malloc(size);
  fprintf(stderr, "mymalloc(%ld)                     = %p\n", size, ret);
  return ret;
}

void myfree(void *ptr)
{
  internal_free(ptr);
  fprintf(stderr, "myfree(%p)                    = <void>\n", ptr);
}

void *myrealloc(void *ptr, size_t size)
{
  void *ret = internal_realloc(ptr, size);
  fprintf(stderr, "myrealloc(%p, %ld)                     = %p\n", ptr, size, ret);
  return ret;
}

void *mycalloc(size_t nmemb, size_t size)
{
  void *ret = internal_calloc(nmemb, size);
  fprintf(stderr, "mycalloc(%ld, %ld)                   = %p\n", nmemb, size, ret);
  return ret;
}

// ======================================================================
//
//    Implementation
//
// ======================================================================

/* On suppose qu'on ajoute au moins 50 Headers au minimum */
#define MIN_ALLOCATION 50

/* Pour s'aligner sur des frontieres multiples
 * de la taille du type le plus contraignant
 */
#define MOST_RESTRICTING_TYPE long double
typedef union header
{ /* Header de bloc */
  struct
  {
    size_t size;       /* Taille du bloc */
    union header *ptr; /* bloc libre suivant */
  } info;
  MOST_RESTRICTING_TYPE dummy; /* Ne sert qu'a provoquer un alignement */
} Header;
#define HEADER_SIZE sizeof(Header)

#define NEXT(p) ((p)->info.ptr)
#define SIZE(p) ((p)->info.size)

/* L'unité de découpage de la mémoire est la taille de Header car ça permet de gérer facilement chaînage
   Le programme appelant malloc reçoit un pointeur et utilise la mémoire comme il veut.
   BLOCKS_TO_ALLOCATE renvoie le nombre de blocks nécessaires pour le malloc demandé, en tenant compte du header */
#define BLOCKS_TO_ALLOCATE(size) (1 + (size + HEADER_SIZE - 1) / HEADER_SIZE)

static Header base = {{0, &base}}; /* Le pointeur de départ: aucune zone allouée */
static Header *freep = &base;      /* freep pointe sur la 1ère zone libre */

/* ====================================================================== */

/* Utilisé si on n'a pas trouvé assez de place */
static void *allocate_core(size_t size)
{
  Header *new;

  // Allouer au moins MIN_ALLOCATION cellules
  if (size < MIN_ALLOCATION)
  {
    size = MIN_ALLOCATION;
  }

  new = mysbrk(size * HEADER_SIZE);

  // Si on a pas pu allouer assez de place
  if (new == (void *)-1)
  {
    return NULL;
  }

  // Mise à jour de la taille du header
  SIZE(new) = size;

  // Libérer ce bloc (ceci afin de le remettre dans la liste des blocs libres)
  internal_free(new + 1);

  // Retourner le pointeur vers le premier élément de la nouvelle zone
  return freep;
}

/* ====================================================================== */

void *internal_malloc(size_t size)
{
  // fait un appel à allocate_core si pas de place dans la liste freep
  size_t blocksToAllocate = BLOCKS_TO_ALLOCATE(size);
  Header *prevp = freep;
  Header *p = freep;

  // On cherche un bloc libre suffisamment grand
  while (p != NULL && SIZE(p) < blocksToAllocate)
  {
    Header *newPrevp = p;
    p = NEXT(p);

    if (p == freep)
    {
      size_t eblocks = blocksToAllocate < MIN_ALLOCATION ? MIN_ALLOCATION : blocksToAllocate;
      p = allocate_core(eblocks);
      break;
    }

    prevp = newPrevp;
  }

  if (SIZE(p) == blocksToAllocate)
  {
    NEXT(prevp) = NEXT(p);
  }
  else
  {
    Header *next = p + blocksToAllocate;
    NEXT(next) = NEXT(p);
    SIZE(next) = SIZE(p) - blocksToAllocate;
    SIZE(p) = blocksToAllocate;
    NEXT(prevp) = next;
  }
  return p + 1;
}

/* ====================================================================== */

void internal_free(void *ptr)
{
  // Libère la zone pointée par ptr en l'insérant dans freep
  // Essai de coller les blocs adjacents à cette zone
  // NOTA : la liste freep est triée par ordre croissant des adresses

  Header *bp, *p, *prevp;
  if (!ptr)
    return;                 // On peut appeller free avec NULL. Ne rien faire dans ce cas
  bp = ((Header *)ptr) - 1; // Ajuster bp sur le debut du bloc

  /* rechercher le block à supprimer */
  prevp = freep;
  p = NEXT(freep);
  while (NEXT(prevp) != freep && p <= bp)
  {
    prevp = p;
    p = NEXT(p);
  }

  /* Essayer de "coller" ce bloc au suivant */
  if (bp + SIZE(bp) == p)
  {
    SIZE(bp) += SIZE(p);
    NEXT(bp) = NEXT(p);
  }
  else
  {
    NEXT(bp) = p;
  }

  /* Essayer de "coller" ce bloc au precedent */
  if (prevp + SIZE(prevp) == bp)
  {
    SIZE(prevp) += SIZE(bp);
    NEXT(prevp) = NEXT(bp);
  }
  else
  {
    NEXT(prevp) = bp;
  }
}

/* ====================================================================== */

void *internal_calloc(size_t nmemb, size_t size)
{
  // Utilise internal_malloc
  void *ptr = internal_malloc(nmemb * size);
  if (ptr)
  {
    memset(ptr, 0, nmemb * size);
  }
  return ptr;
}

void *internal_realloc(void *ptr, size_t size)
{
  // utilise internal_free et internal_malloc
  return ptr;
}
