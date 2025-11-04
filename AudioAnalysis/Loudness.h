#ifndef _AudioAnalysis_Loudness_h_
#define _AudioAnalysis_Loudness_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "../AudioFX/Analyzer.h"
#include "../AudioFX/SignalBus.h"

using namespace Upp;

namespace DSP {

// LUFS meter for measuring loudness according to ITU-R BS.1770-4
class LUFSMeter {
public:
    LUFSMeter();
    
    // Process an audio buffer and measure LUFS
    double ProcessBuffer(const AudioBuffer& buffer, int sampleRate);
    
    // Get the integrated LUFS value (integrated over time)
    double GetIntegratedLUFS() const;
    
    // Get the momentary LUFS value (over the last 400ms)
    double GetMomentaryLUFS() const;
    
    // Get the short-term LUFS value (over the last 3s)
    double GetShortTermLUFS() const;
    
    // Reset the meter
    void Reset();
    
private:
    // Internal variables for LUFS calculations
    Vector<double> filterCoeffs;
    double integratedLUFS;
    double momentaryLUFS;
    double shortTermLUFS;
    
    // Apply K-weighting filter (for LUFS measurement)
    AudioBuffer ApplyKWeighting(const AudioBuffer& input, int sampleRate);
};

// Inter-sample peak detector
class ISPDetector {
public:
    ISPDetector();
    
    // Process an audio buffer to detect inter-sample peaks
    double ProcessBuffer(const AudioBuffer& buffer);
    
    // Get the maximum ISP value since last reset
    double GetMaxISP() const;
    
    // Reset the detector
    void Reset();
    
private:
    double maxISP;
    double previousSample;
};

// Automatic gain scheduler for maintaining consistent loudness
class AutoGainScheduler {
public:
    AutoGainScheduler();
    
    // Set the target loudness level
    void SetTargetLoudness(double lufs);
    
    // Process a buffer and return the appropriate gain to apply
    double ProcessBuffer(const AudioBuffer& buffer);
    
    // Get the current calculated gain
    double GetCurrentGain() const;
    
    // Reset the scheduler
    void Reset();
    
private:
    double targetLoudness;
    double currentGain;
    double smoothingFactor;
};

// Mastering assistant for applying mastering effects
class MasterAssistant {
public:
    MasterAssistant();
    
    // Process an audio buffer through the mastering chain
    void ProcessBuffer(AudioBuffer& buffer, int sampleRate);
    
    // Set parameters for various mastering processes
    void SetEQParams(double lowGain, double midGain, double highGain);
    void SetCompressorParams(double threshold, double ratio, double attack, double release);
    void SetLimiterParams(double threshold, double release);
    
    // Reset the assistant
    void Reset();
    
private:
    // Mastering parameters
    double eqLowGain, eqMidGain, eqHighGain;
    double compThreshold, compRatio, compAttack, compRelease;
    double limThreshold, limRelease;
    
    // Internal processing components
    LUFSMeter lufsMeter;
    ISPDetector ispDetector;
    AutoGainScheduler gainScheduler;
};

// Stabilizer for reducing dynamic range
class Stabilizer {
public:
    Stabilizer();
    
    // Process an audio buffer to stabilize dynamics
    void ProcessBuffer(AudioBuffer& buffer);
    
    // Set stabilization parameters
    void SetAttackTime(double ms);
    void SetReleaseTime(double ms);
    void SetThreshold(double db);
    
    // Reset the stabilizer
    void Reset();
    
private:
    double attackTime;
    double releaseTime;
    double threshold;
    double currentGain;
};

// Impact shaper for controlling transients
class ImpactShaper {
public:
    ImpactShaper();
    
    // Process an audio buffer to shape impact/transients
    void ProcessBuffer(AudioBuffer& buffer);
    
    // Set shaping parameters
    void SetAttackTime(double ms);
    void SetReleaseTime(double ms);
    void SetThreshold(double db);
    void SetRatio(double ratio);
    
    // Reset the shaper
    void Reset();
    
private:
    double attackTime;
    double releaseTime;
    double threshold;
    double ratio;
    double currentGain;
};

// Priority allocator for managing resource allocation in mastering
class PriorityAllocator {
public:
    PriorityAllocator();
    
    // Allocate processing priority for different mastering modules
    void AllocatePriority(int sampleRate, int channels);
    
    // Set processing priorities
    void SetEQPriority(double priority);
    void SetCompressionPriority(double priority);
    void SetLimitingPriority(double priority);
    
    // Get current allocation
    ValueMap GetAllocation() const;
    
    // Reset the allocator
    void Reset();
    
private:
    double eqPriority;
    double compressionPriority;
    double limitingPriority;
};

// Dither engine for adding dither when reducing bit depth
class DitherEngine {
public:
    DitherEngine();
    
    // Process an audio buffer with dithering
    void ProcessBuffer(AudioBuffer& buffer, int targetBitDepth);
    
    // Set dither type (rectangular, triangular, shaped)
    void SetDitherType(int type);
    
    // Reset the dither engine
    void Reset();
    
private:
    int ditherType;
    double lastError;
    Vector<double> noiseShapingFilter;
};

} // namespace DSP

#endif