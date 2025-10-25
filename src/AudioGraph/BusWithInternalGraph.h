#pragma once
#include "../AudioCore/Bus.h"  // Only the specific header needed
#include "Graph.h"
namespace am {
struct BusWithInternalGraph : am::Bus {
    Graph graph; // internal routing for post/mastering etc.
};
}