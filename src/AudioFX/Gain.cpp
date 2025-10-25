#include "Gain.h"
namespace am {
void Gain::Process(AudioBuffer& io) {
    // Apply gain in dB to all channels
    double linear_gain = pow(10.0, gain_db / 20.0);
    for(int c = 0; c < io.GetChannels(); c++) {
        for(int s = 0; s < io.GetFrames(); s++) {
            io.data[c][s] *= linear_gain;
        }
    }
}
}