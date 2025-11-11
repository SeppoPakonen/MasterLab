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
    Upp::Vector<Complex> fft_buffer;
    int fft_size;
};

}

#endif