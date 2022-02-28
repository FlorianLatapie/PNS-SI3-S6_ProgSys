#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define MAX_LENGTH 100

int main(int argc, char const *argv[])
{
    while (1)
    {
        system("echo -n $PWD");
        printf("$ ");
        fflush(stdout);

        char command[MAX_LENGTH];

        fgets(command, MAX_LENGTH, stdin);

        if (!strcmp(command, "exit\n"))
        {
            break;
        }

        char testCd[2];
        testCd[0] = command[0];
        testCd[1] = command[1];
        testCd[2] = '\0';

        if (!strcmp(testCd, "cd\n"))
        {
            if (chdir(getenv("HOME")))
                printf("Error: cd command\n");
        }
        else
        {
            printf("oui system");
            system(command);
        }
    }

    return 0;
}
