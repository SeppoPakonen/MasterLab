#ifndef _AudioCore_Timeline_h_
#define _AudioCore_Timeline_h_

namespace am {
struct Timeline {
    FrameIndex length_frames = 0;
    void SetLength(FrameIndex f) { length_frames = f; }
};
}

#endif