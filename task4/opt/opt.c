#include "opt.h"


const char *SHORT_OPTIONS = "-mcst";

void output_options(int argc, char *argv[])
{
    int opt_result = 0;
    Array founded_short = {0};
    Array founded_long = {0};
    Array founded_non = {0};

    opterr = 0;                 // Позволяет убрать сторонний вывод в stderr
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
                
                if (check_optarg(optarg) != 0) 
                {
                    char buffer[100];
                    snprintf(buffer, sizeof(buffer), "elbrus=%s", optarg);
                    array_push(&founded_long, strdup(buffer));
                }
                else
                    printf("Incorrect argument: %s\n", optarg);
                break;
            case 'm':
            case 'c':
            case 's':
            case 't':
                char s[2] = {opt_result, '\0'};
                array_push(&founded_short, strdup(s));
                break;
            case 1:
                array_push(&founded_non, strdup(optarg));
                break;
            case '?':
                if (optopt != 0)
                {
                    printf("Incorrect option: '%c'\n", optopt);
                    goto cleanup;
                }
                else
                {
                    printf("Incorrect option: '%s'\n", argv[optind - 1] + 2);
                    goto cleanup;
                }
                break;
        }
    }

    printf("Short options: ");
    array_output(&founded_short);
    printf("Long options: ");
    array_output(&founded_long);
    printf("Non options: ");
    array_output(&founded_non);

cleanup:
    array_destroy(&founded_short);
    array_destroy(&founded_long);
    array_destroy(&founded_non);
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
