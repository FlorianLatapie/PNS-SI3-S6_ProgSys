//Merge-sort is much faster than insertion-sort in general, and works by
//dividing the array successively into smaller arrays, sorting them, and then
//merging the results.  merge_sort is written as two functions, `merge` which takes two
//pre-sorted lists and merges them to a single sorted list.  This is called on by merge_sort,
//which also recursively calls itself.

static void merge(int list[], int p, int q, int r)
{
    //n1 and n2 are the lengths of the pre-sorted sublists, list[p..q] and list[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;
    //copy these pre-sorted lists to L and R
    int L[n1 + 1];
    int R[n2 + 1];
    for (int i = 0; i < n1; i++) {
        L[i] = list[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = list[q + 1 + j];
    }

    //Create a sentinal value for L and R that is larger than the largest
    //element of list
    int largest;
    if (L[n1 - 1] < R[n2 - 1]) largest = R[n2 - 1];
    else largest = L[n1 - 1];
    L[n1] = largest + 1;
    R[n2] = largest + 1;

    //Merge the L and R lists
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            list[k] = L[i];
            i++;
        } else {
            list[k] = R[j];
            j++;
        }
    }
}

static void merge_sort_aux(int list[], int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2; // floor((p + r) / 2);
        merge_sort_aux(list, p, q);
        merge_sort_aux(list, q + 1, r);
        merge(list, p, q, r);
    }

}

void sort(int list[], int size)
{
    merge_sort_aux(list, 0, size - 1);
}
