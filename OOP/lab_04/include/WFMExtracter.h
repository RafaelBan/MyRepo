#ifndef WFM_EXTRACTER_H_
#define WFM_EXTRACTER_H_

#include "WFMReaderBase.h"

#include "WFMIterator.h"
#include "WireFrameModel.h"

class WFMExtracter : public WFMReaderBase
{
public:
    explicit WFMExtracter(WireFrameModel *model);
    ~WFMExtracter() = default;

    void setModel(WireFrameModel *model);

    void rewind() override;

    int readVerticesQuan() override;
    int readEdgesQuan() override;

    Point3d readVertex() override;
    Container<Point3d> readVertices() override;

    Pair<int, int> readEdge() override;
    Container< Pair<int, int> > readEdges() override;

    bool isAvailableVertices() override;
    bool isAvailableEdges() override;

private:
    WFMConstIterator vertexIt;
    WFMConstEdgeIterator edgeIt;

    WireFrameModel *model;
};

#endif // WFM_EXTRACTER_H_

