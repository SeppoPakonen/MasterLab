#pragma once
#include "AudioTypes.h"
namespace am {
struct Channel; // fwd
struct Bus; // fwd
struct Mixer {
    Vector<Channel*> channels;
    Bus* master = nullptr;
    // simple pan-law and mix placeholder API
    void MixBlock(AudioBuffer& out);
};
}
namespace am {
struct Mixer {
    Vector<Channel*> channels;
    Bus* master = nullptr;
    // simple pan-law and mix placeholder API
    void MixBlock(AudioBuffer& out);
};
}