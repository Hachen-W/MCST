#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED


#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "../array/array.h"


void output_options(int argc, char *argv[]);
int check_optarg(char *optarg);


#endif