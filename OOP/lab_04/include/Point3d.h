#ifndef POINT3D_H_
#define POINT3D_H_

#include <cmath>
#include "MathConstants.h"

class Point3d
{
public:
    Point3d(double x = 0, double y = 0, double z = 0);

    double X() const;
    double Y() const;
    double Z() const;

    void setX(double X);
    void setY(double Y);
    void setZ(double Z);

    bool operator==(const Point3d &another) const;

private:
    double x;
    double y;
    double z;
};

#endif // POINT3D_H_

