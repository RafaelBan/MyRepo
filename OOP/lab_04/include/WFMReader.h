#ifndef WFM_READER_H_
#define WFM_READER_H_

#include "IOBase.h"

#include "Pair.h"
#include "Point3d.h"
#include "WFMReaderBase.h"

class WFMReader : public WFMReaderBase
{
public:
    explicit WFMReader();
    explicit WFMReader(IOBase *inputs);
    ~WFMReader() override;

    void setInputStream(IOBase *inputs);

    int readVerticesQuan() override;
    int readEdgesQuan() override;

    Point3d readVertex() override;
    Container<Point3d> readVertices() override;

    Pair<int, int> readEdge() override;
    Container< Pair<int, int> > readEdges() override;

    bool isAvailableVertices() override;
    bool isAvailableEdges() override;

private:
    int vertexIdx;
    int verticesQuan;

    int edgeIdx;
    int edgesQuan;

    IOBase *inputs;
};

#endif // WFM_READER_H_

