Title: Une nouvelle organisation pour le TD-08 
Author: Erick Gallesio, Stéphane Lavirotte, Hélène Collavizza
Date:  9-Apr-2020 14:00
Modified:  21-Apr-2020 08:59


Durant la séance de TD de la dernière fois, nous avons constaté que certains avaient du mal avec 
l'organisation des fichiers, avec le Makefile, ... 

Cette nouvelle organisation devrait être plus facile à appréhender. 

- le fichier `mymalloc.h` contient les déclarations des fonctions que vous
  devez implémenter. Ce fichier 
     - **ne doit pas être modifié**.
     - **doit être inclus** par les programmes qui veulent utiliser de l'allocation dynamique
     (avec votre version de malloc, ou avec la version standard de C).
  
- le fichier `mymalloc.c` est le fichier que vous devez construire. Pour
  l'instant, il contient toutes les fonctions, mais leur corps est vide.
  
- Trois fichiers sources complets de test sont fournis:
     - test-simple.c (quelques malloc, pas de boucle)
     - test-limit.c (quelques mallocs et des écritures de valeurs aux extrémités des zones allouées,
       vous pouvez espionner les valeurs écrites en mémoire avec le débogueur sous VScode)
     - test.c (un test un peu plus complet qui alloue pas mal et désalloue ensuite).

- le fichier `Makefile` regarde les fichiers `.c` de votre répertoire. Pour
  un fichier de nom `xxx.c` (sauf pour mymalloc.c bien sûr), il construit:
     - `xxx.exe` qui est le fichier utilisant les fonctions d'allocations écrites
     - `xxx.html` qui permet de visualiser les allocations faites dans un navigateur Web.
       
**Exemple d'utilsation:** Je me demande ce qu'il se passe si j'alloue un
bloc de 1000 caractères (plus que les 800 faits par le `sbrk` par
défaut). J'écris le petit programmes `prog.c` suivant:

```c
#include <stdio.h>
#include "mymalloc.h"

int main() {
  void *x= mymalloc(1000);
  return 0;
}
```

Après le lancement de la commande `make`, j'ai donc 2 fichiers construits:
   - `prog.exe` et `prog.html` qui utilisent le `mymalloc` que vous avez écrit


**Notes**:
  - Il est possible (mais pas souhaitable) d'utiliser du `mymalloc` et du
    `malloc` dans un même programme (dans le .h, nous redéfissons le malloc
    et free standard aux nouvelles fonctions mymalloc et myfree).
  - Le dossier HTML contient des exemples de référence, vous ne devez pas y toucher. 
    Il s'agit des sorties HTML produites pour les programmes `test` et
    `test-simple` pour le malloc standard (`test-std-malloc.html` et 
    `test-simple-std-malloc.html`) et pour le mymalloc que vous devez écrire
    (`test-my-malloc.html` et `test-simple-my-malloc.html`).
 - En cas de besoin, vous pouvez utilser le convertisseur décimal/hexdécimal suivant:
 http://sebastienguillon.com/test/javascript/convertisseur.html