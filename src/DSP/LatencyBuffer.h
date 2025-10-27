#ifndef _DSP_LatencyBuffer_h_
#define _DSP_LatencyBuffer_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

class LatencyBuffer {
public:
    typedef LatencyBuffer CLASSNAME;
    
    LatencyBuffer();
    virtual ~LatencyBuffer();
    
    // Configure lookahead buffer
    void Configure(int lookahead_samples);
    
    // Process input/output with lookahead delay applied
    void Process(const BufferView& input, BufferView& output);
    
    // Get the configured latency
    int GetLatency() const { return latency_samples; }
    
    // Clear the buffer
    void Clear();
    
private:
    int latency_samples;
    BufferView buffer;
    int write_pos;
    int read_pos;
};

}

#endif