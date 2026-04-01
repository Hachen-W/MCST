#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#define BUFFER_SIZE 4096


int process(FILE *fd_input, FILE *fd_output);
int mode_parsing(const char *str_mode);
int string_clean(char* string);
int lines_comparator(const void *first, const void *second);


enum SortMode
{
    PLAIN = 0,
    LEX,
    RPLAIN,
    RLEX,
};

static enum SortMode sort_mode;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Use %s <input_file> <output_file> <plain|lex|rplain|rlex>\n", argv[0]);
        return 1;
    }

    int checker = 0;
    FILE *fd_input, *fd_output;

    checker = mode_parsing(argv[3]);
    if (checker != 0)
    {
        fprintf(stderr, "Incorrect sort mode: %s\n", argv[3]);
        return checker;
    }

    fd_input = fopen(argv[1], "r");
    if (fd_input == NULL)
    {
        checker = 1;
        fprintf(stderr, "Can't open input file: %s\n", argv[1]);
        return checker;
    }

    fd_output = fopen(argv[2], "w");
    if (fd_output == NULL)
    {
        checker = 1;
        fclose(fd_input);
        fprintf(stderr, "Can't open output file: %s\n", argv[2]);
        return checker;
    }

    checker = process(fd_input, fd_output);

    fclose(fd_input);
    fclose(fd_output);
    return checker;
}


int process(FILE *fd_input, FILE *fd_output)
{
    char buffer[BUFFER_SIZE];
    int checker = 0;
    unsigned int count = 0;
    unsigned int capacity = 0;
    char** lines = NULL;

    while (fgets(buffer, sizeof(buffer), fd_input) != NULL)
    {
        char *line = NULL;

        if (string_clean(buffer) != 0)
            continue;

        line = malloc(strlen(buffer) + 1);
        if (line == NULL)
        {
            fprintf(stderr, "Incorrect malloc in process()!\n");
            checker = 1;
            break;
        }

        strcpy(line, buffer);

        if (count == capacity)
        {
            capacity = (capacity == 0) ? 8 : capacity * 2;
            char **new_lines = realloc(lines, capacity * sizeof(char *));
            if (new_lines == NULL)
            {
                checker = 1;
                fprintf(stderr, "Incorrect malloc in process()!\n");
                free(line);
                break;
            }
            lines = new_lines;
        }

        lines[count] = line;
        count++;
    }

    if (checker == 0)
        qsort(lines, count, sizeof(char *), lines_comparator);

    for (unsigned int index = 0; index < count; index++)
    {
        fprintf(fd_output, "%s\n", lines[index]);
        free(lines[index]);
    }
    free(lines);
    return checker;
}


int lines_comparator(const void *first, const void *second)
{
    const char *first_string = *(const char * const *)first;
    const char *second_string = *(const char * const *)second;
    int result;

    if (sort_mode == PLAIN || sort_mode == RPLAIN)
    {
        result = strcmp(first_string, second_string);
    }
    else
    {
        result = strcasecmp(first_string, second_string);
    }

    if (sort_mode == RPLAIN || sort_mode == RLEX)
        result = -result;

    return result;
}


int string_clean(char* string)
{
    unsigned int length = strlen(string);
    while (length > 0 && (string[length - 1] == '\n' || string[length - 1] == '\r'))
    {
        string[length - 1] = '\0';
        length--;
    }

    for (unsigned int index = 0; string[index] != '\0'; index++)
        if (!isspace((unsigned char)string[index]))
            return 0;

    return 1;
}


int mode_parsing(const char *str_mode)
{
    if (strcmp(str_mode, "plain") == 0)
    {
        sort_mode = PLAIN;
        return 0;
    }
    if (strcmp(str_mode, "lex") == 0)
    {
        sort_mode = LEX;
        return 0;
    }
    if (strcmp(str_mode, "rplain") == 0)
    {
        sort_mode = RPLAIN;
        return 0;
    }
    if (strcmp(str_mode, "rlex") == 0)
    {
        sort_mode = RLEX;
        return 0;
    }
    return 1;
}
