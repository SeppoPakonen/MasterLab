#ifndef _DSP_ParameterSet_h_
#define _DSP_ParameterSet_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

struct ParameterId {
    String name;
    String description;
    double min_value;
    double max_value;
    double default_value;
    
    ParameterId(const String& n, const String& desc, double min, double max, double def)
        : name(n), description(desc), min_value(min), max_value(max), default_value(def) {}
};

class ParameterSet {
public:
    typedef ParameterSet CLASSNAME;
    
    ParameterSet();
    virtual ~ParameterSet();
    
    // Register automatable parameters
    void RegisterParameter(const ParameterId& param);
    
    // Set/get parameter values
    void SetValue(const String& name, double value);
    double GetValue(const String& name) const;
    
    // Apply smoothing to parameters
    void ApplySmoothing(double milliseconds);
    
    // Get parameter descriptor
    const ParameterId* GetParameter(const String& name) const;
    
private:
    VectorMap<String, ParameterId> parameters;
    VectorMap<String, double> values;
    double smoothing_ms;
};

}

#endif