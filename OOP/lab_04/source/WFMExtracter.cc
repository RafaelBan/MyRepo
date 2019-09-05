#include "WFMExtracter.h"

WFMExtracter::WFMExtracter(WireFrameModel *model)
{
    setModel(model);
}

void WFMExtracter::setModel(WireFrameModel *model)
{
    this->model = model;
    rewind();
}

void WFMExtracter::rewind()
{
    vertexIt = model->cbegin();
    edgeIt = model->getConstEdges().cbegin();
}

int WFMExtracter::readVerticesQuan()
{
    return int(model->verticesQuantity());
}

int WFMExtracter::readEdgesQuan()
{
    return int(model->edgesQuantity());
}

Point3d WFMExtracter::readVertex()
{
    if (!isAvailableVertices())
    {
        // EXCEPTION
    }

    return **(vertexIt++);
}

Container<Point3d> WFMExtracter::readVertices()
{
    Container<Point3d> vertices;

    do
    {
        vertices.append(readVertex());
    }
    while (isAvailableVertices());

    return vertices;
}

Pair<int, int> WFMExtracter::readEdge()
{
    if (!isAvailableEdges())
    {
        // EXCEPTION
    }

    Point3d v1 = (*edgeIt)->getVertex1();
    Point3d v2 = (*edgeIt)->getVertex2();
    edgeIt++;

    return { model->indexOf(v1), model->indexOf(v2) };
}

Container< Pair<int, int> > WFMExtracter::readEdges()
{
    Container< Pair<int, int> > edges;

    do
    {
        edges.append(readEdge());
    }
    while (isAvailableEdges());

    return edges;
}

bool WFMExtracter::isAvailableVertices()
{
    return vertexIt != model->end();
}

bool WFMExtracter::isAvailableEdges()
{
    return edgeIt != model->getConstEdges().end();
}

