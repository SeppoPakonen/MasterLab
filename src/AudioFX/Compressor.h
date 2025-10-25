#pragma once
#include "Effect.h"
namespace am {
struct Compressor : Effect {
    double threshold_db = -12, ratio = 4.0, attack_ms = 10, release_ms = 80;
    void Process(AudioBuffer& io) override;
    String Name() const override { return "Compressor"; }
};
}