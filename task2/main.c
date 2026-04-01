#include "main.h"

#define BUFFER_SIZE 512


void greeting();
int process(int fifo_fd);
int process_stdin(int fd_fifo, pid_t current_pid);
int process_fifo(int fd_fifo, pid_t current_pid);
int request_wait(fd_set *fds_ready, int fd_fifo);
int write_all(int fd, const char *buffer, int count);


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


int process(int fd_fifo)
{
    fd_set fds_ready;
    pid_t current_pid = getpid();
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


int process_stdin(int fd_fifo, int current_pid)
{
    char buffer_input[BUFFER_SIZE];
    char buffer_output[BUFFER_SIZE];
    int readed_symbols = 0;
    int length = 0;

    readed_symbols = read(STDIN_FILENO, buffer_input, sizeof(buffer_input) - 1);
    if (readed_symbols < 0)
    {
        if (errno == EINTR)
            return 0;
        fprintf(stderr, "Error in process_stdin()!\n");
        return 1;
    }

    if (readed_symbols == 0)
        return 1;

    buffer_input[readed_symbols] = '\0';

    length = snprintf(
        buffer_output, sizeof(buffer_output), "%ld:%s",
        (long) current_pid, buffer_input
        );
    if (length < 0 || length >= (int)sizeof(buffer_output))
    {
        fprintf(stderr, "Message is too long!\n");
        return 0;
    }

    if (write_all(fd_fifo, buffer_output, (size_t) length) != 0)
    {
        fprintf(stderr, "Cant't write for fifo\n");
        return 1;
    }

    return 0;
}


int write_all(int fd, const char *buffer, int count)
{
    int written_all = 0;
    int written_current = 0;

    while (written_all < count)
    {
        written_current = write(fd, buffer + written_all, count - written_all);

        if (written_current < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        }

        written_all += written_current;
    }

    return 0;
}


int process_fifo(int fd_fifo, int current_pid)
{
    char buffer[BUFFER_SIZE];
    int readed_symbols = 0;
    char *colon_ptr = NULL;
    long pid_sender = 0;
    char *text = NULL;

    readed_symbols = read(fd_fifo, buffer, sizeof(buffer) - 1);
    if (readed_symbols < 0)
    {
        if (errno == EINTR)
            return 0;
        fprintf(stderr, "Error in process_fifo()!");
        return 1;
    }

    if (readed_symbols == 0)
        return 0;

    buffer[readed_symbols] = '\0';
    colon_ptr = strchr(buffer, ':');
    if (colon_ptr == NULL)
        return 0;

    *colon_ptr = '\0';
    pid_sender = atol(buffer);
    text = colon_ptr + 1;

    if ((pid_t)pid_sender != current_pid)
    {
        printf("%ld> %s", pid_sender, text);
        fflush(stdout);
    }

    return 0;
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
    printf("Process PID = %ld\n", (long)getpid());
    printf("Type message and then press Enter...\n");
}
