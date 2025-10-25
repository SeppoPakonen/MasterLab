#ifndef _AudioGraph_BusWithInternalGraph_h_
#define _AudioGraph_BusWithInternalGraph_h_

// Note: Requires AudioCore/AudioCore.h and Graph.h - included via main header in .cpp files

namespace am {
struct BusWithInternalGraph : am::Bus {
    Graph graph; // internal routing for post/mastering etc.
};
}

#endif