#include "ParameterSet.h"

namespace DSP {

ParameterSet::ParameterSet() : smoothing_ms(0.0) {
}

ParameterSet::~ParameterSet() {
}

void ParameterSet::RegisterParameter(const ParameterId& param) {
    parameters.GetAdd(param.name) = param;
    values.GetAdd(param.name) = param.default_value;
}

void ParameterSet::SetValue(const Upp::String& name, double value) {
    if (values.Find(name) >= 0) {
        double min_val = parameters.Get(name).min_value;
        double max_val = parameters.Get(name).max_value;
        values.GetAdd(name) = max(min_val, min(max_val, value)); // Clamp between min/max
    }
}

double ParameterSet::GetValue(const Upp::String& name) const {
    int idx = values.Find(name);
    if (idx >= 0) {
        return values[idx];
    }
    return 0.0; // Default value if not found
}

void ParameterSet::ApplySmoothing(double milliseconds) {
    smoothing_ms = milliseconds;
    // In a real implementation, this would set up parameter smoothing
    // using various interpolation techniques
}

const ParameterId* ParameterSet::GetParameter(const Upp::String& name) const {
    int idx = parameters.Find(name);
    if (idx >= 0) {
        return &parameters[idx];
    }
    return nullptr;
}

}