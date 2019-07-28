#include "geometry.h"

double deg_to_rad(double degrees)
{
    return M_PI / 180.0 * degrees;
}

vector4f mult_matrix_vector4f(const matrix4f &matrix, const vector4f &vector)
{
    vector4f result;

    result.data[0] = matrix.data[0][0] * vector.data[0] +
                     matrix.data[0][1] * vector.data[1] +
                     matrix.data[0][2] * vector.data[2] +
                     matrix.data[0][3] * vector.data[3];

    result.data[1] = matrix.data[1][0] * vector.data[0] +
                     matrix.data[1][1] * vector.data[1] +
                     matrix.data[1][2] * vector.data[2] +
                     matrix.data[1][3] * vector.data[3];

    result.data[2] = matrix.data[2][0] * vector.data[0] +
                     matrix.data[2][1] * vector.data[1] +
                     matrix.data[2][2] * vector.data[2] +
                     matrix.data[2][3] * vector.data[3];

    result.data[3] = matrix.data[3][0] * vector.data[0] +
                     matrix.data[3][1] * vector.data[1] +
                     matrix.data[3][2] * vector.data[2] +
                     matrix.data[3][3] * vector.data[3];

    return result;
}

matrix4f translate_matrix(double dx, double dy, double dz)
{
    matrix4f matrix;

    matrix.data[0][0] = 1;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[0][3] = dx;

    matrix.data[1][0] = 0;
    matrix.data[1][1] = 1;
    matrix.data[1][2] = 0;
    matrix.data[1][3] = dy;

    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 1;
    matrix.data[2][3] = dz;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 1;

    return  matrix;
}

matrix4f scaling_matrix(double kx, double ky, double kz)
{
    matrix4f matrix;

    matrix.data[0][0] = kx;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[0][3] = 0;

    matrix.data[1][0] = 0;
    matrix.data[1][1] = ky;
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 0;

    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = kz;
    matrix.data[2][3] = 0;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 1;

    return  matrix;
}

matrix4f rotation_xmatrix(double alphax)
{
    double angle;
    matrix4f matrix;

    angle = deg_to_rad(alphax);

    matrix.data[0][0] = 1;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[0][3] = 0;

    matrix.data[1][0] = 0;
    matrix.data[1][1] = +cos(angle);
    matrix.data[1][2] = +sin(angle);
    matrix.data[1][3] = 0;

    matrix.data[2][0] = 0;
    matrix.data[2][1] = -sin(angle);
    matrix.data[2][2] = +cos(angle);
    matrix.data[2][3] = 0;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 1;

    return  matrix;
}

matrix4f rotation_ymatrix(double alphay)
{
    double angle;
    matrix4f matrix;

    angle = deg_to_rad(alphay);

    matrix.data[0][0] = +cos(angle);
    matrix.data[0][1] = 0;
    matrix.data[0][2] = +sin(angle);
    matrix.data[0][3] = 0;

    matrix.data[1][0] = 0;
    matrix.data[1][1] = 1;
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 0;

    matrix.data[2][0] = -sin(angle);
    matrix.data[2][1] = 0;
    matrix.data[2][2] = +cos(angle);
    matrix.data[2][3] = 0;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 1;

    return  matrix;
}

matrix4f rotation_zmatrix(double alphaz)
{
    double angle;
    matrix4f matrix;

    angle = deg_to_rad(alphaz);

    matrix.data[0][0] = +cos(angle);
    matrix.data[0][1] = +sin(angle);
    matrix.data[0][2] = 0;
    matrix.data[0][3] = 0;

    matrix.data[1][0] = -sin(angle);
    matrix.data[1][1] = +cos(angle);
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 0;

    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 1;
    matrix.data[2][3] = 0;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 1;

    return  matrix;
}

