#pragma once
#include "AudioTypes.h"
#include "Channel.h"
#include "Bus.h"
namespace am {
struct Mixer {
    Vector<Channel*> channels;
    Bus* master = nullptr;
    // simple pan-law and mix placeholder API
    void MixBlock(AudioBuffer& out);
};
}