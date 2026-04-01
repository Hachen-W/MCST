#ifndef FIFO_H_ICLUDED
#define FIFO_H_INCLUDED


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int process(int fifo_fd);
int process_stdin(int fd_fifo, pid_t current_pid);
int process_fifo(int fd_fifo, pid_t current_pid);
int request_wait(fd_set *fds_ready, int fd_fifo);
int write_all(int fd, const char *buffer, int count);


#endif