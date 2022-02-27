#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("%d %s\n", getpid(), argv[0]);
    return 0;
}