#ifndef _TIMER_H_
#define _TIMER_H_

#define NANO_TO_MICRO 1000
#define NANO_TO_MILLI 1000000
#define NANO_TO_SECONDS 1000000000

/* Démarre un chronometre pour mesurer le temps process ecoulé en nano-secondes */
struct timespec timer_start();

/* Arrête le chronomètre et mesure le temps écoulé en nano-secondes */
long timer_end(struct timespec start_time);

#endif