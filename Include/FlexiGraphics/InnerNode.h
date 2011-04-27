#ifndef InnerNode_H__
#define InnerNode_H__
/**
 * @file
 * @brief InnerNode template
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "FlexiUtil\DebugDefs.h"
#include "FlexiGraphics\Node.h"

namespace flexi {
namespace graphics {

class InnerNode: public Node
{
    friend struct Visit;
    Node* child;

public:
    InnerNode() : child(0) {}
    virtual ~InnerNode() {
        Node* child = this->child;
        while (child) {
            Node* next = child->sibling;
            delete child;
            child = next;
        }
    }

    InnerNode& addChild(Node& child) {
        flexiAssert(!child.sibling);

        child.sibling = this->child;
        this->child = &child;

        return *this;
    }
}; // class InnerNode

} // namespace graphics
} // namespace flexi

#endif // InnerNode_H__