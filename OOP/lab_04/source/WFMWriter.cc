#include "WFMWriter.h"

#include "IOBase.h"
#include "IO.h"

WFMWriter::WFMWriter()
{
    reset();
}

WFMWriter::WFMWriter(IOBase *outputs)
{
    reset(outputs);
}

WFMWriter::~WFMWriter()
{
}

void WFMWriter::reset()
{
    outputs = &OUTPUTS;
}

void WFMWriter::reset(IOBase *outputs)
{
    this->outputs = outputs;
}

void WFMWriter::setSizes(int verticesQuan, int edgesQuan)
{
    *outputs << verticesQuan << " " << edgesQuan << "\n";
}

void WFMWriter::addVertex(const Point3d &point)
{
    *outputs << point.X() << " " << point.Y() << " " << point.Z() << "\n";
}

void WFMWriter::addVertices(const Container<Point3d> &points)
{
    for (Point3d point: points)
    {
        addVertex(point);
    }
}

void WFMWriter::addEdge(const Pair<> &edge)
{
    *outputs << edge.first << " " << edge.second << "\n";
}

void WFMWriter::addEdges(const Container< Pair<> > &edges)
{
    for (Pair<> edge: edges)
    {
        addEdge(edge);
    }
}

