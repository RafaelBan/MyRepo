#ifndef WFM_READER_H_
#define WFM_READER_H_

#include <cstdio>

#include "Pair.h"
#include "Point3d.h"
#include "WFMReaderBase.h"

class WFMReader : public WFMReaderBase
{
public:
    explicit WFMReader();
    explicit WFMReader(const char *fname);
    ~WFMReader() override;

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
    int vertexIdx;
    int verticesQuan;

    int edgeIdx;
    int edgesQuan;

    FILE *dataStream;
};

#endif // WFM_READER_H_

