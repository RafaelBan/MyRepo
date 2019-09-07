#include "WFMReader.h"

#include "WFMExceptions.h"

static inline int
_read_int(IOBase *inputs)
{
    int number = 0;

    *inputs >> number;

    if (!inputs->isValid())
    {
        throw WFMReadException("Can not read int. ");
    }

    return number;
}

static inline double
_read_double(IOBase *inputs)
{
    double number = 0;

    *inputs >> number;

    if (!inputs->isValid())
    {
        throw WFMReadException("Can not read double. ");
    }

    return number;
}

WFMReader::WFMReader() :
    WFMReaderBase(),

    vertexIdx(0), verticesQuan(-1),
    edgeIdx(0), edgesQuan(-1)
{
}

WFMReader::WFMReader(IOBase *inputs) :
    WFMReader()
{
    setInputStream(inputs);
}

WFMReader::~WFMReader()
{
}

void WFMReader::setInputStream(IOBase *inputs)
{
    this->inputs = inputs;
}

int WFMReader::readVerticesQuan()
{
    try
    {
        verticesQuan = _read_int(inputs);
        return verticesQuan;
    }
    catch (WFMReadException e)
    {
        throw WFMReadException((std::string("At readVerticesQuan. ") + e.what()).c_str());
    }

    return 0;
}

int WFMReader::readEdgesQuan()
{
    try
    {
        edgesQuan =_read_int(inputs);
        return edgesQuan;
    }
    catch (WFMReadException e)
    {
        throw WFMReadException((std::string("At readEdgesQuan. ") + e.what()).c_str());
    }

    return 0;
}

Point3d WFMReader::readVertex()
{
    if (!isAvailableVertices())
    {
        throw WFMReadException("At readEdge. No available vertices to read. ");
    }

    double x, y, z;

    x = y = z = 0;

    try
    {
        x = _read_double(inputs);
        y = _read_double(inputs);
        z = _read_double(inputs);
    }
    catch (WFMReadException e)
    {
        throw WFMReadException((std::string("At readVertex. ") + e.what()).c_str());
    }

    vertexIdx++;
    return { x, y, z };
}

Container<Point3d> WFMReader::readVertices()
{
    Container<Point3d> vertices;

    do
    {
        vertices.append(readVertex());
    }
    while (isAvailableVertices());

    return vertices;
}

Pair<int, int> WFMReader::readEdge()
{
    if (!isAvailableEdges())
    {
        throw WFMReadException("At readEdge. No available edges to read. ");
    }

    int idx1, idx2;

    idx1 = idx2 = 0;

    try
    {
        idx1 = _read_int(inputs);
        idx2 = _read_int(inputs);
    }
    catch (WFMReadException e)
    {
        throw WFMReadException((std::string("At readEdge. ") + e.what()).c_str());
    }

    edgeIdx++;
    return { idx1, idx2 };
}

Container< Pair<int, int> > WFMReader::readEdges()
{
    Container< Pair<int, int> > edges;

    do
    {
        edges.append(readEdge());
    }
    while (isAvailableEdges());

    return edges;
}

bool WFMReader::isAvailableVertices()
{
    return (verticesQuan > 0) && (vertexIdx < verticesQuan);
}

bool WFMReader::isAvailableEdges()
{
    return (edgesQuan >= 0) && (edgeIdx < edgesQuan);
}

