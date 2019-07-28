#ifndef HANDLER_H
#define HANDLER_H

#include "projection.h"

struct translation_base
{
    double dx;
    double dy;
    double dz;
};

struct scaling_base
{
    double kx;
    double ky;
    double kz;
};

struct rotation_base
{
    double alphax;
    double alphay;
    double alphaz;
};

struct Handler
{
    char *filename;

    translation_base tdata;
    scaling_base sdata;
    rotation_base rdata;

    size_t pointsq;
    point2d_t *points;

    double cameraDistance;
};

Handler handler_create();

translation_base handler_read_translate(const Handler handler);

scaling_base handler_read_scaling(const Handler handler);

rotation_base handler_read_rotation(const Handler handler);

int handler_set_filename(Handler &handler, const char *filename);

#endif // HANDLER_H
