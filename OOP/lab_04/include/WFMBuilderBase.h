#ifndef WFM_BUILDER_BASE_H_
#define WFM_BUILDER_BASE_H_

#include "Container.h"

#include "Point3d.h"
#include "Pair.h"
#include "WireFrameModel.h"

class WFMBuilderBase
{
public:
    explicit WFMBuilderBase() = default;
    virtual ~WFMBuilderBase() = default;

    virtual void reset() = 0;

    virtual void setSizes(int pointsQuan, int edgesQuan) = 0;

    virtual void addVertex(const Point3d &point) = 0;
    virtual void addVertices(const Container<Point3d> &points) = 0;

    virtual void addEdge(const Pair<> &edge) = 0;
    virtual void addEdges(const Container< Pair<> > &edges) = 0;
};

#endif // WFM_BUILDER_BASE_H_

