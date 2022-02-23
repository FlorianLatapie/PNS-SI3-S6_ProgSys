#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int nbFils = 10;

    for (int j = 0; j < nbFils; j++)
    {
        switch (fork())
        {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            for (int k = 0; k < 10; k++)
            {
                printf("fils: %d\n", j);
                sleep(1);
            }
            exit(0);

        default:
            exit(0);
        }
    }
    return 0;
}