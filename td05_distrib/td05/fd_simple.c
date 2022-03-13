#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;

    printf("File descripteurs:\n");
    printf("stdin = %d\nstdout = %d\nstderr = % d\n", fileno(stdin), fileno(stdout), fileno(stderr));

    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        printf("%s = %d\n", argv[i], fd);
        close(fd);
    }
    return 0;
}