#pragma once
#include "Node.h"
#include "Graph.h"
namespace am {
struct SubgraphNode : Node {
    Ptr<Graph> sub; // owns a sub-graph
    bool IsContainer() const override { return true; }
};
}