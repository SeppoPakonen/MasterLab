#ifndef _AudioCore_Channel_h_
#define _AudioCore_Channel_h_

namespace am {
	
struct Clip; // Forward declaration - full type provided by main header
struct EffectChain; // fwd (in AudioFX)
struct Channel {
    Upp::Vector<Clip> clips;
    double gain_db = 0.0;
    double pan = 0.0; // -1..+1
    EffectChain* fx = nullptr; // owned elsewhere or by channel, TBD
};

}

#endif
