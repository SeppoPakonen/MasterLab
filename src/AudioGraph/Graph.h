#pragma once
#include "Node.h"
#include "Edge.h"
namespace am {
struct Graph {
    Vector< Ptr<Node> > nodes;
    Vector<Edge> edges;
    // navigation helpers
    int AddNode(Node* n);
    void Connect(int fromNode, int fromPort, int toNode, int toPort, const MultiChannelLayout& mcl);
};
}