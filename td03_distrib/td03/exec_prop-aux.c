#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("%d %s\n", getpid(), argv[1]);
    return 0;
}