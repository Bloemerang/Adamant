#ifndef NodeRegistryUtils_H__
#define NodeRegistryUtils_H__
/**
 * @file
 * @brief Contains the macros used to hide the implementation of the node
 *        registry.
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include <FlexiUtil\DebugDefs.h>

#define NODE_TYPE_REGISTRY_BEGIN                                \
namespace flexi {                                               \
namespace graphics {                                            \
namespace internal {                                            \
template <typename Visitor>                                     \
Visitor& applyVisitor(Visitor& visitor, Node& node) {           \
    const auto& id = typeid(node);                              \
    if (false) {}

#define REGISTER(node_type)                                     \
    else if (id == typeid(node_type))                           \
        visitor.visit(reinterpret_cast<node_type&>(node));

#define NODE_TYPE_REGISTRY_END                                  \
    else flexiAssertM(false, "Encountered a node type not present in NodeTypeRegistry.h during scenegraph traversal"); \
    return visitor;                                             \
}}}}

#endif // NodeRegistryUtils_H__