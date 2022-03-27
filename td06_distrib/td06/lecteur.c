#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void lecture(int fd) {
    char buff[1];
    while (read(fd, buff, 1)) {
        write(STDOUT_FILENO, buff, sizeof(buff));
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    assert(argc == 2);

    int descripteurFichier = open(argv[1], O_RDONLY);    
    lecture(descripteurFichier);
    return 0;
}
