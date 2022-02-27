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
        exit(0);
    default:
        printf("parent\n");
    }

    printf("pid parent : %d\n", getpid());
    printf("ce buffer sera perdu car il n'y a pas de \\n à la fin");
    
    execlp("./exec_prop-aux.exe", "exec_prop-aux.exe", "coucou", NULL);

    printf("ce buffer sera perdu car après exceclp\n");
    // puts("Après execve - pas affiché");
    return 0;
}