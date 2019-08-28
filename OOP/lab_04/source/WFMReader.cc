#include "WFMReader.h"

static inline int
_read_int(FILE *inputs)
{
    int rc;
    int number = 0;

    rc = fscanf(inputs, "%d", &number);

    if (rc != 1)
    {
        // EXCEPTION
    }

    return number;
}

static inline double
_read_double(FILE *inputs)
{
    int rc;
    double number = 0;

    rc = fscanf(inputs, "%lf", &number);

    if (rc != 1)
    {
        // EXECPTION
    }

    return number;
}

static inline bool
_is_external_stream(FILE *file_stream)
{
    return (file_stream != stdout) && (file_stream != stderr) && (file_stream != stdin);
}

WFMReader::WFMReader() :
    WFMReaderBase(),

    verticesQuan(-1), edgesQuan(-1),
    vertexIdx(0), edgeIdx(0)
{
    dataStream = stdout;
}

WFMReader::WFMReader(const char *fname) :
    WFMReaderBase(),

    verticesQuan(-1), edgesQuan(-1),
    vertexIdx(0), edgeIdx(0)

{
    dataStream = fopen(fname, "r");
}

WFMReader::~WFMReader()
{
    if (_is_external_stream(dataStream))
    {
        fclose(dataStream);
    }
}

void WFMReader::rewind()
{
    vertexIdx = 0;
    edgeIdx = 0;
    ::rewind(dataStream);
}

int WFMReader::readVerticesQuan()
{
    // try {
    verticesQuan = _read_int(dataStream);
    return verticesQuan;
    // }
    // catch {}
}

int WFMReader::readEdgesQuan()
{
    // try {
    edgesQuan =_read_int(dataStream);
    return edgesQuan;
    // }
    // catch {}
}

Point3d WFMReader::readVertex()
{
    if (!isAvailableVertices())
    {
        // EXCEPTION
    }

    double x, y, z;

    x = y = z = 0;

    // try {
    x = _read_double(dataStream);
    y = _read_double(dataStream);
    z = _read_double(dataStream);
    // }
    // catch {}

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
        // EXCEPTION
    }

    int idx1, idx2;

    idx1 = idx2 = 0;

    // try {
    idx1 = _read_int(dataStream);
    idx2 = _read_int(dataStream);
    // }
    // catch {}

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

