#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>

#ifndef NANO_TO_SECONDS
#   define NANO_TO_SECONDS 1000000000L
#endif

struct timespec timer_start();
long timer_end(struct timespec start_time);

#endif