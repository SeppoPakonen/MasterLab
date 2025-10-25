#pragma once
#include "../AudioCore/AudioBuffer.h"
#include "Graph.h"
namespace am {
struct Routing {
    // placeholder for graph execution (toposort etc.)
    void Process(Graph& g, AudioBuffer& io);
};
}