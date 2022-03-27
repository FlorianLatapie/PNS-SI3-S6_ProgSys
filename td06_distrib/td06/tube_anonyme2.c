#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void lecture(int fd) {
    char buff[1];
    while (read(fd, buff, 1)) {
        write(STDOUT_FILENO, buff, sizeof(buff));
    }
    printf("\n");
}

int main() {
    int p[2];
    pipe(p);
    switch (fork())
    {
    case -1:
        perror("Erreur fork");
        abort();
    case 0:
        sleep(2);
        write(p[1], "0123456789", sizeof("0123456789"));
        close(p[1]);
        break;
    default:
        close(p[1]);
        lecture(p[0]); 
        close(p[0]);
        break;
    }   
    return 0;
}