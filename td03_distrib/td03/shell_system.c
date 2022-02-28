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
        if (!strcmp(command, "cd\n"))
        {
            if (chdir(getenv("HOME")))
                printf("Error: cd command");
        }
        else
        {
            system(command);
        }
    }

    return 0;
}
