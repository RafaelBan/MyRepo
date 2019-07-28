#include "line3d.h"

Line3d::Line3d() :
    Line3d(0, 0, 0, 0, 0, 0)
{

}

Line3d::Line3d(double x1, double y1, double z1, double x2, double y2, double z2) :
    Line3d(Point3d(x1, y1, z1), Point3d(x2, y2, z2))
{

}

Line3d::Line3d(Point3d first, Point3d second) :
    _first(first), _second(second)
{

}

Point3d Line3d::first()
{
    return  _first;
}

Point3d Line3d::second()
{
    return  _second;
}

void Line3d::setFirst(Point3d point)
{
    _first = point;
}

void Line3d::setSecond(Point3d point)
{
    _second = point;
}
