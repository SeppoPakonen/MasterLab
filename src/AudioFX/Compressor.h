#ifndef _AudioFX_Compressor_h_
#define _AudioFX_Compressor_h_

// Note: Requires AudioCore/AudioCore.h (for AudioBuffer) - included via main header in .cpp files

namespace am {
struct Compressor : Effect {
    double threshold_db = -12, ratio = 4.0, attack_ms = 10, release_ms = 80;
    void Process(AudioBuffer& io) override;
    Upp::String Name() const override { return "Compressor"; }
};
}

#endif