#include "projection.h"

vector4f point3d_to_projective(const point3d_t &point)
{
    vector4f result;

    result.data[0] = point.x;
    result.data[1] = point.y;
    result.data[2] = point.z;
    result.data[3] = 1.0;

    return  result;
}

matrix4f projection_matrix(double znear, double zfar, double aspect_ratio, double field_of_view)
{
    matrix4f result;

    double tan_fov_half = tan(deg_to_rad(field_of_view) / 2);

    result.data[0][0] = 1.0 / tan_fov_half / aspect_ratio;
    result.data[0][1] = 0;
    result.data[0][2] = 0;
    result.data[0][3] = 0;

    result.data[1][0] = 0;
    result.data[1][1] = 1.0 / tan_fov_half;
    result.data[1][2] = 0;
    result.data[1][3] = 0;

    result.data[2][0] = 0;
    result.data[2][1] = 0;
    result.data[2][2] = (znear + zfar) / (znear - zfar) * -1.0;
    result.data[2][3] = (znear * zfar) / (znear - zfar) * +2.0;

    result.data[3][0] = 0;
    result.data[3][1] = 0;
    result.data[3][2] = 1.0;
    result.data[3][3] = 0;

    return result;
}

point2d_t point3d_project(point3d_t point, matrix4f projection)
{
    point2d_t result;
    vector4f projective;
    vector4f projected;

    projective = point3d_to_projective(point);
    projected = mult_matrix_vector4f(projection, projective);

    result.x = projected.data[0] / projected.data[2];
    result.y = projected.data[1] / projected.data[2];

    return  result;
}
