#include "main.h"


#define MAX_LENGTH 2048

int main()
{
    char input[MAX_LENGTH];

    if (!fgets(input, sizeof(input), stdin))
        return 1;
    
    unsigned int length = strlen(input);
    while (length > 0 && (input[length - 1] == '\n' || input[length - 1] == ' ' || input[length - 1] == '\t'))
    {
        length--;
        input[length] = '\0';
    }

    return 0;
}
