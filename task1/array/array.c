#include <stdio.h>
#include <stdlib.h>
#include "array.h"


int array_make(Array *array, unsigned int capacity)
{
    if (array == NULL)
        return 1;
    if (capacity == 0)
        *array = (Array){NULL, 0, 0};
    else {
        array->data = malloc(capacity * sizeof(int));
        if (array->data == NULL)
            return 1;
        array->capacity = capacity;
        array->size = 0;
    }
    return 0;
}


int array_update(Array *array, unsigned int capacity)
{
    if (array == NULL ||
            array->size > capacity)
        return 1;

    if (capacity == 0)
    {
        free(array->data);
        *array = (Array) {NULL, 0, 0};
    }
    else
    {
        int *temp_data = realloc(array->data, capacity * sizeof(int));
        if (temp_data == NULL)
            return 1;
        array->data = temp_data;
        array->capacity = capacity;
    }

    return 0;
}


int array_destroy(Array *array)
{
    if (array == NULL)
        return 1;

    free(array->data);
    array->data = NULL;
    array->capacity = 0;
    array->size = 0;
    return 0;
}


int array_push(Array *array, int value)
{
    if (array == NULL)
        return 1;

    int checker = 0;
    if (array->size == array->capacity)
    {
        unsigned int new_capacity = 1;
        if (array->capacity != 0)
            new_capacity = array->capacity * 2;
        checker = array_update(array, new_capacity);
        if (checker != 0)
            return checker;
    }

    array->data[array->size] = value;
    array->size++;

    return 0;
}


void array_output(Array *array)
{
    for (unsigned int index = 0; index < array->size; index++)
        printf("%d ", array->data[index]);
    printf("\n");
}
