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


int sort_array(int* array, unsigned int count)
{
    if (array == NULL && count > 0)
        return 1;
    if (array != NULL && count > 1)
        qsort(array, count, sizeof(*array), comparator_ints);
    return 0;
}


void sort_merge(int *source, int left, int middle, int right, int *destination)
{
    int left_index = left;
    int right_index = middle;
    int destination_index = left;

    while (left_index < middle && right_index < right)
    {
        if (source[left_index] <= source[right_index])
        {
            destination[destination_index] = source[left_index];
            destination_index++;
            left_index++;
        }
        else
        {
            destination[destination_index] = source[right_index];
            destination_index++;
            right_index++;
        }
    }

    while (left_index < middle)
    {
        destination[destination_index] = source[left_index];
        destination_index++;
        left_index++;
    }

    while (right_index < right)
    {
        destination[destination_index] = source[right_index];
        destination_index++;
        right_index++;
    }
}
