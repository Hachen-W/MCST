#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "array/array.h"


void output_options(int argc, char *argv[]);
int check_optarg(char *optarg);

const char *SHORT_OPTIONS = "mcst";


int main(int argc, char *argv[])
{
    output_options(argc, argv);

    return 0;
}

void output_options(int argc, char *argv[])
{
    int opt_result = 0;
    Array array = {0};

    opterr = 0;             // Позволяет убрать сторонний вывод в stderr
    static struct option long_options[] = 
        {
            {"elbrus",  required_argument, 0, 0},
            {0, 0, 0, 0}
        };
    
    int option_index = 0;
    while ((opt_result = getopt_long(argc, argv, SHORT_OPTIONS, long_options, &option_index)) != -1)
    {
        switch (opt_result)
        {
            case 0:
                printf("Long option: %s\n", long_options[option_index].name);
                if (check_optarg(optarg) != 0)
                    printf("It's argument: %s\n", optarg);
                else
                    printf("Incorrect argument: %s\n", optarg);
                break;
            case 'm':
            case 'c':
            case 's':
            case 't':
                array_push(&array, opt_result);
                break;
        }
    }

    printf("Short options: ");
    array_output(&array);
}

int check_optarg(char *optarg)
{
    const char *valid_elbrus[] = 
        {
            "1c+", "2c+", "2c3",
            "4c", "8c", "16c"
        };

    int count = sizeof(valid_elbrus) / sizeof(valid_elbrus[0]);
    int found = 0;

    for (int index = 0; index < count; index++)
    {
        if (strcmp(optarg, valid_elbrus[index]) == 0)
        {
            found = 1;
            break;
        }
    }

    return found;
}
