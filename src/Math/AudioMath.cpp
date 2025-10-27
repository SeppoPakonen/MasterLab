#include "AudioMath.h"
#include <math.h>

namespace Upp {
    
    double GainToDb(double gain) {
        if (gain <= 0.0) return -std::numeric_limits<double>::infinity();
        return 20.0 * log10(gain);
    }
    
    double DbToGain(double db) {
        return pow(10.0, db / 20.0);
    }
    
    template<typename T>
    T clamp(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    double lerp(double a, double b, double t) {
        return a + (b - a) * clamp(t, 0.0, 1.0);
    }
    
    double MidiNoteToFreq(int note) {
        return 440.0 * pow(2.0, (note - 69) / 12.0);
    }
    
    double FreqToMidiNote(double freq) {
        if (freq <= 0.0) return 0;
        return 69 + 12 * log2(freq / 440.0);
    }
    
    double CalculateRMS(const double* samples, int count) {
        if (count <= 0) return 0.0;
        double sum = 0.0;
        for (int i = 0; i < count; i++) {
            sum += samples[i] * samples[i];
        }
        return sqrt(sum / count);
    }
    
    double CalculatePeak(const double* samples, int count) {
        if (count <= 0) return 0.0;
        double peak = 0.0;
        for (int i = 0; i < count; i++) {
            double abs_sample = fabs(samples[i]);
            if (abs_sample > peak) {
                peak = abs_sample;
            }
        }
        return peak;
    }

    // Explicit instantiation for common types
    template int clamp<int>(int value, int min, int max);
    template double clamp<double>(double value, double min, double max);
    template float clamp<float>(float value, float min, float max);
}