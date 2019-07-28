#include "management.h"
#include <QDebug>

int handle(Handler &handler, hcommand_t command)
{
    int rc = 0;
    static Object object = object_create();

    switch (command)
    {
    case DO_LOADING:
        rc = handle_load(object, handler);
        break;

    case DO_SAVING:
        rc = handle_save(object, handler);
        break;

    case DO_TRASNLATE:
        rc = handle_translate(object, handler);
        break;

    case DO_SCALING:
        rc = handle_scaling(object, handler);
        break;

    case DO_ROTATION:
        rc = handle_rotation(object, handler);
        break;

    case DO_RENDERING:
        rc = handle_render(object, handler);
        break;

    case DO_LEAVING:
        rc = handle_leave(object);
        break;

    default:
        qDebug() << "unknown command";
    }

    return rc;
}

int handle_load(Object &object, Handler &handler)
{
    int rc;
    IO stream;

    rc = io_open(stream, handler.filename, 'r');

    if (rc == __EXIT_SUCCESS)
    {
        rc = object_read(object, stream);
    }

    if (rc == __EXIT_SUCCESS)
    {
        rc = io_close(stream);
    }

    free(handler.filename);
    handler.filename = NULL;

    return rc;
}

int handle_save(Object &object, Handler &handler)
{
    int rc = __EXIT_SUCCESS;

    if (!object_is_null(object))
    {
        IO stream;

        rc = io_open(stream, handler.filename, 'w');

        if (rc == __EXIT_SUCCESS)
        {
            rc = object_write(object, stream);
        }

        if (rc == __EXIT_SUCCESS)
        {
            rc = io_close(stream);
        }
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_NULL_OBJECT;
    }

    free(handler.filename);
    handler.filename = NULL;

    return rc;
}

int handle_translate(Object &object, Handler &handler)
{
    int rc = __EXIT_SUCCESS;

    if (!object_is_null(object))
    {
        double dx = handler_read_translate(handler).dx;
        double dy = handler_read_translate(handler).dy;
        double dz = handler_read_translate(handler).dz;

        object_translate(object, dx, dy, dz);
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_NULL_OBJECT;;
    }

    return rc;
}

int handle_scaling(Object &object, Handler &handler)
{
    int rc = __EXIT_SUCCESS;

    if (!object_is_null(object))
    {
        double kx = handler_read_scaling(handler).kx;
        double ky = handler_read_scaling(handler).ky;
        double kz = handler_read_scaling(handler).kz;

        object_scale(object, kx, ky, kz);
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_NULL_OBJECT;;
    }

    return rc;
}

int handle_rotation(Object &object, Handler &handler)
{
    int rc = __EXIT_SUCCESS;

    if (!object_is_null(object))
    {
        double alphax = handler_read_rotation(handler).alphax;
        double alphay = handler_read_rotation(handler).alphay;
        double alphaz = handler_read_rotation(handler).alphaz;

        object_rotate(object, alphax, alphay, alphaz);
    }
    else if (rc == __EXIT_SUCCESS)
    {
        rc = __EXIT_NULL_OBJECT;
    }

    return rc;
}

int handle_render(Object &object, Handler &handler)
{
    int rc;

    rc = object_project(&handler.points, handler.pointsq, object, handler.cameraDistance);

    return rc;
}

int handle_leave(Object &object)
{
    object_delete(object);

    return __EXIT_SUCCESS;
}
