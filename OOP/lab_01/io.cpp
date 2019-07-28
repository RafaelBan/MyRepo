#include "io.h"

int io_open(IO &stream, const char *filename, char mode)
{
    int rc = __EXIT_SUCCESS;

    stream.mode = mode;

    switch (mode)
    {
    case 'w':
        stream.file = fopen(filename, "w");
        break;

    case 'r':
        stream.file = fopen(filename, "r");
        break;

    default:
        stream.mode = 0;
        rc = __EXIT_OPEN_ERR;
    }

    if (stream.file == NULL)
    {
        rc= __EXIT_OPEN_ERR;
    }

    return rc;
}

int io_close(IO &stream)
{
    int rc = __EXIT_SUCCESS;

    stream.mode = 0;

    if (fclose(stream.file) == EOF)
    {
        rc = __EXIT_CLOSE_ERR;
    }

    return rc;
}

int io_read_i(IO &stream, int *num_ptr)
{
    int rc = __EXIT_SUCCESS;

    if (stream.mode == 'r')
    {
        if (fscanf(stream.file, "%d", num_ptr) != 1)
        {
            rc = __EXIT_READ_ERR;
        }
    }
    else
    {
        rc = __EXIT_READ_ERR;
    }

    return  rc;
}

int io_read_d(IO &stream, double *num_ptr)
{
    int rc = __EXIT_SUCCESS;

    if (stream.mode == 'r')
    {
        if (fscanf(stream.file, "%lf", num_ptr) != 1)
        {
            rc = __EXIT_READ_ERR;
        }
    }
    else
    {
        rc = __EXIT_READ_ERR;
    }

    return  rc;
}

int io_write_i(IO &stream, int num)
{
    int rc = __EXIT_SUCCESS;

    if (stream.mode == 'w')
    {
        fprintf(stream.file, "%9d", num);
    }
    else
    {
        rc = __EXIT_WRITE_ERR;
    }

    return  rc;
}

int io_write_d(IO &stream, double num)
{
    int rc = __EXIT_SUCCESS;

    if (stream.mode == 'w')
    {
        fprintf(stream.file, "%9g", num);
    }
    else
    {
        rc = __EXIT_WRITE_ERR;
    }

    return  rc;
}

int io_put_space(IO &stream)
{
    int rc = __EXIT_SUCCESS;

    if (stream.mode == 'w')
    {
        fprintf(stream.file, " ");
    }
    else
    {
        rc = __EXIT_WRITE_ERR;
    }

    return  rc;
}

int io_put_linebreak(IO &stream)
{
    int rc = __EXIT_SUCCESS;

    if (stream.mode == 'w')
    {
        fprintf(stream.file, "\n");
    }
    else
    {
        rc = __EXIT_WRITE_ERR;
    }

    return  rc;
}
