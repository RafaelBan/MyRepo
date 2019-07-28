#include "point3d.h"

Point3d::Point3d(double x, double y, double z) :
    _x(x), _y(y), _z(z)
{
}

double Point3d::x()
{
    return  _x;
}

double Point3d::y()
{
    return  _y;
}

double Point3d::z()
{
    return  _z;
}

void Point3d::setX(double x)
{
    _x = x;
}

void Point3d::setY(double y)
{
    _y = y;
}

void Point3d::setZ(double z)
{
    _z = z;X
}
