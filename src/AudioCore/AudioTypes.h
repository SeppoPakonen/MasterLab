#ifndef _AudioCore_AudioTypes_h_
#define _AudioCore_AudioTypes_h_

#include <Core/Core.h>

namespace am {
    using Sample = float;
    using SampleRate = int;
    using FrameIndex = int64;      // timeline frame index
    struct ChannelSet {
        // bitmask of channels (L=1<<0, R=1<<1, C=1<<2, ...)
        uint64 mask = 0;
        static ChannelSet Stereo();
        static ChannelSet Mono();
    };
}

#endif