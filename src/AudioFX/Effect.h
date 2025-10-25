#ifndef _AudioFX_Effect_h_
#define _AudioFX_Effect_h_

// Note: Requires AudioCore/AudioCore.h (for SampleRate, AudioBuffer) - included via main header in .cpp files

namespace am {
struct Effect : Pte<Effect> {
    virtual ~Effect() {}
    virtual void Prepare(SampleRate sr, int maxBlock) {}
    virtual void Process(AudioBuffer& io) = 0;
    virtual String Name() const = 0;
};
}

#endif
