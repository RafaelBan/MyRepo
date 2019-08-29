#ifndef EDGE3D_H_
#define EDGE3D_H_

#include <memory>

#include "Point3d.h"

class Edge3d
{
public:
    Edge3d(std::weak_ptr<Point3d> v1, std::weak_ptr<Point3d> v2);

private:
    std::weak_ptr<Point3d> vertex1Ptr;
    std::weak_ptr<Point3d> vertex2Ptr;
};

#endif // EDGE3D_H_

