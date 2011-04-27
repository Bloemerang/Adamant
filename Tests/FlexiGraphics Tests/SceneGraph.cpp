/**
 * @file
 * @brief Integration tests for the scene graph.
 * @author   Steven Bloemer
 * @date     4/17/2011
 * @lastedit 4/17/2011
 */
#include "FlexiGraphics\Node.h"
#include "FlexiGraphics\InnerNode.h"
#include "FlexiGraphics\Visit.h"
#include "FlexiGraphics\Spatial.h"
#include "FlexiGraphics\VNode.h"
#include "FlexiGraphics\Visitor.h"
#include "FlexiGraphics\NodeBase.h"
#include "FlexiGraphics\Leaf.h"
#include "FlexiUtil\Timer.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;
using namespace flexi::graphics;
using namespace flexi::util;


////////////////////////////////////////////////////////////////////////////////
// Visitors

class ScenePrinter
{
    const unsigned tabsize;
    unsigned depth;

    ScenePrinter& operator=(const ScenePrinter&);

public:
    ScenePrinter(unsigned tabsize) : tabsize(tabsize), depth(0) {}

    void visit(Node&) {
        cout << string(depth, ' ') << "Node" << endl;
    }

    void visit(InnerNode& innerNode) {
        cout << string(depth, ' ') << "InnerNode" << endl;

        depth += tabsize;
        Visit::children(innerNode, *this);
        depth -= tabsize;
    }
};

struct NodeCounter
{
    unsigned nodeCount;

    NodeCounter() : nodeCount(0) {}

    void visit(Node&) {
        ++nodeCount;
    }

    void visit(InnerNode& in) {
        ++nodeCount;
        Visit::children(in, *this);
    }
};

struct VNodeCounter: public Visitor
{
    unsigned nodeCount;

    VNodeCounter() : nodeCount(0) {}

    virtual void visitSpatial(Spatial&) { ++nodeCount; }
    virtual void visitNode(VNode& vn) {
        ++nodeCount;
        vn.visitChildren(*this);
    }
};

struct EnumNodeCounter
{
    unsigned nodeCount;

    EnumNodeCounter() : nodeCount(0) {}

    void visitNodeBase(NodeBase& nb) {++nodeCount;}
    void visitLeaf(Leaf& leaf) {
        ++nodeCount;
        leaf.visitChildren(*this);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Test templates

template <typename N, typename L>
N& buildTree(unsigned depth, unsigned breadth) {
    N& root = *new N();
    if (depth)
        for (unsigned i = 0; i < breadth; ++i)
            root.addChild(buildTree<N,L>(depth-1, breadth));
    else
        root.addChild(*new L()).addChild(*new L());

    return root;
}

template <typename Counter, typename N, typename L, typename RunFxn>
void runTest(RunFxn run_it) {
    L& root = buildTree<N,L>(22,2);

    Counter counter;
    Timer timer;

    timer.start();
    run_it(root, counter);
    timer.stop();

    delete &root;

    printf("Counted %d nodes in %.2f seconds\n", counter.nodeCount, timer.getLastSeconds());
}


//---------------------------------------------------------------------------
// MAIN METHOD:
//---------------------------------------------------------------------------
void main()
{
    cout << "Testing with InnerNode/Node" << endl;
    runTest<NodeCounter,InnerNode,Node>([](Node& n, NodeCounter& c) {
        Visit::node(n,c);
    });

    cout << "Testing with VNode/Spatial" << endl;
    runTest<VNodeCounter,VNode,Spatial>([](Spatial& sp, VNodeCounter& vc) {
        sp.accept(vc);
    });

    cout << "Testing with NodeBase/Leaf" << endl;
    runTest<EnumNodeCounter,Leaf,NodeBase>([](NodeBase& nb, EnumNodeCounter& ec) {
        nb.accept(ec);
    });

    cout << "\nEnter a character to exit";
    std::string s;
    std::cin >> s;
}