#ifndef Visit_H__
#define Visit_H__
/**
 * @file
 * @brief Defines the static Visit class.
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include <typeinfo>
#include "FlexiUtil\DebugDefs.h"
#include "FlexiGraphics\NodeTypeRegistry.h"

namespace flexi {
namespace graphics {

struct Visit {
    template <typename Visitor>
    static Visitor& node(Node& node, Visitor& visitor) {
        return internal::applyVisitor(visitor, node);
    }

    template <typename Visitor>
    static Visitor& children(InnerNode& innerNode, Visitor& visitor) {
        Node* child = innerNode.child;
        while (child) {
            Visit::node(*child, visitor);
            child = child->sibling;
        }
        return visitor;
    }
};

} // namespace graphics
} // namespace flexi


#endif // Visit_H__