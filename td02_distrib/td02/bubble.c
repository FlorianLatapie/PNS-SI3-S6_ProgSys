// Bubble-sort is a simple sorting algorithm that repeatedly steps
//  through the list to be sorted, compares each pair of adjacent items
//  and swaps them if they are in the wrong order

#include "sort.h"

void sort(int list[], int size)
{
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j > i; j--) {
            if (list[j] < list[j - 1]) {
                temp = list[j - 1];
                list[j - 1] = list[j];
                list[j] = temp;
            }
        }
    }
}
