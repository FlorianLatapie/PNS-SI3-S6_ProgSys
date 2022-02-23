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
        for (int k = 0; k < 10; k++)
            printf("fils: %d\n", 1);

        exit(0);
    default:
        sleep(10);
    }

    return 0;
}