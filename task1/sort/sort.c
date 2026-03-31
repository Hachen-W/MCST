#include "sort.h"


int comparator_ints(const void *first, const void *second)
{
    int x = *(const int *) first;
    int y = *(const int *) second;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}


int array_sort(int* array, unsigned int count)
{
    if (array == NULL && count > 0)
        return 1;
    if (array != NULL && count > 1)
        qsort(array, count, sizeof(*array), comparator_ints);
    return 0;
}
