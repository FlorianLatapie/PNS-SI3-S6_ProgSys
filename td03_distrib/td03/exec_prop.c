#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    switch (fork())
    {
    case -1:
        perror("fork");
        exit(1);
    case 0:
        printf("enfant\n");
        printf("ceci ne flushe pas");
        exit(0);
    default:
        printf("parent\n");
        printf("ceci ne flushe pas");
    }
    printf("ceci ne flushe pas");
    execlp("./exec_prop-aux.exe", "exec_prop-aux.exe", "coucou", NULL);

    // puts("Après execve - pas affiché");
    return 0;
}