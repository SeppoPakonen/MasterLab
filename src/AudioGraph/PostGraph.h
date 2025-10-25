#pragma once
#include "BusWithInternalGraph.h"
namespace am {
// Ozone-like mastering topology lives here
struct PostGraph : BusWithInternalGraph {
    // helpers to build band-split chains, parallel/serial routes, etc.
    void BuildDefault();
};
}