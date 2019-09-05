#ifndef WIRE_FRAME_MODEL_H_
#define WIRE_FRAME_MODEL_H_

#include <memory>
#include "Container.h"

#include "WFMIterator.h"

#include "Point3d.h"
#include "Edge3d.h"

class WireFrameModel
{
public:
    using iterator = WFMIterator;
    using const_iterator = WFMConstIterator;

    void addVertex(const Point3d &point);

    void addEdge(int idx1, int idx2);
    void addEdge(const Point3d &p1, const Point3d &p2);

    size_t verticesQuantity();
    size_t edgesQuantity();

    int indexOf(const Point3d &vertex);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    Container< std::shared_ptr<Edge3d> > &getEdges();
    const Container< std::shared_ptr<Edge3d> > &getEdges() const;
    const Container< std::shared_ptr<Edge3d> > &getConstEdges() const;

private:
    Container< std::shared_ptr<Point3d> > vertices;
    Container< std::shared_ptr<Edge3d> > edges;
};

#endif // WIRE_FRAME_MODEL_H_

