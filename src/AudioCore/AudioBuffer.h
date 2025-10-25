#pragma once

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