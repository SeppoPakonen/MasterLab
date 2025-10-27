#include "LatencyBuffer.h"

namespace DSP {

LatencyBuffer::LatencyBuffer() : latency_samples(0), write_pos(0), read_pos(0) {
}

LatencyBuffer::~LatencyBuffer() {
}

void LatencyBuffer::Configure(int lookahead_samples) {
    latency_samples = lookahead_samples;
    if (latency_samples > 0) {
        buffer.SetCount(latency_samples);
        Clear();
    }
}

void LatencyBuffer::Process(const BufferView& input, BufferView& output) {
    if (latency_samples <= 0) {
        // No latency, pass through
        output = input;
        return;
    }
    
    // Resize output buffer if needed
    if (output.GetCount() < input.GetCount()) {
        output.SetCount(input.GetCount());
    }
    
    // Process with delay
    for (int i = 0; i < input.GetCount(); i++) {
        // Write input to buffer
        if (write_pos < buffer.GetCount()) {
            buffer[write_pos] = input[i];
        }
        
        // Read delayed output
        if (read_pos < buffer.GetCount()) {
            output[i] = buffer[read_pos];
        } else {
            output[i] = 0.0; // Zero if buffer not filled
        }
        
        // Update positions with wrapping
        write_pos = (write_pos + 1) % buffer.GetCount();
        read_pos = (read_pos + 1) % buffer.GetCount();
    }
}

void LatencyBuffer::Clear() {
    for (int i = 0; i < buffer.GetCount(); i++) {
        buffer[i] = 0.0;
    }
    write_pos = 0;
    read_pos = 0;
}

}