#include "WFMBuilder.h"

WFMBuilder::WFMBuilder() :
    isSizesLimited(false),
    verticesQuan(0),
    edgesQuan(0)
{
}

std::shared_ptr<WireFrameModel> WFMBuilder::get()
{
    return model;
}

void WFMBuilder::reset()
{
    isSizesLimited = false;
    verticesQuan = 0;
    edgesQuan = 0;

    model = std::make_shared<WireFrameModel>();
}

void WFMBuilder::setSizes(int verticesQuan, int edgesQuan)
{
    this->verticesQuan = verticesQuan;
    this->edgesQuan = edgesQuan;

    isSizesLimited = true;
}

void WFMBuilder::addVertex(const Point3d &point)
{
    if (model->verticesQuantity() >= size_t(verticesQuan))
    {
        // EXCEPTION
    }

    model->addVertex(point);
}

void WFMBuilder::addVertices(const Container<Point3d> &points)
{
    for (Point3d point: points)
    {
        addVertex(point);
    }
}

void WFMBuilder::addEdge(const Pair<> &edge)
{
    if (model->edgesQuantity() >= size_t(edgesQuan))
    {
        // EXCEPTION
    }

    model->addEdge(edge.first, edge.second);
}

void WFMBuilder::addEdges(const Container< Pair<> > &edges)
{
    for (Pair<> edge: edges)
    {
        addEdge(edge);
    }
}

