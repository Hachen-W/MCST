typedef struct
{
    int *data;
    unsigned int capacity;
    unsigned int size;
} Array;


int array_make(Array *array, unsigned int capacity);
int array_update(Array *old_array, unsigned int capacity);
int array_destroy(Array *array);
int array_push(Array *array, int value);
void array_output(Array *array);
