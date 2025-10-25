#pragma once
#include "Effect.h"
namespace am {
struct EffectChain {
    Vector< Ptr<Effect> > effects; // U++ Ptr smart ptr
    void Add(Effect* e) { effects.Add(e); }
    void Process(AudioBuffer& io) {
        for(auto& e : effects) if(e) e->Process(io);
    }
};
}