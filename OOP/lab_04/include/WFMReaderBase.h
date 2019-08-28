#ifndef WFM_READER_BASE_H_
#define WFM_READER_BASE_H_

#include "Container.h"

#include "Point3d.h"
#include "Pair.h"

class WFMReaderBase
{
public:
    explicit WFMReaderBase() = default;
    virtual ~WFMReaderBase() = default;

    virtual void rewind() = 0;

    virtual int readVerticesQuan() = 0;
    virtual int readEdgesQuan() = 0;

    virtual Point3d readVertex() = 0;
    virtual Container<Point3d> readVertices() = 0;

    virtual Pair<int, int> readEdge() = 0;
    virtual Container< Pair<int, int> > readEdges() = 0;

    virtual bool isAvailableVertices() = 0;
    virtual bool isAvailableEdges() = 0;
};

#endif // WFM_READER_BASE_H_

