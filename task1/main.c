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
        fprintf(stderr, "Wrong value of threads_count!\n");
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

    checker = process(&array, threads_count);
    if (checker != 0)
        return checker;

    array_output(&array);

    return 0;
}


int process(Array *array, unsigned int threads_count)
{
    if (threads_count > array->size)
        threads_count = array->size;
    int checker = 0;

    pthread_t *threads = malloc(sizeof(pthread_t) * threads_count);
    ThreadData *tasks = malloc(sizeof(ThreadData) * threads_count);
    int *buffer = malloc(sizeof(int) * array->size);
    int *lefts = malloc(sizeof(int) * threads_count);
    int *rights = malloc(sizeof(int) * threads_count);
    if (threads == NULL || tasks == NULL || buffer == NULL ||
            lefts == NULL || rights == NULL)
    {
        checker = 1;
        goto cleanup;
    }
    
    checker = sort_parts(array, threads_count, threads, tasks, lefts, rights);
    if (checker != 0)
        goto cleanup;
    merge_parts(array, threads_count, buffer, lefts, rights);

cleanup:
    free(threads);
    free(tasks);
    free(buffer);
    free(lefts);
    free(rights);

    return checker;
}


void *sort_part(void *part)
{
    ThreadData *thread_data = (ThreadData *) part;
    int count = thread_data->right - thread_data->left;
    sort_array(thread_data->data + thread_data->left, count);
    return NULL;
}


int sort_parts(Array *array, unsigned int threads_count, pthread_t *threads,
        ThreadData *tasks, int *lefts, int *rights
        )
{
    int base = array->size / threads_count;
    unsigned int rem = array->size % threads_count;
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

        if (pthread_create(&threads[thread_index], NULL, sort_part, &tasks[thread_index]) != 0)
            return 1;
    }

    for (unsigned int thread_index = 0; thread_index < threads_count; thread_index++)
        if (pthread_join(threads[thread_index], NULL) != 0)
            return 1;

    return 0;
}


void merge_parts(Array *array, unsigned int threads_count, 
        int *buffer, int *lefts, int *rights
        )
{
    int *source = array->data;
    int *destination = buffer;
    unsigned int parts_count = threads_count;

    while (parts_count > 1)
    {
        unsigned int new_parts_count = 0;

        for (unsigned int part_index = 0; part_index < parts_count; part_index += 2)
        {
            if (part_index + 1 < parts_count)
            {
                int left = lefts[part_index];
                int middle = rights[part_index];
                int right = rights[part_index + 1];

                sort_merge(source, left, middle, right, destination);

                lefts[new_parts_count] = left;
                rights[new_parts_count] = right;
                new_parts_count++;
            }
            else
            {
                int left = lefts[part_index];
                int right = rights[part_index];

                for (int index = left; index < right; index++)
                    destination[index] = source[index];
                
                lefts[new_parts_count] = left;
                rights[new_parts_count] = right;
                new_parts_count++;
            }
        }
        int *temp = source;
        source = destination;
        destination = temp;
        parts_count = new_parts_count;
    }

    if (source != array->data)
        for (unsigned int index = 0; index < array->size; index++)
            array->data[index] = source[index];
}
