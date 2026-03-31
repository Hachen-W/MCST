#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "array/array.h"


int array_read(Array *array);
int process(Array *array);


const int INITIAL_CAPACITY = 16;


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <threads_count>\n", argv[0]);
        return 1;
    }

    unsigned int threads_count = atoi(argv[1]);
    if (threads_count == 0)
    {
        fprintf(stderr, "Wrong value of threads_count!");
        return 1;
    }
    
    int checker = 0;
    Array array = {0};

    checker = array_make(&array, INITIAL_CAPACITY);
    if (checker != 0)
        return checker;

    checker = array_read(&array);
    if (checker != 0)
        return checker;

    process(&array);

    array_output(&array);

    return 0;
}


int array_read(Array *array)
{
    int new_elem = 0;

    while (scanf("%d", &new_elem) == 1)
        array_push(array, new_elem);

    return 0;
}


int process(Array *array)
{

}
