#ifndef Spatial_H__
#define Spatial_H__
/**
 * @file
 * @brief Header for Spatial class.
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "Visitor.h"

class Spatial
{
public:
    Spatial() : sibling(0) {}
    virtual ~Spatial() {}

    virtual Visitor& accept(Visitor& visitor) {
        visitor.visitSpatial(*this);
        return visitor;
    }
protected:
    friend class VNode;
    Spatial* sibling;
};

#endif // Spatial_H__