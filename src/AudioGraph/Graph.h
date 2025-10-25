#ifndef _AudioGraph_Graph_h_
#define _AudioGraph_Graph_h_

// Note: Requires Node.h and Edge.h (from same package) - available via main header in .cpp files

namespace am {
struct Graph {
    Vector< Ptr<Node> > nodes;
    Vector<Edge> edges;
    // navigation helpers
    int AddNode(Node* n);
    void Connect(int fromNode, int fromPort, int toNode, int toPort, const MultiChannelLayout& mcl);
};
}

#endif
namespace am {
struct Graph {
    Vector< Ptr<Node> > nodes;
    Vector<Edge> edges;
    // navigation helpers
    int AddNode(Node* n);
    void Connect(int fromNode, int fromPort, int toNode, int toPort, const MultiChannelLayout& mcl);
};
}