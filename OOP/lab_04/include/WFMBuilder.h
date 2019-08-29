#ifndef WFM_BUILDER_H
#define WFM_BUILDER_H

#include <memory>

#include "Pair.h"
#include "WFMBuilderBase.h"
#include "WireFrameModel.h"

class WFMBuilder : public WFMBuilderBase
{
public:
    WFMBuilder();
    ~WFMBuilder() = default;

    void reset() override;

    void setSizes(int verticesQuan, int edgesQuan) override;

    void addVertex(const Point3d &point) override;
    void addVertices(const Container<Point3d> &points) override;

    void addEdge(const Pair<> &edge) override;
    void addEdges(const Container< Pair<> > &edges) override;

    std::shared_ptr<WireFrameModel> get();

private:
    bool isSizesLimited;
    int verticesQuan;
    int edgesQuan;

    std::shared_ptr<WireFrameModel> model;
};

#endif // WFM_BUILDER_H

