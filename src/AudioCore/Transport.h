#pragma once
#include "AudioTypes.h"
namespace am {
struct Transport {
    bool playing = false;
    FrameIndex playhead = 0;
    void Play(); void Stop(); void Seek(FrameIndex f);
};
}