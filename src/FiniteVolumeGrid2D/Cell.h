#ifndef CELL_H
#define CELL_H

#include <vector>

#include "Types.h"

#include "Node.h"
#include "Face.h"
#include "Link.h"

class Cell
{
public:

    enum {NO_NEIGHBOUR = -1, INACTIVE = -1};

    Cell(const std::vector<size_t>& faceIds, std::vector<Face>& faces);

    Scalar volume() const { return volume_; }
    const Point2D& centroid() const { return centroid_; }

    size_t id() const { return id_; }
    int globalIndex() const { return globalIndex_; }

    const std::vector< Ref<const Face> >& faces() const { return faces_; }
    const std::vector<InteriorLink>& neighbours() const { return interiorLinks_; }
    const std::vector<BoundaryLink>& boundaries() const { return boundaryLinks_; }

    size_t nFaces() const { return faces_.size(); }
    size_t nInteriorFaces() const { return interiorLinks_.size(); }
    size_t nBoundaryFaces() const { return boundaryLinks_.size(); }
    size_t nNeighbours() const { return interiorLinks_.size(); }

private:

    void computeCellAdjacency();

    Scalar volume_;
    Point2D centroid_;

    size_t id_;
    int globalIndex_;

    std::vector< Ref<const Face> > faces_;

    std::vector<InteriorLink> interiorLinks_;
    std::vector<BoundaryLink> boundaryLinks_;



    friend class FiniteVolumeGrid2D;
};

#endif