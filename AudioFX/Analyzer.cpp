#include "Analyzer.h"

namespace DSP {

Analyzer::Analyzer() : rmsValue(0.0), peakValue(0.0), currentFrequency(0.0) {
    // Initialize analyzer state
}

ValueMap Analyzer::Analyze(const AudioBuffer& buffer) {
    ValueMap result;
    
    // Calculate RMS
    double sum = 0.0;
    double peak = 0.0;
    for (Sample sample : buffer) {
        sum += sample * sample;
        if (abs(sample) > peak) peak = abs(sample);
    }
    rmsValue = sqrt(sum / buffer.GetCount());
    peakValue = peak;
    
    // Store results in value map
    result.Set("rms", rmsValue);
    result.Set("peak", peakValue);
    result.Set("frequency", currentFrequency);
    
    return result;
}

ValueMap Analyzer::GetRealTimeAnalysis() {
    ValueMap result;
    result.Set("rms", rmsValue);
    result.Set("peak", peakValue);
    result.Set("frequency", currentFrequency);
    return result;
}

void Analyzer::Reset() {
    rmsValue = 0.0;
    peakValue = 0.0;
    currentFrequency = 0.0;
    spectrum.Clear();
}

} // namespace DSP