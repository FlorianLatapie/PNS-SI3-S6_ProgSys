#include <stdlib.h>
#include <unistd.h>

int main()
{
    return execlp("/usr/bin/java", "java", "exo1", (char *)NULL);
}