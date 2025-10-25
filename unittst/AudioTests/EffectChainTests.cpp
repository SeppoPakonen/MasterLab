#include <Core/Core.h>
#include "../src/AudioFX/AudioFX.h"
#include "../src/AudioCore/AudioCore.h"

CONSOLE_APP_MAIN {
    using namespace Upp;
    using namespace am;
    
    EffectChain chain;
    
    Gain* gain = new Gain();
    gain->gain_db = -3.0;
    chain.Add(gain);
    
    Limiter* limiter = new Limiter();
    limiter->ceiling_db = -1.0;
    chain.Add(limiter);
    
    // Create a dummy buffer
    AudioBuffer buffer;
    buffer.Resize(2, 48000); // Stereo, 1 second at 48kHz
    
    // Run the chain
    chain.Process(buffer);
    
    LOG("Effect chain test completed successfully");
}