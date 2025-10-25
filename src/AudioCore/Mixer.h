#ifndef _AudioCore_Mixer_h_
#define _AudioCore_Mixer_h_

namespace am {
struct Channel; // Forward declaration - full type provided by main header
struct Bus; // Forward declaration - full type provided by main header
struct Mixer {
    Vector<Channel*> channels;
    Bus* master = nullptr;
    // simple pan-law and mix placeholder API
    void MixBlock(AudioBuffer& out);
};
}

#endif