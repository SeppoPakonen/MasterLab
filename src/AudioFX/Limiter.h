#pragma once
#include "Effect.h"
namespace am {
struct Limiter : Effect {
    double ceiling_db = -1.0;
    void Process(AudioBuffer& io) override;
    String Name() const override { return "Limiter"; }
};
}