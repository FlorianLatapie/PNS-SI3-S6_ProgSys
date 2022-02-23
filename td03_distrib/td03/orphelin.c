#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        printf("fils: %d, ppid : %d\n", 1, getppid());
        sleep(2);
        printf("fils: %d, ppid : %d\n", 1, getppid());

        exit(0);
    default:
        sleep(1);
    }

    return 0;
}