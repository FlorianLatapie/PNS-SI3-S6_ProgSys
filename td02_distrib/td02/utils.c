#include <stdio.h>

void print_list(int list[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", list[i]);
    printf("\n");
}
