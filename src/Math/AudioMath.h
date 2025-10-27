#ifndef _Math_AudioMath_h_
#define _Math_AudioMath_h_

#include <Core/Core.h>

namespace Upp {
    
    // Convert gain to decibels
    double GainToDb(double gain);
    
    // Convert decibels to gain
    double DbToGain(double db);
    
    // Clamp a value between min and max
    template<typename T>
    T clamp(T value, T min, T max);
    
    // Linear interpolation between two values
    double lerp(double a, double b, double t);
    
    // Convert MIDI note number to frequency in Hz
    double MidiNoteToFreq(int note);
    
    // Convert frequency in Hz to MIDI note number
    double FreqToMidiNote(double freq);
    
    // Calculate RMS (Root Mean Square) of audio samples
    double CalculateRMS(const double* samples, int count);
    
    // Calculate peak level of audio samples
    double CalculatePeak(const double* samples, int count);
}

#endif