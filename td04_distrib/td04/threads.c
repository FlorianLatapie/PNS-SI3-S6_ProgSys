#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <syscall.h>

void *fn_thread(void *arg) {
  int time = *(int *) arg; 

  if (time < 0){
        pthread_exit((void *) 1);
  }
    
  for (size_t i = 0; i < 5; i++)
  {
      printf("pid : %d, pthread_self : %ld\n", getpid(), pthread_self());
      printf("Linux Thread ID: %ld\n", syscall(SYS_gettid));

      sleep(time);
  }

  pthread_exit((void *) 0);
  return NULL;
}

int main(int argc, char const *argv[])
{
    printf("%d", getpid());

    // args
    assert(argc == 3);
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    // threads
    pthread_t th;
    pthread_t th2;

    long retour;
    long retour2;

    pthread_create(&th, NULL, fn_thread, (void *) &n1);
    pthread_create(&th2, NULL, fn_thread, (void *) &n2);

    pthread_join(th, (void*) &retour);
    pthread_join(th2, (void*) &retour2);

    printf("%ld, %ld\n", retour, retour2);

    return 0;
}
