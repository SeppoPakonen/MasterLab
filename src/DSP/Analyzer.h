#ifndef _DSP_Analyzer_h_
#define _DSP_Analyzer_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

// Base class for various DSP analyzers
class Analyzer {
public:
    typedef Analyzer CLASSNAME;
    
    Analyzer();
    virtual ~Analyzer();
    
    // Process a block of audio data
    virtual void ProcessBlock(const BufferView& input) = 0;
    
    // Get analysis results
    virtual ValueMap GetResults() const = 0;
    
    // Reset the analyzer state
    virtual void Reset();
    
    // Configure analysis parameters
    virtual void Configure(const ValueMap& config);
    
protected:
    ValueMap configuration;
};

// Spectrum analyzer
class SpectrumAnalyzer : public Analyzer {
public:
    typedef SpectrumAnalyzer CLASSNAME;
    
    SpectrumAnalyzer();
    virtual ~SpectrumAnalyzer();
    
    virtual void ProcessBlock(const BufferView& input) override;
    virtual ValueMap GetResults() const override;
    
private:
    Vector<Complex> fft_buffer;
    int fft_size;
};

// LUFS meter for loudness measurement
class LUFSMeter : public Analyzer {
public:
    typedef LUFSMeter CLASSNAME;
    
    LUFSMeter();
    virtual ~LUFSMeter();
    
    virtual void ProcessBlock(const BufferView& input) override;
    virtual ValueMap GetResults() const override;
    
private:
    double integrated_loudness;
    double momentary_loudness;
    double short_term_loudness;
};

// ISP (Inter-sample Peak) detector
class ISPDetector : public Analyzer {
public:
    typedef ISPDetector CLASSNAME;
    
    ISPDetector();
    virtual ~ISPDetector();
    
    virtual void ProcessBlock(const BufferView& input) override;
    virtual ValueMap GetResults() const override;
    
private:
    double max_inter_sample_peak;
    double current_peak;
};

}

#endif