#ifndef _AudioFX_SignalBus_h_
#define _AudioFX_SignalBus_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h>  // For audio processing types

using namespace Upp;

namespace DSP {

using Sample = double;
using AudioBuffer = Vector<Sample>;

// Enum for signal bus types
enum class BusType {
    kAudio,
    kControl,
    kMIDI,
    kSidechain
};

// Signal bus for audio data transport
class SignalBus {
public:
    SignalBus();
    SignalBus(int channels, int maxFrames);
    
    void Resize(int channels, int frames);
    void Clear();
    
    // Access for reading/writing audio data
    Sample* GetChannel(int channel);
    const Sample* GetChannel(int channel) const;
    
    // Get/set number of channels and frames
    int GetChannelCount() const { return channelCount; }
    int GetFrameCount() const { return frameCount; }
    void SetFrameCount(int frames) { frameCount = min(frames, maxFrames); }
    
    // Process audio through this bus
    void ProcessAudio();
    
private:
    int channelCount;
    int frameCount;
    int maxFrames;
    Vector<AudioBuffer> buffers;  // One buffer per channel
};

} // namespace DSP

#endif