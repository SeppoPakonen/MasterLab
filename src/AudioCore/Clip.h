#pragma once
#include "AudioTypes.h"
#include "IIdentified.h"
namespace am {
struct Clip : IIdentified {
    String filepath;
    FrameIndex start_frame = 0;   // position on timeline
    FrameIndex length_frames = 0; // duration
    // metadata & edit data placeholders
    struct Meta { String name; };
    Meta meta;
};
}