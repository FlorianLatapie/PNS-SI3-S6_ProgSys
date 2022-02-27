#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        switch (fork())
        {
        case -1:
            perror("fork");
            exit(1);
        case 0:;
            char *current_env = getenv("HOME");

            if (chdir(current_env))
            {
                perror("Error: cd command");
            }

            execlp("ls", "ls", "-ls", NULL);

            exit(0);
        }
        wait(NULL);
        execlp("whoami", "whoami", NULL);
        exit(0);
    }
    wait(NULL);

    return 0;
}
