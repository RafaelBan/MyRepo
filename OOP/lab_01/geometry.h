#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>

double deg_to_rad(double degrees);

struct point2d_t
{
    double x;
    double y;
};

struct point3d_t
{
    double x;
    double y;
    double z;
};

struct vector4f
{
    double data[4];
};

struct matrix4f
{
    double data[4][4];
};

vector4f mult_matrix_vector4f(const matrix4f &matrix, const vector4f &vector);

matrix4f translate_matrix(double dx, double dy, double dz);

matrix4f scaling_matrix(double kx, double ky, double kz);

matrix4f rotation_xmatrix(double alphax);

matrix4f rotation_ymatrix(double alphay);

matrix4f rotation_zmatrix(double alphaz);

#endif // GEOMETRY_H
