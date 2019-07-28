#ifndef LINE_H
#define LINE_H

#include "point3d.h"

struct Line3d
{
private:
    Point3d _first;
    Point3d _second;

public:
    Line3d();
    Line3d(double x1, double y1, double z1, double x2, double y2, double z2);
    Line3d(Point3d first, Point3d second);

    Point3d first();
    Point3d second();

    void setFirst(Point3d point);
    void setSecond(Point3d point);
};

#endif // LINE_H
