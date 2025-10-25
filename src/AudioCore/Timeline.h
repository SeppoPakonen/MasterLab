#pragma once
#include "AudioTypes.h"
namespace am {
struct Timeline {
    FrameIndex length_frames = 0;
    void SetLength(FrameIndex f) { length_frames = f; }
};
}