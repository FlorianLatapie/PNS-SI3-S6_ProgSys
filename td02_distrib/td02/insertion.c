//Insertion sort is another n^2 algorithm, which works by taking each element
//and inserting it into the proper spot.  Can work quickly on arrays that
//are either small or nearly sorted already.

void sort(int list[], int size)
{
    for (int j = 1; j < size; j++) {
        int key = list[j];
        int i = j - 1;
        while (i > -1 && list[i] > key) {
            list[i + 1] = list[i];
            i = i - 1;
        }
        list[i + 1] = key;

    }
}
