#ifndef _AudioFX_LatencyBuffer_h_
#define _AudioFX_LatencyBuffer_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "SignalBus.h"

using namespace Upp;

namespace DSP {

using Sample = double;
using AudioBuffer = Vector<Sample>;

// Latency buffer for handling processing delays
class LatencyBuffer {
public:
    LatencyBuffer();
    explicit LatencyBuffer(int maxDelaySamples);
    
    // Set the delay amount in samples
    void SetDelay(int samples);
    
    // Get the current delay amount
    int GetDelay() const { return delaySamples; }
    
    // Process a sample with the specified delay
    Sample Process(Sample input);
    
    // Process an audio buffer
    void ProcessBuffer(const AudioBuffer& input, AudioBuffer& output);
    
    // Get latency in samples
    int GetLatency() const { return delaySamples; }
    
private:
    int maxDelay;
    int delaySamples;
    Vector<Sample> delayLine;
    int writeIndex;
};

} // namespace DSP

#endif