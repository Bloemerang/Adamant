#ifndef VNode_H__
#define VNode_H__
/**
 * @file
 * @brief Header for VNode class.
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "FlexiUtil\DebugDefs.h"
#include "Spatial.h"

class VNode: public Spatial
{
    Spatial* child;

public:
    VNode() : child(0) {}
    virtual ~VNode() {
        Spatial* child = this->child;
        while (child) {
            Spatial* next = child->sibling;
            delete child;
            child = next;
        }
    }

    VNode& addChild(Spatial& child) {
        flexiAssert(!child.sibling);

        child.sibling = this->child;
        this->child = &child;
        return *this;
    }

    virtual Visitor& accept(Visitor& visitor) {
        visitor.visitNode(*this);
        return visitor;
    }

    void visitChildren(Visitor& visitor) {
        Spatial* child = this->child;
        while (child) {
            child->accept(visitor);
            child = child->sibling;
        }
    }
};

#endif // VNode_H__