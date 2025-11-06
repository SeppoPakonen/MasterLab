#ifndef _AudioFX_GainNormalization_h_
#define _AudioFX_GainNormalization_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <AudioFX/DSP.h>

using namespace Upp;

namespace am {
namespace DSP {

// GainStage - applies gain with various options
class GainStage {
public:
    enum GainMode {
        LINEAR,
        LOGARITHMIC,
        DECIBELS
    };
    
    GainStage();
    ~GainStage();
    
    void Process(const double* input, double* output, int sample_count, double sample_rate);
    void SetGain(double gain_db);  // Input in dB
    double GetGain() const { return gain; }
    void SetMode(GainMode mode);
    void SetAutoGain(bool enabled);
    
    void SetParameter(const String& name, double value);
    double GetParameter(const String& name) const;
    
    // Get current gain applied
    double GetCurrentGain() const { return current_gain; }
    
private:
    double gain;  // In dB
    GainMode mode;
    bool auto_gain;
    double current_gain;  // Current gain applied
    VectorMap<String, double> parameters;
};

// NormalizationStage - normalizes audio to a target level
class NormalizationStage {
public:
    NormalizationStage();
    ~NormalizationStage();
    
    void Process(const double* input, double* output, int sample_count, double sample_rate);
    void SetTargetLevel(double level_db);  // Target in dBFS
    double GetTargetLevel() const { return target_level; }
    void SetLookahead(int samples);  // Lookahead in samples
    void SetSoftKnee(bool enabled);  // Use soft knee for limiting
    
    void SetParameter(const String& name, double value);
    double GetParameter(const String& name) const;
    
private:
    double target_level;  // In dBFS
    int lookahead_samples;
    bool soft_knee;
    double current_peak;
    Vector<double> lookahead_buffer;
    int buffer_pos;
    VectorMap<String, double> parameters;
};

// AdaptiveGainControl - automatically adjusts gain based on content
class AdaptiveGainControl {
public:
    AdaptiveGainControl();
    ~AdaptiveGainControl();
    
    void Process(const double* input, double* output, int sample_count, double sample_rate);
    void SetTargetRMS(double target_rms);
    void SetAttackTime(double ms);
    void SetReleaseTime(double ms);
    void SetHoldTime(double ms);
    
    void SetParameter(const String& name, double value);
    double GetParameter(const String& name) const;
    
private:
    double target_rms;
    double attack_coeff;
    double release_coeff;
    double hold_time_samples;
    double current_gain;
    int hold_counter;
    VectorMap<String, double> parameters;
    
    void UpdateCoefficients(double sample_rate);
};

}
}

#endif