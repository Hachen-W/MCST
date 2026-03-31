#include "main.h"


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

    process(&array, threads_count);

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


int process(Array *array, unsigned int threads_count)
{
    sort_parts(array, threads_count);
}


int sort_parts(Array *array, unsigned int threads_count)
{
    if (threads_count > array->size)
        threads_count = array->size;

    pthread_t *threads = malloc(sizeof(pthread_t) * threads_count);
    ThreadData *tasks = malloc(sizeof(ThreadData) * threads_count);
    int *buffer = malloc(sizeof(int) * array->size);
    int *lefts = malloc(sizeof(int) * threads_count);
    int *rights = malloc(sizeof(int) * threads_count);
    int result = 1;

    if (threads == NULL || tasks == NULL || buffer == NULL ||
            lefts == NULL || rights == NULL)
        goto cleanup;

    int base = array->size / threads_count;
    int rem = array->size % threads_count;
    int start = 0;
    for (unsigned int thread_index = 0; thread_index < threads_count; thread_index++)
    {
        int part_size = base;
        if (thread_index < rem)
            part_size++;

        tasks[thread_index].data = array->data;
        tasks[thread_index].left = start;
        tasks[thread_index].right = start + part_size;

        lefts[thread_index] = tasks[thread_index].left;
        rights[thread_index] = tasks[thread_index].right;

        start = tasks[thread_index].right;

        if (pthread_create(&threads[thread_index], NULL, array_sort, &tasks[thread_index]) != 0)
            goto cleanup;
    }

    for (unsigned int thread_index = 0; thread_index < threads_count; thread_index++)
        if (pthread_join(threads[thread_index], NULL) != 0)
            goto cleanup;

cleanup:
    free(threads);
    free(tasks);
    free(buffer);
    free(lefts);
    free(rights);
    return result;
}
