#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    int nbFils = 10;

    for (int j = 0; j < nbFils; j++)
    {
        switch (fork())
        {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            ++i;
            for (int k = 0; k < 10; k++)
                printf("fils: %d\n", j);
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}