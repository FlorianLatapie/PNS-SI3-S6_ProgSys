//Quicksort works by dividing the array based upon a 'pivot' element, everything
//to the right of it are greater than or equal to the pivot, everything
//smaller than the pivot are moved to the left.  Then the left and right
//arrays are sorted in the same way.  Works great on a random array, but
//data that is nearly already sorted are very slow by this method.

static int partition(int list[], int p, int r)
{
    int pivot, index, exchange_temp;
    pivot = list[r];
    index = p - 1;
    for (int i = p; i < r; i++) {
        if (list[i] <= pivot) {
            index++;
            exchange_temp = list[i];
            list[i] = list[index];
            list[index] = exchange_temp;
        }
    }
    exchange_temp = list[r];
    list[r] = list[index + 1];
    list[index + 1] = exchange_temp;
    return index + 1;
}

static void quicksort_aux(int list[], int p, int r)
{
    int q;
    if (p < r) {
        q = partition(list, p, r);
        quicksort_aux(list, p, q - 1);
        quicksort_aux(list, q + 1, r);
    }
}

void sort(int list[], int size)
{
    quicksort_aux(list, 0, size - 1);
}
