#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

/*
#ifdefined(Win32)
  #include <windows.h>
  #define psleep(sec) Sleep((sec) * 1000)
#elifdefined(Linux)
  #include <unistd.h>
  #define psleep(sec) sleep((sec))
#endif
*/

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define INITIAL_ALLUMETTES 19
#define NB_JOUEURS  2

/* Structure stockant les informations des threads joueurs et du jeu. */
typedef struct {
    int allumettes;

    pthread_t thread_jeu;
    pthread_t thread_joueurs[NB_JOUEURS];

    pthread_mutex_t mutex_jeu;
    pthread_cond_t cond_jeu;
    pthread_cond_t cond_joueurs;

} jeu_t;

static jeu_t jeu = {
    .allumettes = INITIAL_ALLUMETTES,

    .mutex_jeu = PTHREAD_MUTEX_INITIALIZER,
    .cond_jeu = PTHREAD_COND_INITIALIZER,
    .cond_joueurs = PTHREAD_COND_INITIALIZER,

};

/* Fonction pour tirer un nombre au sort entre 1 et max. */
static int get_random(int max)
{
    double val;

    val = (double) max * rand();
    val = val / (RAND_MAX) + 1.0;

    return ((int) val);
}

/* Fonction pour le thread du jeu. */
static void * fn_jeu(void *data)
{
    while (1) {

        /* Debut de la zone protegee. */
        pthread_mutex_lock(&jeu.mutex_jeu);
        pthread_cond_wait(&jeu.cond_jeu, &jeu.mutex_jeu);

        jeu.allumettes = INITIAL_ALLUMETTES;
        printf("Réinitialisation du jeu avec %d allumettes.\n", jeu.allumettes);

        pthread_cond_broadcast(&jeu.cond_joueurs);
        pthread_mutex_unlock(&jeu.mutex_jeu);
        /* Fin de la zone protegee. */
    }

    return NULL;
}

/* Fonction pour les threads des joueurs. */
static void * fn_joueurs(void * data)
{
    long nb = (long) data;

    while (1) {
        /* Le joueur tire au sort le nombre d'allumettes qu'il retire: entre 1 et 3 ou au maximum le nombre d'allumettes restantes */
        int val = get_random(MIN(3, jeu.allumettes));

        /* Debut de la zone protegee. */
        pthread_mutex_lock(&jeu.mutex_jeu);

        if (val > jeu.allumettes) {
            pthread_cond_signal(&jeu.cond_jeu);
            pthread_cond_wait(&jeu.cond_joueurs, &jeu.mutex_jeu);
        }

        jeu.allumettes = jeu.allumettes - val;
        printf("Joueur %ld prend %d allumettes, reste %d allumettes\n", nb, val, jeu.allumettes);
        pthread_mutex_unlock(&jeu.mutex_jeu);
        /* Fin de la zone protegee. */

        /* Le joueur attend 1 microseconde avant de rejouer */
        usleep(1); /* mais encore un problème si on enlève complètement cette attente... Mais là vous verrez cela plus tard */
    }

    return NULL;
}

int main(void)
{
    /* Initialisation du jeu Creation du thread du magasin. */
    printf("Creation du thread du jeu !\n");
    if (pthread_create(&jeu.thread_jeu, NULL, fn_jeu, NULL)) {
        printf("Erreur à la création du thread de jeu\n");
        perror("pthread_create jeu");
        exit(1);
    }

    /* Creation des threads des joueurs si celui du jeu a reussi. */
    printf("Creation des threads joueurs !\n");
    for (long i = 0; i < NB_JOUEURS; i++) {
        if (pthread_create(&jeu.thread_joueurs [i], NULL, fn_joueurs, (void *) i)) {
            printf("Erreur à la création du thread du joueur %ld\n", + i);
            perror("pthread_create joueur");
            exit(1);
        }
    }

    /* Attente de la fin de tous les threads. */
    for (int i = 0; i < NB_JOUEURS; i++) {
        pthread_join(jeu.thread_joueurs[i], NULL);
    }
    pthread_join(jeu.thread_jeu, NULL);

    return EXIT_SUCCESS;
}
