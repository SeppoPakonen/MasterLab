#ifndef _AudioFX_EffectChain_h_
#define _AudioFX_EffectChain_h_

// Note: Requires AudioCore/AudioCore.h (for AudioBuffer) - included via main header in .cpp files

namespace am {
struct Effect; // Forward declaration for same-package type
struct EffectChain {
    Vector< Ptr<Effect> > effects; // U++ Ptr smart ptr
    void Add(Effect* e) { effects.Add(e); }
    void Process(AudioBuffer& io) {
        for(auto& e : effects) if(e) e->Process(io);
    }
};
}

#endif