#include <unistd.h>
#include <stdio.h>

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
    write(p[1], "0123456789", sizeof("0123456789"));
    close(p[1]);
    lecture(p[0]);
    close(p[0]);
    return 0;
}