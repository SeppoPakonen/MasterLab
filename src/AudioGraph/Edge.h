#pragma once
#include "Port.h"
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