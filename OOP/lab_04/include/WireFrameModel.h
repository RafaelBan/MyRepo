#ifndef WIRE_FRAME_MODEL_H_
#define WIRE_FRAME_MODEL_H_

#include <Container.h>

#include "Point3d.h"
#include "Edge3d.h"

class WireFrameModel
{
public:
    void addVertex(const Point3d &point);

    void addEdge(int idx1, int idx2);
    void addEdge(const Point3d *v1, const Point3d *v2);

private:
    Container<Point3d> vertices;
    Container<Edge3d> edges;
};

#endif // WIRE_FRAME_MODEL_H_

