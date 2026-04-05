#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    char **data;
    unsigned int capacity;
    unsigned int size;
} Array;


int array_make(Array *array, unsigned int capacity);
int array_update(Array *old_array, unsigned int capacity);
int array_destroy(Array *array);
int array_push(Array *array, char* value);
void array_output(Array *array);
int array_read(Array *array);


#endif