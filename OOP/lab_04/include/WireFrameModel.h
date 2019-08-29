#ifndef WIRE_FRAME_MODEL_H_
#define WIRE_FRAME_MODEL_H_

#include <memory>
#include "Container.h"

#include "Point3d.h"
#include "Edge3d.h"

class WireFrameModel
{
public:
    void addVertex(const Point3d &point);

    void addEdge(int idx1, int idx2);
    void addEdge(const Point3d &p1, const Point3d &p2);

    size_t verticesQuantity();
    size_t edgesQuantity();

private:
    Container< std::shared_ptr<Point3d> > vertices;
    Container< std::shared_ptr<Edge3d> > edges;
};

#endif // WIRE_FRAME_MODEL_H_

