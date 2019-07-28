#include "object.h"

Object object_create()
{
    return { .pointsq = 0,
             .points = NULL,
             .edgesq = 0,
             .nodes_1 = NULL,
             .nodes_2 = NULL };
}

void object_delete(Object &object)
{
    free(object.points);
    free(object.nodes_1);
    free(object.nodes_2);

    object = object_create();
}

bool object_is_null(const Object &object)
{
    if (object.edgesq == 0 ||
        object.pointsq == 0 ||
        object.points == NULL ||
        object.nodes_1 == NULL ||
        object.nodes_2 == NULL)
    {
        return true;
    }

    return  false;
}

int object_read(Object &object, IO stream)
{
    int temp;
    int rc = __EXIT_SUCCESS;

    size_t edgesq;
    size_t pointsq;

    size_t *nodes_1 = NULL;
    size_t *nodes_2 = NULL;

    point3d_t *points = NULL;

    rc = io_read_i(stream, &temp);
    pointsq = size_t(temp);

    if (rc == __EXIT_SUCCESS)
    {
        rc = io_read_i(stream, &temp);
        edgesq = size_t(temp);
    }

    if ((rc == __EXIT_SUCCESS) && (pointsq == 0 || edgesq == 0))
    {
        rc = __EXIT_READ_ERR;
    }

    if (rc == __EXIT_SUCCESS)
    {
        nodes_1 = (size_t *)malloc(edgesq * sizeof(size_t));
    }

    if (nodes_1 != NULL)
    {
        nodes_2 = (size_t *)malloc(edgesq * sizeof(size_t));
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_MEM_ERR;
    }

    if (nodes_2 != NULL)
    {
        points = (point3d_t *)malloc(edgesq * sizeof(point3d_t));
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_MEM_ERR;

        free(nodes_1);
    }

    if (points != NULL)
    {
        object.pointsq = pointsq;
        object.points = points;

        object.edgesq = edgesq;
        object.nodes_1 = nodes_1;
        object.nodes_2 = nodes_2;

        for (size_t i = 0; i < pointsq && rc == __EXIT_SUCCESS; i++)
        {
            double x, y, z;

            if (rc == __EXIT_SUCCESS)
            {
                rc = io_read_d(stream, &x);
            }

            if (rc == __EXIT_SUCCESS)
            {
                rc = io_read_d(stream, &y);
            }

            if (rc == __EXIT_SUCCESS)
            {
                rc = io_read_d(stream, &z);
            }

            if (rc == __EXIT_SUCCESS)
            {
                object.points[i] = {x, y, z};
            }
        }

        for (size_t i = 0; i < edgesq && rc == __EXIT_SUCCESS; i++)
        {
            int ind1, ind2;

            if (rc == __EXIT_SUCCESS)
            {
                rc = io_read_i(stream, &ind1);
            }

            if (rc == __EXIT_SUCCESS)
            {
                rc = io_read_i(stream, &ind2);
            }

            if (rc == __EXIT_SUCCESS)
            {
                object.nodes_1[i] = ind1;
                object.nodes_2[i] = ind2;
            }
        }

    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_MEM_ERR;

        free(nodes_1);
        free(nodes_2);
    }
    return rc;
}

int object_write(const Object &object, IO stream)
{
    int rc = __EXIT_SUCCESS;

    rc = io_write_i(stream, int(object.pointsq));

    if (rc == __EXIT_SUCCESS)
    {
        io_put_space(stream);

        io_write_i(stream, int(object.edgesq));
        io_put_linebreak(stream);
        io_put_linebreak(stream);

        for (size_t i = 0; i < object.pointsq; i++)
        {
            io_write_d(stream, object_point(object, i).x);
            io_put_space(stream);

            io_write_d(stream, object_point(object, i).y);
            io_put_space(stream);

            io_write_d(stream, object_point(object, i).z);
            io_put_linebreak(stream);
        }
        io_put_linebreak(stream);

        for (size_t i = 0; i < object.edgesq; i++)
        {
            io_write_i(stream, int(object.nodes_1[i]));
            io_put_space(stream);

            io_write_i(stream, int(object.nodes_2[i]));
            io_put_linebreak(stream);
        }
        io_put_linebreak(stream);
    }

    return  rc;
}

int object_project(point2d_t **points, size_t &pointsq, const Object &object, double zoffset)
{
    int rc = __EXIT_SUCCESS;

    point2d_t *temp_points;

    temp_points = (point2d_t *) malloc(object.edgesq * 2 * sizeof(point2d_t));

    if (temp_points != NULL)
    {
        matrix4f projection = projection_matrix(1e-3, 1e+3, 1.0, 60.0);

        free(*points);
        *points = temp_points;

        pointsq = object.edgesq * 2;

        for (size_t i = 0, j = 1; i < object.edgesq; i++, j += 2)
        {
            point3d_t first = object_point(object, object.nodes_1[i]);
            point3d_t second = object_point(object, object.nodes_2[i]);

            first.z -= zoffset;
            second.z -= zoffset;

            points[0][j - 1] = point3d_project(first, projection);
            points[0][j + 0] = point3d_project(second, projection);
        }
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_MEM_ERR;
    }

    return rc;
}

int object_translate(Object &object, double dx, double dy, double dz)
{
    matrix4f tmatrix = translate_matrix(dx, dy, dz);

    return object_process(object, tmatrix);
}

int object_scale(Object &object, double kx, double ky, double kz)
{
    matrix4f smatrix = scaling_matrix(kx, ky, kz);

    return object_process(object, smatrix);
}

int object_rotate(Object &object, double alphax, double alphay, double alphaz)
{
    int rc;

    matrix4f xmatrix = rotation_xmatrix(alphax);
    matrix4f ymatrix = rotation_ymatrix(alphay);
    matrix4f zmatrix = rotation_zmatrix(alphaz);

    rc = object_process(object, xmatrix);

    if (rc == __EXIT_SUCCESS)
    {
        rc = object_process(object, ymatrix);
    }

    if (rc == __EXIT_SUCCESS)
    {
        rc = object_process(object, zmatrix);
    }

    return rc;
}

int object_process(Object &object, matrix4f matrix)
{
    int rc = __EXIT_SUCCESS;

    if (object_is_null(object))
    {
        rc = __EXIT_NULL_OBJECT;
    }
    else
    {
        for (size_t i = 0; i < object.pointsq; i++)
        {
            vector4f processed;
            vector4f projective = point3d_to_projective(object_point(object, i));

            processed = mult_matrix_vector4f(matrix, projective);

            object_set_point(object, i, { .x = processed.data[0] / processed.data[3],
                                          .y = processed.data[1] / processed.data[3],
                                          .z = processed.data[2] / processed.data[3] });
        }
    }

    return rc;
}

point3d_t object_point(const Object &object, size_t i)
{
    return object.points[i];
}

void object_set_point(const Object &object, size_t i, point3d_t point)
{
    object.points[i] = point;
}
