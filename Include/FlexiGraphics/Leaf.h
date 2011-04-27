#ifndef Leaf_H__
#define Leaf_H__
/**
 * @file
 * @brief 
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "FlexiGraphics\NodeBase.h"

class Leaf: public NodeBase
{
    NodeBase* child;

public:
    Leaf() : NodeBase(INNER), child(0) {}
    ~Leaf() {
        NodeBase* child = this->child;
        while (child) {
            NodeBase* next = child->sibling;
            delete child;
            child = next;
        }
    }

    Leaf& addChild(NodeBase& child) {
        flexiAssert(!child.sibling);

        child.sibling = this->child;
        this->child = &child;
        return *this;
    }

    template <typename V>
    void visitChildren(V& visitor) {
        NodeBase* child = this->child;
        while (child) {
            child->accept(visitor);
            child = child->sibling;
        }
    }
};

#endif // Leaf_H__