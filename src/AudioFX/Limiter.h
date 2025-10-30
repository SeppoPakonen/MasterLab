#ifndef _AudioFX_Limiter_h_
#define _AudioFX_Limiter_h_

// Note: Requires AudioCore/AudioCore.h (for AudioBuffer) - included via main header in .cpp files

namespace am {
struct Limiter : Effect {
    double ceiling_db = -1.0;
    void Process(AudioBuffer& io) override;
    Upp::String Name() const override { return "Limiter"; }
};
}

#endif