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
        execlp("whoami", "whoami", NULL);
        exit(0);
    }
    wait(NULL);

    execlp("ls", "ls", "-ls", NULL);

    return 0;
}
