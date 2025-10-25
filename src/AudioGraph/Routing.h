#ifndef _AudioGraph_Routing_h_
#define _AudioGraph_Routing_h_

// Note: Requires AudioCore/AudioCore.h and Graph.h - included via main header in .cpp files

namespace am {
struct Routing {
    // placeholder for graph execution (toposort etc.)
    void Process(Graph& g, AudioBuffer& io);
};
}

#endif
namespace am {
struct Routing {
    // placeholder for graph execution (toposort etc.)
    void Process(Graph& g, AudioBuffer& io);
};
}