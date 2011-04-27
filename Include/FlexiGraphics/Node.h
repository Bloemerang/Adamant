#ifndef Node_H__
#define Node_H__
/**
 * @file
 * @brief Node Template
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */

namespace flexi {
namespace graphics {

class Node
{
public:
    Node() : sibling(0) {}

    virtual ~Node() {};
protected:
    friend struct Visit;
    friend class InnerNode;
    Node* sibling;
}; // class Node

} // namespace graphics
} // namespace flexi

#endif // Node_H__