#include "timer.h"

/* Subtract the ‘struct timeval’ values X and Y, storing the result in RESULT.
   Return 1 if the difference is negative, otherwise 0. */
static int time_subtract(struct timespec *result, struct timespec *x, struct timespec *y) {
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_nsec < y->tv_nsec) {
        long nsec = (y->tv_nsec - x->tv_nsec) / NANO_TO_SECONDS + 1;
        y->tv_nsec -= NANO_TO_SECONDS * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_nsec - y->tv_nsec > NANO_TO_SECONDS) {
        long nsec = (x->tv_nsec - y->tv_nsec) / NANO_TO_SECONDS;
        y->tv_nsec += NANO_TO_SECONDS * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait. tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_nsec = x->tv_nsec - y->tv_nsec;

    /* Return 1 if result is negative, otherwise 0 */
    return x->tv_sec < y->tv_sec;
}

// call this function to start a nanosecond-resolution timer
struct timespec timer_start() {
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time)
{
    struct timespec end_time;
    struct timespec result;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    time_subtract(&result, &end_time, &start_time);
    return result.tv_nsec;
}
