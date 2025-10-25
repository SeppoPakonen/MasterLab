#pragma once
#include "Effect.h"
namespace am {
struct Gain : Effect {
    double gain_db = 0.0;
    void Process(AudioBuffer& io) override;
    String Name() const override { return "Gain"; }
};
}