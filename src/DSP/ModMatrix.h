#ifndef _DSP_ModMatrix_h_
#define _DSP_ModMatrix_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

class ModSource : public Moveable<ModSource> {
public:
    Upp::String name;
    double value;
    double min_value;
    double max_value;
    
    ModSource() : value(0.0), min_value(0.0), max_value(1.0) {}
    ModSource(const Upp::String& n, double min = 0.0, double max = 1.0) 
        : name(n), value(0.0), min_value(min), max_value(max) {}
};

class ModDestination : public Moveable<ModDestination> {
public:
    Upp::String name;
    double* target;
    double min_value;
    double max_value;
    
    ModDestination() : target(nullptr), min_value(0.0), max_value(1.0) {}
    ModDestination(const Upp::String& n, double* t, double min = 0.0, double max = 1.0)
        : name(n), target(t), min_value(min), max_value(max) {}
};

struct ModConnection : public Moveable<ModConnection> {
    Upp::String source;
    Upp::String destination;
    double depth;
    double offset;
    
    ModConnection(const Upp::String& src, const Upp::String& dst, double d = 1.0, double off = 0.0)
        : source(src), destination(dst), depth(d), offset(off) {}
};

class ModMatrix {
public:
    typedef ModMatrix CLASSNAME;
    
    ModMatrix();
    virtual ~ModMatrix();
    
    // Add modulation source
    void AddSource(const ModSource& source);
    
    // Add modulation destination
    void AddDestination(const ModDestination& destination);
    
    // Create a connection between source and destination
    void Connect(const Upp::String& source, const Upp::String& destination, double depth = 1.0, double offset = 0.0);
    
    // Compute all connections and produce modulation buffers
    void ComputeConnections();
    
    // Update source values
    void SetSourceValue(const Upp::String& source, double value);
    double GetSourceValue(const Upp::String& source) const;
    
private:
    VectorMap<Upp::String, ModSource> sources;
    VectorMap<Upp::String, ModDestination> destinations;
    Upp::Vector<ModConnection> connections;
};

}

#endif