#ifndef NodeTypeRegistry_H__
#define NodeTypeRegistry_H__
/**
 * @file
 * @brief Contains registration entries for each node type usable in the scene
 *        graph.
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "FlexiGraphics\NodeRegistryUtils.h"

// Include the headers for your node types here
#include "Node.h"
#include "InnerNode.h"
//

NODE_TYPE_REGISTRY_BEGIN
    REGISTER(Node)
    REGISTER(InnerNode)
NODE_TYPE_REGISTRY_END

#endif // NodeTypeRegistry_H__