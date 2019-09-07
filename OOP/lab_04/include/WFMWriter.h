#ifndef WFM_WRITER_H_
#define WFM_WRITER_H_

#include "WFMBuilderBase.h"

class IOBase;

class WFMWriter : public WFMBuilderBase
{
public:
    WFMWriter();
    WFMWriter(IOBase *outputs);
    ~WFMWriter();

    void reset() override;
    void reset(IOBase *outputs);

    void setSizes(int verticesQuan, int edgesQuan) override;

    void addVertex(const Point3d &point) override;
    void addVertices(const Container<Point3d> &points) override;

    void addEdge(const Pair<> &edge) override;
    void addEdges(const Container< Pair<> > &edges) override;

private:
    IOBase *outputs;
};

#endif // WFM_WRITER_H_

