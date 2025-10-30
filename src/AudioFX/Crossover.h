#ifndef _AudioFX_Crossover_h_
#define _AudioFX_Crossover_h_

// Note: Requires AudioCore/AudioCore.h and Effect.h - included via main header in .cpp files

namespace am {
struct Crossover : Effect {
    // splits into N bands; routing handled by graph layer
    Upp::Vector<double> split_freqs;
    void Process(AudioBuffer& io) override; // no-op placeholder
    Upp::String Name() const override { return "Crossover"; }
};
}

#endif