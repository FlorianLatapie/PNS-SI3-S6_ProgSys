#include <fcntl.h>


int main(int argc, char const *argv[])
{
    char buffer[MAX];
    int n;
    int fdin = open("foo", O_RDONLY | O_EXCL);
    int fdout = open("bar", O_WRONLY | O_TRUNC | O_CREAT, …);
    while ((n = read(fdin, buffer, MAX)) != 0){
        write(fdout, buffer, n);
    }
    return 0;
}
