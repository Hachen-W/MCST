#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <sys/stat.h>


void output_properties(char *argv[], struct stat stats);
const char *file_type(mode_t mode);


#endif