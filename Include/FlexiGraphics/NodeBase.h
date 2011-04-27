#ifndef NodeBase_H__
#define NodeBase_H__
/**
 * @file
 * @brief 
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "FlexiUtil\DebugDefs.h"
#include "FlexiGraphics\NodeTypes.h"

class NodeBase
{
    NodeBase& operator=(const NodeBase&);
protected:
    const unsigned nodeType;
    NodeBase* sibling;
    friend class Leaf;

public:
    NodeBase() : nodeType(LEAF), sibling(0) {}
    NodeBase(NodeTypes t) : nodeType(t), sibling(0) {}
    virtual ~NodeBase() {}

    template<typename V>
    V& accept(V& visitor) {
        switch (this->nodeType) {
        case LEAF: visitor.visitNodeBase(*this);                        break;
        case INNER:  visitor.visitLeaf(reinterpret_cast<Leaf&>(*this)); break;
        default: flexiAssertM(false, "Unexpected node type in NodeBase::accept");
        }
        return visitor;
    }
};

#endif // NodeBase_H__