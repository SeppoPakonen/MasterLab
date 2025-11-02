#ifndef _AudioCore_AudioTypes_h_
#define _AudioCore_AudioTypes_h_


namespace am {
	
using Sample = float;
using SampleRate = int;
using FrameIndex = int64;      // timeline frame index

// Sample index within a clip
using SampleIndex = int64;

struct ChannelSet {
    // bitmask of channels (L=1<<0, R=1<<1, C=1<<2, ...)
    uint64 mask = 0;
    static ChannelSet Stereo();
    static ChannelSet Mono();
};

// FrameContext - context for audio processing operations
struct FrameContext {
	int sample_count = 0;
	double sample_rate = 44100.0;
	int64 position = 0;  // Position in timeline frames
	ValueMap metadata;   // Additional metadata if needed
	
	FrameContext() = default;
	FrameContext(int count, double rate, int64 pos) 
		: sample_count(count), sample_rate(rate), position(pos) {}
};

}

#endif
