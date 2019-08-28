#ifndef WFM_BUILDER_BASE_H_
#define WFM_BUILDER_BASE_H_

#include "Container.h"

#include "Point3d.h"
#include "Edge3d.h"
#include "WireFrameModel.h"

class WFMBuilderBase
{
public:
    void reset();

    void setSizes(int pointsQuan, int edgesQuan);

    void addVertex(const Point3d &point);
    void addVertices(const Container<Point3d> &points);

    void addEdge(const Edge3d &edge);
    void addEdges(const Container<Edge3d> &edges);
};

#endif // WFM_BUILDER_BASE_H_

