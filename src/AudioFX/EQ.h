#ifndef _AudioFX_EQ_h_
#define _AudioFX_EQ_h_

// Note: Requires AudioCore/AudioCore.h (for AudioBuffer) - included via main header in .cpp files

namespace am {
struct EQ : Effect {
    // placeholder bands
    struct Band { double freq=1000, q=1.0, gain_db=0.0; };
    Vector<Band> bands;
    void Process(AudioBuffer& io) override;
    String Name() const override { return "EQ"; }
};
}

#endif