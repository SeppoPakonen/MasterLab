#pragma once
#include "AudioTypes.h"
namespace am {
struct Clip; // fwd (defined in Clip.h)
struct EffectChain; // fwd (in AudioFX)
struct Channel {
    Vector<Clip> clips;
    double gain_db = 0.0;
    double pan = 0.0; // -1..+1
    EffectChain* fx = nullptr; // owned elsewhere or by channel, TBD
};
}
namespace am {
struct EffectChain; // fwd (in AudioFX)
struct Channel {
    Vector<Clip> clips;
    double gain_db = 0.0;
    double pan = 0.0; // -1..+1
    EffectChain* fx = nullptr; // owned elsewhere or by channel, TBD
};
}