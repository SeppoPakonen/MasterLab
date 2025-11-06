#include "GainNormalization.h"

namespace am {
namespace DSP {

// GainStage implementation
GainStage::GainStage() : gain(0.0), mode(DECIBELS), auto_gain(false), current_gain(1.0) {
    parameters.Set("gain_db", 0.0);
    parameters.Set("mode", (int)DECIBELS);
    parameters.Set("auto_gain", 0.0);
}

GainStage::~GainStage() {
    // Clean up
}

void GainStage::Process(const double* input, double* output, int sample_count, double sample_rate) {
    // Update gain from parameters
    gain = parameters.Get("gain_db", 0.0);
    auto_gain = parameters.Get("auto_gain", 0.0) > 0.5;
    
    // Convert gain from dB to linear
    double linear_gain = pow(10.0, gain / 20.0);
    
    // Apply gain to the signal
    for (int i = 0; i < sample_count; i++) {
        output[i] = input[i] * linear_gain;
    }
    
    current_gain = linear_gain;
}

void GainStage::SetGain(double gain_db) {
    gain = gain_db;
    parameters.Set("gain_db", gain_db);
}

void GainStage::SetMode(GainMode mode) {
    this->mode = mode;
    parameters.Set("mode", (int)mode);
}

void GainStage::SetAutoGain(bool enabled) {
    auto_gain = enabled;
    parameters.Set("auto_gain", enabled ? 1.0 : 0.0);
}

void GainStage::SetParameter(const String& name, double value) {
    parameters.Set(name, value);
}

double GainStage::GetParameter(const String& name) const {
    return parameters.Get(name, 0.0);
}

// NormalizationStage implementation
NormalizationStage::NormalizationStage() : target_level(-1.0), lookahead_samples(0), 
                                          soft_knee(false), current_peak(0.0), buffer_pos(0) {
    parameters.Set("target_level", -1.0);
    parameters.Set("lookahead_samples", 0.0);
    parameters.Set("soft_knee", 0.0);
}

NormalizationStage::~NormalizationStage() {
    // Clean up
}

void NormalizationStage::Process(const double* input, double* output, int sample_count, double sample_rate) {
    // Update parameters
    target_level = parameters.Get("target_level", -1.0);
    lookahead_samples = (int)parameters.Get("lookahead_samples", 0.0);
    soft_knee = parameters.Get("soft_knee", 0.0) > 0.5;
    
    // Resize lookahead buffer if needed
    if (lookahead_buffer.GetCount() != lookahead_samples) {
        lookahead_buffer.SetCount(lookahead_samples);
        buffer_pos = 0;
    }
    
    double target_linear = pow(10.0, target_level / 20.0);
    
    // If no lookahead, process directly
    if (lookahead_samples <= 0) {
        // Find peak in the current block
        double peak = 0.0;
        for (int i = 0; i < sample_count; i++) {
            peak = max(peak, abs(input[i]));
        }
        
        // Calculate required gain
        double required_gain = (peak > 0.0) ? target_linear / peak : 1.0;
        
        // Apply gain
        for (int i = 0; i < sample_count; i++) {
            output[i] = input[i] * required_gain;
        }
    } else {
        // With lookahead, we would implement a more complex algorithm
        // This is a simplified version
        for (int i = 0; i < sample_count; i++) {
            // Add current input to lookahead buffer
            if (lookahead_samples > 0) {
                lookahead_buffer[buffer_pos] = input[i];
                buffer_pos = (buffer_pos + 1) % lookahead_samples;
            }
            
            // Output the delayed sample with applied gain
            output[i] = input[i] * target_linear; // Simplified - real implementation would be more complex
        }
    }
}

void NormalizationStage::SetTargetLevel(double level_db) {
    target_level = level_db;
    parameters.Set("target_level", level_db);
}

void NormalizationStage::SetLookahead(int samples) {
    lookahead_samples = samples;
    parameters.Set("lookahead_samples", (double)samples);
    if (samples > 0) {
        lookahead_buffer.SetCount(samples);
    }
}

void NormalizationStage::SetSoftKnee(bool enabled) {
    soft_knee = enabled;
    parameters.Set("soft_knee", enabled ? 1.0 : 0.0);
}

void NormalizationStage::SetParameter(const String& name, double value) {
    parameters.Set(name, value);
}

double NormalizationStage::GetParameter(const String& name) const {
    return parameters.Get(name, 0.0);
}

// AdaptiveGainControl implementation
AdaptiveGainControl::AdaptiveGainControl() : target_rms(0.1), attack_coeff(0.999), 
                                           release_coeff(0.99), hold_counter(0), current_gain(1.0) {
    parameters.Set("target_rms", 0.1);
    parameters.Set("attack_time_ms", 10.0);
    parameters.Set("release_time_ms", 100.0);
    parameters.Set("hold_time_ms", 0.0);
}

AdaptiveGainControl::~AdaptiveGainControl() {
    // Clean up
}

void AdaptiveGainControl::Process(const double* input, double* output, int sample_count, double sample_rate) {
    // Update parameters
    target_rms = parameters.Get("target_rms", 0.1);
    double attack_ms = parameters.Get("attack_time_ms", 10.0);
    double release_ms = parameters.Get("release_time_ms", 100.0);
    double hold_ms = parameters.Get("hold_time_ms", 0.0);
    
    // Update coefficients based on sample rate
    UpdateCoefficients(sample_rate);
    
    // Calculate hold time in samples
    hold_time_samples = (int)(hold_ms * sample_rate / 1000.0);
    
    // Process each sample
    for (int i = 0; i < sample_count; i++) {
        // Calculate current RMS
        double input_power = input[i] * input[i];
        static double avg_power = input_power; // Simple IIR filter
        avg_power = avg_power * 0.9 + input_power * 0.1; // Simplified averaging
        double current_rms = sqrt(avg_power);
        
        // Calculate required gain
        double required_gain = (current_rms > 0) ? target_rms / current_rms : 1.0;
        
        // Adjust gain based on whether we're going up or down
        if (required_gain > current_gain) {
            // Attack - increase gain slowly
            if (hold_counter <= 0) {
                current_gain = current_gain * attack_coeff + required_gain * (1.0 - attack_coeff);
            }
        } else {
            // Release - decrease gain more slowly
            if (hold_counter <= 0) {
                current_gain = current_gain * release_coeff + required_gain * (1.0 - release_coeff);
            }
        }
        
        // Apply the gain
        output[i] = input[i] * current_gain;
        
        // Update hold counter
        if (hold_counter > 0) {
            hold_counter--;
        }
        if (required_gain < current_gain) { // Only reset hold when gain decreases
            hold_counter = (int)hold_time_samples;
        }
    }
}

void AdaptiveGainControl::SetTargetRMS(double target_rms) {
    this->target_rms = target_rms;
    parameters.Set("target_rms", target_rms);
}

void AdaptiveGainControl::SetAttackTime(double ms) {
    parameters.Set("attack_time_ms", ms);
}

void AdaptiveGainControl::SetReleaseTime(double ms) {
    parameters.Set("release_time_ms", ms);
}

void AdaptiveGainControl::SetHoldTime(double ms) {
    parameters.Set("hold_time_ms", ms);
}

void AdaptiveGainControl::SetParameter(const String& name, double value) {
    parameters.Set(name, value);
}

double AdaptiveGainControl::GetParameter(const String& name) const {
    return parameters.Get(name, 0.0);
}

void AdaptiveGainControl::UpdateCoefficients(double sample_rate) {
    double attack_ms = parameters.Get("attack_time_ms", 10.0);
    double release_ms = parameters.Get("release_time_ms", 100.0);
    
    // Calculate coefficients for exponential approach
    if (attack_ms > 0) {
        attack_coeff = exp(-1.0 / (attack_ms * sample_rate / 1000.0));
    } else {
        attack_coeff = 0.0;
    }
    
    if (release_ms > 0) {
        release_coeff = exp(-1.0 / (release_ms * sample_rate / 1000.0));
    } else {
        release_coeff = 0.0;
    }
}

}
}