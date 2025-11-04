#ifndef _AudioFX_Analyzer_h_
#define _AudioFX_Analyzer_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "SignalBus.h"

using namespace Upp;

namespace DSP {

// Analyzer for processing and analyzing audio signals
class Analyzer {
public:
    Analyzer();
    
    // Analyze an audio buffer, returns analysis results
    ValueMap Analyze(const AudioBuffer& buffer);
    
    // Get real-time analysis results
    ValueMap GetRealTimeAnalysis();
    
    // Reset analysis state
    void Reset();
    
private:
    // Analysis data and state
    double rmsValue;
    double peakValue;
    double currentFrequency;
    Vector<double> spectrum;
};

} // namespace DSP

#endif