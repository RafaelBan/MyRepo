#ifndef IO_H
#define IO_H

#include "exit.h"
#include <cstdio>

struct IO
{
    char mode;
    FILE *file;
};

int io_open(IO &stream, const char *filename, char mode);
int io_close(IO &stream);

int io_read_i(IO &stream, int *num_ptr);
int io_read_d(IO &stream, double *num_ptr);

int io_write_i(IO &stream, int num);
int io_write_d(IO &stream, double num);

int io_put_space(IO &stream);
int io_put_linebreak(IO &stream);

#endif // IO_H
