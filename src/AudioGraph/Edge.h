#ifndef _AudioGraph_Edge_h_
#define _AudioGraph_Edge_h_

// Note: Requires Port.h (from same package) - available via main header in .cpp files

namespace am {
struct Node; // fwd
struct Edge {
    Node* from = nullptr;
    int   from_port = 0;
    Node* to = nullptr;
    int   to_port = 0;
    MultiChannelLayout layout;
};
}

#endif
namespace am {
struct Node; // fwd
struct Edge {
    Node* from = nullptr;
    int   from_port = 0;
    Node* to = nullptr;
    int   to_port = 0;
    MultiChannelLayout layout;
};
}
namespace am {
struct Node; // fwd
struct Edge {
    Node* from = nullptr;
    int   from_port = 0;
    Node* to = nullptr;
    int   to_port = 0;
    MultiChannelLayout layout;
};
}