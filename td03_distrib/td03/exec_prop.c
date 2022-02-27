#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    /*printf("Parent");
    if (!fork())
    {
        printf("Enfant");
        exit(0);
    }
    wait(NULL);
    puts("Fin");

    puts("Avant execve - affiché");

    printf("Dans buffer - pas affiché car buffers perdus");
*/
    execlp("./exec_prop-aux.exe", "exec_prop-aux.exe", "coucou", NULL);

    //puts("Après execve - pas affiché");
    return 0;
}