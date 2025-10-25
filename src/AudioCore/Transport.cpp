#include "AudioCore.h"
namespace am {
void Transport::Play() { playing = true; }
void Transport::Stop() { playing = false; }
void Transport::Seek(FrameIndex f) { playhead = f; }
}