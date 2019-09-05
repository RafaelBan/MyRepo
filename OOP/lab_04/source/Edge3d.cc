#include <Edge3d.h>

Edge3d::Edge3d(std::weak_ptr<Point3d> v1, std::weak_ptr<Point3d> v2)
{
    vertex1Ptr = v1;
    vertex2Ptr = v2;
}

Point3d Edge3d::getVertex1()
{
    return *vertex1Ptr.lock();
}

Point3d Edge3d::getVertex2()
{
    return *vertex2Ptr.lock();
}

