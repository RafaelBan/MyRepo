#include "handler.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

Handler handler_create()
{
    return {
        .filename = NULL,
        .tdata = {0, 0, 0},
        .sdata = {0, 0, 0},
        .rdata = {0, 0, 0},
        .pointsq = 0,
        .points = NULL,
        .cameraDistance = 50
    };
}

int handler_set_filename(Handler &handler, const char *filename)
{
    size_t n = strlen(filename);

    free(handler.filename);

    handler.filename = (char *)malloc(n + 1);

    strcpy(handler.filename, filename);

    return n;
}

translation_base handler_read_translate(const Handler handler)
{
    return handler.tdata;
}

scaling_base handler_read_scaling(const Handler handler)
{
    return handler.sdata;
}

rotation_base handler_read_rotation(const Handler handler)
{
    return handler.rdata;
}
