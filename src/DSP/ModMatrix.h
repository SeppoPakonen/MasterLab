#ifndef _DSP_ModMatrix_h_
#define _DSP_ModMatrix_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

class ModSource {
public:
    String name;
    double value;
    double min_value;
    double max_value;
    
    ModSource(const String& n, double min = 0.0, double max = 1.0) 
        : name(n), value(0.0), min_value(min), max_value(max) {}
};

class ModDestination {
public:
    String name;
    double* target;
    double min_value;
    double max_value;
    
    ModDestination(const String& n, double* t, double min = 0.0, double max = 1.0)
        : name(n), target(t), min_value(min), max_value(max) {}
};

struct ModConnection {
    String source;
    String destination;
    double depth;
    double offset;
    
    ModConnection(const String& src, const String& dst, double d = 1.0, double off = 0.0)
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
    void Connect(const String& source, const String& destination, double depth = 1.0, double offset = 0.0);
    
    // Compute all connections and produce modulation buffers
    void ComputeConnections();
    
    // Update source values
    void SetSourceValue(const String& source, double value);
    double GetSourceValue(const String& source) const;
    
private:
    VectorMap<String, ModSource> sources;
    VectorMap<String, ModDestination> destinations;
    Vector<ModConnection> connections;
};

}

#endif