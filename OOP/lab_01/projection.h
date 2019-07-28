#ifndef PROJECTION_H
#define PROJECTION_H

#include "geometry.h"

vector4f point3d_to_projective(const point3d_t &point);

matrix4f projection_matrix(double znear, double zfar, double aspect_ratio, double field_of_view);

point2d_t point3d_project(point3d_t point, matrix4f projection);

#endif // PROJECTION_H
