#ifndef _AudioCore_AudioBuffer_h_
#define _AudioCore_AudioBuffer_h_

// Note: Requires AudioCore/AudioCore.h (for Sample, SampleRate) - included via main header in .cpp files

namespace am {
struct AudioBuffer {
    SampleRate rate = 48000;
    int channels = 2;
    Vector<Vector<Sample>> data; // data[c][n]
    void Resize(int ch, int frames);
    int GetFrames() const;
    int GetChannels() const { return channels; }
};
}

#endif