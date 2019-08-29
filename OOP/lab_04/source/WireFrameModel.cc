#include "WireFrameModel.h"

void WireFrameModel::addVertex(const Point3d &point)
{
    vertices.append(std::make_shared<Point3d>(point));
}

void WireFrameModel::addEdge(const Point3d &p1, const Point3d &p2)
{
    bool v1Found = false;
    bool v2Found = false;

    std::weak_ptr<Point3d> v1;
    std::weak_ptr<Point3d> v2;

    for (auto vertexPtr: vertices)
    {
        if (!v1Found && p1 == *vertexPtr)
        {
            v1 = vertexPtr;
            v1Found = true;
        }
        else if (!v2Found && p2 == *vertexPtr)
        {
            v2 = vertexPtr;
            v2Found = true;
        }
    }

    if (!v1Found || !v2Found)
    {
        // EXCEPTION
    }

    edges.append(std::make_shared<Edge3d>(v1, v2));
}

void WireFrameModel::addEdge(int idx1, int idx2)
{
    if (idx1 >= int(vertices.size()) || idx2 >= int(vertices.size()))
    {
        // EXCEPTION
    }

    if (idx1 < 0 || idx2 < 0)
    {
        // EXCEPTION
    }

    edges.append(std::make_shared<Edge3d>(vertices[idx1], vertices[idx2]));
}

size_t WireFrameModel::verticesQuantity()
{
    return vertices.size();
}

size_t WireFrameModel::edgesQuantity()
{
    return edges.size();
}

