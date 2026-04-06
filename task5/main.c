#include "main.h"


int main()
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Errno = %d\n", errno);
        // Так как в современной версии glibc нет sys_errlist[], используется аналог - strerror
        fprintf(stderr, "strerror(%d) = %s\n", errno, strerror(errno));
        perror("Can't open\n");
        return errno;
    }

    close(fd);
    return 0;
}
