#ifndef WFM_ITERATOR_H_
#define WFM_ITERATOR_H_

#include <memory>

#include "Container.h"
#include "Point3d.h"
#include "Edge3d.h"

using WFMIterator = typename Container< std::shared_ptr<Point3d> >::iterator;
using WFMConstIterator = typename Container< std::shared_ptr<Point3d> >::const_iterator;

using WFMEdgeIterator = typename Container< std::shared_ptr<Edge3d> >::iterator;
using WFMConstEdgeIterator = typename Container< std::shared_ptr<Edge3d> >::const_iterator;

#endif // WFM_ITERATOR_H_

