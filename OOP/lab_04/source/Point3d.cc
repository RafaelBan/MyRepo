#include "Point3d.h"

Point3d::Point3d(double x, double y, double z) :
    x(x), y(y), z(z)
{
}

double Point3d::X() const
{
    return x;
}

double Point3d::Y() const
{
    return y;
}

double Point3d::Z() const
{
    return z;
}

void Point3d::setX(double x)
{
    this->x = x;
}

void Point3d::setY(double y)
{
    this->y = y;
}

void Point3d::setZ(double z)
{
    this->z = z;
}

bool Point3d::operator==(const Point3d &another) const
{
    return isEval(X(), another.X()) && isEval(Y(), another.Y()) && isEval(Z(), another.Z());
}

