#ifndef _AudioFX_Splitter_h_
#define _AudioFX_Splitter_h_

// Note: Requires AudioCore/AudioCore.h and Effect.h - included via main header in .cpp files

namespace am {
struct Splitter : Effect {
    int outputs = 2;
    void Process(AudioBuffer& io) override; // no-op placeholder
    Upp::String Name() const override { return "Splitter"; }
};
}

#endif