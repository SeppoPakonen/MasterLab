#ifndef _AudioGraph_PostGraph_h_
#define _AudioGraph_PostGraph_h_

// Note: Requires BusWithInternalGraph.h - available via main header in .cpp files

namespace am {
	
// Ozone-like mastering topology lives here
struct PostGraph : BusWithInternalGraph {
    // helpers to build band-split chains, parallel/serial routes, etc.
    void BuildDefault();
};

}

#endif
