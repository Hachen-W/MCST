#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "array/array.h"
#include "sort/sort.h"


typedef struct {
    int *data;
    int left;
    int right;
} ThreadData;


int array_read(Array *array);
int process(Array *array, unsigned int threads_count);
int sort_parts(Array *array, unsigned int threads_count, pthread_t *threads,
    ThreadData *tasks, int *lefts, int *rights);
void *sort_part(void *part);
void merge_parts(Array *array, unsigned int threads_count, 
    int *buffer, int *lefts, int *rights);

const int INITIAL_CAPACITY = 16;


#endif