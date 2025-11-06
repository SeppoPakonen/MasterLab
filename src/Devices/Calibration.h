#ifndef _Devices_Calibration_h_
#define _Devices_Calibration_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <DSP/DSP.h>

using namespace Upp;

namespace Calibration {

// MeasurementAnalyzer - analyzes acoustic measurements for calibration
class MeasurementAnalyzer {
public:
    typedef MeasurementAnalyzer CLASSNAME;
    
    MeasurementAnalyzer();
    virtual ~MeasurementAnalyzer();
    
    // Analyze impulse response or frequency response measurement
    struct AnalysisResult {
        double frequency_response[1024];  // Sampled frequency response
        double impulse_response[2048];    // Impulse response
        double delay;                     // Measured delay in samples
        double level_diff;                // Level difference in dB
        double correlation;               // Cross-correlation with reference
        double confidence;                // Confidence of measurement (0-1)
        Time timestamp;
    };
    
    AnalysisResult AnalyzeMeasurement(const Vector<double>& measured_signal, 
                                    const Vector<double>& reference_signal,
                                    double sample_rate = 44100.0);
    
    // Configure analysis parameters
    void SetAnalysisBandwidth(double hz) { bandwidth = hz; }
    void SetMinFrequency(double hz) { min_freq = hz; }
    void SetMaxFrequency(double hz) { max_freq = hz; }
    void SetResolution(int bins) { resolution_bins = bins; }
    
private:
    double bandwidth;
    double min_freq;
    double max_freq;
    int resolution_bins;
};

// PhaseAnalyzer - analyzes phase relationships for spatial calibration
class PhaseAnalyzer {
public:
    typedef PhaseAnalyzer CLASSNAME;
    
    PhaseAnalyzer();
    virtual ~PhaseAnalyzer();
    
    // Analyze phase relationship between two signals
    struct PhaseResult {
        double unwrapped_phase[1024];     // Unwrapped phase in radians
        double group_delay[1024];         // Group delay in samples
        double coherence;                 // Phase coherence (0-1)
        double phase_difference;          // Overall phase difference in radians
        double phase_alignment;           // Alignment quality (0-1)
    };
    
    PhaseResult AnalyzePhaseRelationship(const Vector<double>& signal1, 
                                       const Vector<double>& signal2,
                                       double sample_rate = 44100.0);
    
    // Configure phase analysis
    void SetPhaseTolerance(double tolerance_rad) { phase_tolerance = tolerance_rad; }
    void SetCoherenceThreshold(double threshold) { coherence_threshold = threshold; }
    
private:
    double phase_tolerance;
    double coherence_threshold;
};

// DelaySolver - computes optimal delays for spatial alignment
class DelaySolver {
public:
    typedef DelaySolver CLASSNAME;
    
    DelaySolver();
    virtual ~DelaySolver();
    
    // Solve for optimal delays given measurements
    struct DelaySolution {
        Vector<double> optimal_delays;    // Delays in samples for each channel
        Vector<double> compensation_gains; // Gains to equalize levels
        double total_error;              // Residual error after correction
        double confidence;               // Confidence in solution (0-1)
    };
    
    DelaySolution ComputeDelays(const Vector<MeasurementAnalyzer::AnalysisResult>& measurements,
                               double sample_rate = 44100.0);
    
    // Solve delays for specific spatial configuration
    DelaySolution SolveForConfiguration(const Vector<Point>& speaker_positions,
                                      Point reference_position,
                                      double sample_rate = 44100.0);
    
    // Configure solver
    void SetMaxDelay(double samples) { max_delay_samples = samples; }
    void SetPrecision(double precision) { solver_precision = precision; }
    void SetIterations(int iterations) { max_iterations = iterations; }
    
private:
    double max_delay_samples;
    double solver_precision;
    int max_iterations;
};

}

#endif