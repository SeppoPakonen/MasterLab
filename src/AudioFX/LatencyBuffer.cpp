#include "LatencyBuffer.h"

namespace AudioFX {

LatencyBuffer::LatencyBuffer() : maxDelay(0), delaySamples(0), writeIndex(0) {
    // Default constructor
}

LatencyBuffer::LatencyBuffer(int maxDelaySamples) :
    maxDelay(maxDelaySamples), delaySamples(0), writeIndex(0) {
    delayLine.SetCount(maxDelay);
    for (int i = 0; i < maxDelay; i++) {
        delayLine[i] = 0.0;
    }
}

void LatencyBuffer::SetDelay(int samples) {
    delaySamples = max(0, min(samples, maxDelay));
}

Sample LatencyBuffer::Process(Sample input) {
    // Write input to delay line at current write index
    delayLine[writeIndex] = input;

    // Calculate read index (with wraparound)
    int readIndex = writeIndex - delaySamples;
    if (readIndex < 0) {
        readIndex += maxDelay;
    }

    // Update write index
    writeIndex = (writeIndex + 1) % maxDelay;

    // Return delayed sample
    return delayLine[readIndex];
}

void LatencyBuffer::ProcessBuffer(const AudioBuffer& input, AudioBuffer& output) {
    int size = input.GetCount();
    output.SetCount(size);

    for (int i = 0; i < size; i++) {
        output[i] = Process(input[i]);
    }
}

} // namespace AudioFX