#include "main.h"
#include "fifo/fifo.h"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <path_fifo>\n", argv[0]);
        return 1;
    }

    int checker = 0;
    int fd_fifo = open(argv[1], O_RDWR);
    if (fd_fifo < 0)
    {
        fprintf(stderr, "Wrong open!\n");
        return 1;
    }

    greeting();
    checker = process(fd_fifo);

    close(fd_fifo);
    return checker;
}


void greeting()
{
    printf("The connection is established!\n");
    printf("Process PID = %ld\n", (long)getpid());
    printf("Type message and then press Enter...\n");
}
