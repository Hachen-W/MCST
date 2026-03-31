#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED


#include <stdlib.h>


int comparator_ints(const void *first, const void *second);
int sort_array(int* array, unsigned int count);
void sort_merge(int *source, int left, int middle, int right, int *destination);


#endif