#ifndef _AudioGraph_SubgraphNode_h_
#define _AudioGraph_SubgraphNode_h_

// Note: Requires Node.h and Graph.h (from same package) - available via main header in .cpp files

namespace am {
	
struct Graph; // Forward declaration

struct SubgraphNode : Node {
    Ptr<Graph> sub; // owns a sub-graph
    bool IsContainer() const override { return true; }
};

}

#endif
