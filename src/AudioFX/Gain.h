#ifndef _AudioFX_Gain_h_
#define _AudioFX_Gain_h_

// Note: Requires AudioCore/AudioCore.h (for AudioBuffer) - included via main header in .cpp files

namespace am {
struct Gain : Effect {
    double gain_db = 0.0;
    void Process(AudioBuffer& io) override;
    Upp::String Name() const override { return "Gain"; }
};
}

#endif