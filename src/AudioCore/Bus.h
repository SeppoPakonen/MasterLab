#ifndef _AudioCore_Bus_h_
#define _AudioCore_Bus_h_

namespace am {
struct EffectChain; // fwd (in AudioFX)
struct Bus {
    String name = "Master";
    EffectChain* fx = nullptr; // master/bus effect chain
};
// Forward decl for specialized bus with internal routing graph (see AudioGraph)
struct BusWithInternalGraph;
}

#endif