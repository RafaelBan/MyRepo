#ifndef WIRE_FRAME_MODEL_H_
#define WIRE_FRAME_MODEL_H_

#include <Container.h>

#include "Point3d.h"
#include "Edge3d.h"

class WireFrameModel
{
public:

private:
    Container<Point3d> vertices;
    Container<Edge3d> edges;
};

#endif // WIRE_FRAME_MODEL_H_

