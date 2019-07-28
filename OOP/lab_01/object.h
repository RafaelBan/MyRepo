#ifndef OBJECT_H
#define OBJECT_H

#include <cstdio>

#include "exit.h"

#include "io.h"
#include "projection.h"

struct Object
{
    size_t pointsq;
    point3d_t *points;

    size_t edgesq;
    size_t *nodes_1;
    size_t *nodes_2;
};

int object_read(Object &object, IO stream);

int object_write(const Object &object, IO stream);

int object_project(point2d_t **points, size_t &pointsq, const Object &object, double zoffset);

int object_translate(Object &object, double dx, double dy, double dz);

int object_scale(Object &object, double kx, double ky, double kz);

int object_rotate(Object &object, double alphax, double alphay, double alphaz);

int object_process(Object &object, matrix4f matrix);

void object_set_point(const Object &object, size_t i, point3d_t point);

void object_delete(Object &object);

bool object_is_null(const Object &object);

Object object_create();

point3d_t object_point(const Object &object, size_t i);

#endif // OBJECT_H
