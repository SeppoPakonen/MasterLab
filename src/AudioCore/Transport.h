#ifndef _AudioCore_Transport_h_
#define _AudioCore_Transport_h_

// Note: Requires AudioCore/AudioCore.h (for FrameIndex) - included via main header in .cpp files

namespace am {
struct Transport {
    bool playing = false;
    FrameIndex playhead = 0;
    void Play(); void Stop(); void Seek(FrameIndex f);
};
}

#endif