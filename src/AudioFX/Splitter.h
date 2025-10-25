#pragma once
#include "Effect.h"
namespace am {
struct Splitter : Effect {
    int outputs = 2;
    void Process(AudioBuffer& io) override; // no-op placeholder
    String Name() const override { return "Splitter"; }
};
}