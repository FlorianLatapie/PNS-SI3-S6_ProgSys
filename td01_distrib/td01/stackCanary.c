#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int t[10];
  const int sig = 1234567890;
  
  for (int i = 0; i <= 10; i++) {
    t[i] = 0;
  }

  if (sig != 1234567890) {
    printf("Okay Houston, we've had a problem here!\n");
    exit(1);
  }

  return 0;
}