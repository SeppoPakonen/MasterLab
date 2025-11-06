#include "FFT.h"
#include <math.h>

namespace Upp {
    
    // Bit-reversal permutation for FFT
    static int BitReverse(int x, int bits) {
        int y = 0;
        for (int i = 0; i < bits; i++) {
            y = (y << 1) | (x & 1);
            x >>= 1;
        }
        return y;
    }
    
    // In-place complex FFT
    void FFT(Vector<Complex>& data, bool inverse) {
        int n = data.GetCount();
        if (n < 2) return;
        
        // Check if n is a power of 2
        if ((n & (n - 1)) != 0) {
            // Not a power of 2 - pad with zeros
            int new_n = 1;
            while (new_n < n) new_n <<= 1;
            data.SetCount(new_n);
            for (int i = n; i < new_n; i++) {
                data[i] = Complex(0.0, 0.0);
            }
            n = new_n;
        }
        
        // Calculate number of bits needed
        int bits = 0;
        int temp = n;
        while (temp > 1) {
            temp >>= 1;
            bits++;
        }
        
        // Bit-reversal permutation
        for (int i = 0; i < n; i++) {
            int j = BitReverse(i, bits);
            if (j > i) {
                Swap(data[i], data[j]);
            }
        }
        
        // Cooley-Tukey FFT
        for (int len = 2; len <= n; len <<= 1) {
            double angle = 2.0 * M_PI / len;
            if (inverse) angle = -angle;
            Complex wlen = Complex(cos(angle), sin(angle));
            
            for (int i = 0; i < n; i += len) {
                Complex w = Complex(1.0, 0.0);
                for (int j = 0; j < len / 2; j++) {
                    Complex u = data[i + j];
                    Complex v = data[i + j + len / 2] * w;
                    data[i + j] = u + v;
                    data[i + j + len / 2] = u - v;
                    w = w * wlen;
                }
            }
        }
        
        if (inverse) {
            for (int i = 0; i < n; i++) {
                data[i] = data[i] / n;
            }
        }
    }
    
    // Real FFT - transforms real input to complex output (positive frequencies only)
    Vector<Complex> RealFFT(const Vector<double>& real_data) {
        int n = real_data.GetCount();
        Vector<Complex> complex_data(n);
        
        // Convert real data to complex
        for (int i = 0; i < n; i++) {
            complex_data[i] = Complex(real_data[i], 0.0);
        }
        
        // Perform FFT
        FFT(complex_data, false);
        
        // Only return first half (positive frequencies)
        Vector<Complex> result(n/2 + 1);
        for (int i = 0; i <= n/2; i++) {
            result[i] = complex_data[i];
        }
        
        return result;
    }
    
    // Inverse Real FFT - transforms complex input back to real
    Vector<double> InverseRealFFT(const Vector<Complex>& complex_data) {
        int n = complex_data.GetCount();
        int full_n = (n - 1) * 2;  // Full size before taking half
        
        Vector<Complex> full_data(full_n);
        
        // Reconstruct full spectrum from half (assuming conjugate symmetry)
        for (int i = 0; i < n; i++) {
            full_data[i] = complex_data[i];
        }
        for (int i = n; i < full_n; i++) {
            full_data[i] = conj(complex_data[full_n - i]);
        }
        
        // Perform inverse FFT
        FFT(full_data, true);
        
        // Extract real part
        Vector<double> result(full_n);
        for (int i = 0; i < full_n; i++) {
            result[i] = real(full_data[i]);
        }
        
        return result;
    }
}