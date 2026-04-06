#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include <sys/stat.h>


void output_properties(char *argv[], struct stat stats);
const char *file_type(mode_t mode);
void mode_to_letters(mode_t mode, char *str);
void print_time(const char *label, struct timespec ts);


#endif