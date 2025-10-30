#ifndef _DSP_SignalBus_h_
#define _DSP_SignalBus_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

class SignalBus {
public:
    typedef SignalBus CLASSNAME;
    
    SignalBus();
    virtual ~SignalBus();
    
    // Multi-channel audio frame management
    BufferView AcquireBlock(int frames);
    
    // Sample-accurate routing with latency accounting
    bool Route(const BusLayout& src, const BusLayout& dst);
    
    // Get/set bus layout
    BusLayout GetLayout() const { return layout; }
    void SetLayout(const BusLayout& bus_layout) { layout = bus_layout; }
    
    // Latency management
    int GetLatency() const { return latency; }
    void SetLatency(int samples) { latency = samples; }
    
private:
    BusLayout layout;
    int latency;
    Upp::Vector<BufferView> channels;
};

}

#endif