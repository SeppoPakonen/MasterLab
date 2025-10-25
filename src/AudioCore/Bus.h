#pragma once
#include "AudioTypes.h"
namespace am {
struct EffectChain;
struct Bus {
    String name = "Master";
    EffectChain* fx = nullptr; // master/bus effect chain
};
// Forward decl for specialized bus with internal routing graph (see AudioGraph)
struct BusWithInternalGraph;
}