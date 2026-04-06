#include "main.h"

#define BUFFER_SIZE 1024


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_input = argv[1];
    const char *file_child = "output_child.txt";
    const char *file_parent = "output_parent.txt";
    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Error in fork()!");
        return 1;
    }

    if (pid == 0)
        file_copy(file_input, file_child);
    else
    {
        file_copy(file_input, file_parent);
        waitpid(pid, NULL, 0);
        file_output("Parent:\n", file_parent);
        file_output("Child:\n", file_child);
    }

    return 0;
}

void file_copy(const char *name_source, const char *name_destination)
{
    int fd_source = open(name_source, O_RDONLY);
    if (fd_source < 0)
    {
        fprintf(stderr, "Can't open source!\n");
        return;
    }

    int fd_destination = open(name_destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_destination < 0)
    {
        fprintf(stderr, "Can't work with destination file!\n");
        close(fd_source);
        return;
    }

    char buffer[BUFFER_SIZE];
    int readed = 0;
    while((readed = read(fd_source, buffer, sizeof(buffer))) > 0)
    {
        int off = 0;
        while (off < readed)
        {
            int written = write(fd_destination, buffer + off, readed - off);
            if (written < 0)
            {
                fprintf(stderr, "Error with writing to destination file!\n");
                close(fd_destination);
                close(fd_source);
                return;
            }
            off += written;
        }
    }

    if (readed < 0)
    {
        fprintf(stderr, "Can't read from source!\n");
        close(fd_destination);
        close(fd_source);
    }
    close(fd_destination);
    close(fd_source);
}

void file_output(const char *label, const char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Can't open file for output!\n");
        return;
    }

    char *buffer[BUFFER_SIZE];
    int readed = 0;

    write(STDOUT_FILENO, label, strlen(label));
    while ((readed = read(fd, buffer, BUFFER_SIZE)) > 0)
        write(STDOUT_FILENO, buffer, readed);
    write(STDOUT_FILENO, "\n", 1);
    
    if (readed < 0)
        fprintf(stderr, "Can't read from source!\n");
        
    close(fd);
}  
