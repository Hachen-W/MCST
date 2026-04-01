#include "main.h"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <threads_count>\n", argv[0]);
        return 1;
    }

    int fifo_fd = open(argv[1], O_RDWR);
    if (fifo_fd < 0)
    {
        fprintf(stderr, "Wrong path!\n");
    }

    return 0;
}
