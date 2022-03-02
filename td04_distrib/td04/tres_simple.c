

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *fn_thread(void *arg) {
  printf("Hello from the thread\n");
  sleep(2);
  printf("Bye bye from the thread\n");
  pthread_exit((void *) 1);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t th;
  long retour;

  pthread_create(&th, NULL, fn_thread,NULL);
  pthread_join(th, (void*) &retour);
  printf("Valeur renvoyée: %ld\n", retour);

  printf("The end\n");

  return 0;
}
