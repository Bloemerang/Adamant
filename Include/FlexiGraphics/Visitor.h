#ifndef Visitor_H__
#define Visitor_H__
/**
 * @file
 * @brief Visitor Interface
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
class Spatial;
class VNode;

struct Visitor
{
    virtual void visitSpatial(Spatial&) =0;
    virtual void visitNode(VNode&) =0;
};

#endif // Visitor_H__