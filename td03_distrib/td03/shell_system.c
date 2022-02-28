#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char command[100];

    while (1)
    {
        scanf("%s", command);

        printf("%s\n", command);

        system(command);
    }

    return 0;
}
