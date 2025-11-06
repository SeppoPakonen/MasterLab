#ifndef _Math_FFT_h_
#define _Math_FFT_h_

#include <Core/Core.h>
#include <math.h>

using namespace Upp;

namespace Upp {
    // Fast Fourier Transform functions
    
    // In-place complex FFT
    // Length must be a power of 2
    void FFT(Vector<Complex>& data, bool inverse = false);
    
    // Real FFT - transforms real input to complex output (positive frequencies only)
    Vector<Complex> RealFFT(const Vector<double>& real_data);
    
    // Inverse Real FFT - transforms complex input back to real
    Vector<double> InverseRealFFT(const Vector<Complex>& complex_data);
}

#endif