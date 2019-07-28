#ifndef POINT3D_H
#define POINT3D_H


struct Point3d
{
private:
    double _x;
    double _y;
    double _z;

public:
    Point3d(double x = 0, double y = 0, double z = 0);

    double x();
    double y();
    double z();

    void setX(double x);
    void setY(double y);
    void setZ(double z);
};

#endif // POINT3D_H
