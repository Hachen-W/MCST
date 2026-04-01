#include "main.h"


void greeting();
int process(int fifo_fd);
int request_wait(fd_set *fds_ready, int fd_fifo);


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <threads_count>\n", argv[0]);
        return 1;
    }

    unsigned int checker = 0;
    int fd_fifo = open(argv[1], O_RDWR);
    if (fd_fifo < 0)
    {
        close(fd_fifo);
        fprintf(stderr, "Wrong path!\n");
        return 1;
    }

    greeting();
    checker = process(fd_fifo);

    close(fd_fifo);
    return checker;
}


int process(int fd_fifo)
{
    fd_set fds_ready;
    int current_pid = get_pid();
    int checker = 0;

    while(1)
    {
        if (request_wait(&fds_ready, fd_fifo) < 0)
            break;

        /* читать из stdin и писать в fifo */
        if (FD_ISSET(STDIN_FILENO, &fds_ready))
            if (process_stdin(fd_fifo, current_pid) != 0)
                return 1;

        /* читать из fifo и пиать в stdout */
        if (FD_ISSET(fd_fifo, &fds_ready))
            if(process_fifo(fd_fifo, current_pid) != 0)
                return 1;
    }

    return checker;
}


int request_wait(fd_set *fds_ready, int fd_fifo)
{
    FD_ZERO(fds_ready);
    FD_SET(STDIN_FILENO, fds_ready);
    FD_SET(fd_fifo, fds_ready);

    int fd_count = 0;
    int fd_max = fd_fifo;
    if (STDIN_FILENO > fd_fifo)
        fd_max = STDIN_FILENO;

    while (1)
    {
        fd_count = select(fd_max + 1, fds_ready, NULL, NULL, NULL);
        if (fd_count > 0)
            return 0;

        if (fd_count < 0 && errno == EINTR)
            continue;

        fprintf(stderr, "Error im select()!");
        return -1;
    }
}


void greeting()
{
    printf("The connection is established!\n");
    printf("Process PID = %d\n", getpid());
    printf("Type message and then press Enter...\n");
}
