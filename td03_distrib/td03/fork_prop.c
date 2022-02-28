#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int f = fork();

    if (f == 0)
    {
        printf("enfant \n");
    }
    else
    {
        wait(NULL);
        printf("parent\n");
    }

    printf("the real user ID of the calling process. : %d\n", getuid());
    printf("the effective user ID of the calling process. : %d\n", geteuid());

    printf("the real group ID of the calling process. : %d\n", getgid());
    printf("the effective group ID of the calling process. : %d\n", getegid());

    printf("\n");

    if (f == 0)
    {
        exit(0);
    }
    else
    {
        return 0;
    }
}
