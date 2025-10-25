#pragma once
#include "Effect.h"
namespace am {
struct Crossover : Effect {
    // splits into N bands; routing handled by graph layer
    Vector<double> split_freqs;
    void Process(AudioBuffer& io) override; // no-op placeholder
    String Name() const override { return "Crossover"; }
};
}