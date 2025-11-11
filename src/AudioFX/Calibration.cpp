#include "DSP.h"

namespace Calibration {

MeasurementAnalyzer::MeasurementAnalyzer() {
    // Initialize
}

ValueMap MeasurementAnalyzer::AnalyzeImpulseResponse(const AudioBuffer& impulse) {
    ValueMap result;

    // Find peak in impulse response (for delay measurement)
    double maxVal = 0.0;
    int peakPos = 0;

    if (impulse.data.GetCount() > 0 && impulse.data[0].GetCount() > 0) {
        for (int i = 0; i < impulse.data[0].GetCount(); i++) {
            if (abs(impulse.data[0][i]) > maxVal) {
                maxVal = abs(impulse.data[0][i]);
                peakPos = i;
            }
        }
    }

    result.Set("peak_position", peakPos);
    result.Set("peak_value", maxVal);

    // Calculate total energy
    double energy = 0.0;
    if (impulse.data.GetCount() > 0) {
        for (int i = 0; i < impulse.data[0].GetCount(); i++) {
            double sample = impulse.data[0][i];
            energy += sample * sample;
        }
    }
    result.Set("energy", energy);

    // Calculate decay time (T60) - time to decay 60dB
    double initialEnergy = 0.0;
    if (impulse.data.GetCount() > 0 && impulse.data[0].GetCount() > 0) {
        int impulseSize = impulse.data[0].GetCount();
        initialEnergy = impulse.data[0][0] * impulse.data[0][0];
        double targetEnergy = initialEnergy * pow(10.0, -60.0/10.0);  // -60dB

        int t60Sample = 0;
        for (int i = 0; i < impulse.data[0].GetCount(); i++) {
            if (impulse.data[0][i] * impulse.data[0][i] <= targetEnergy) {
                t60Sample = i;
                break;
            }
        }

        result.Set("t60_sample", t60Sample);
    } else {
        result.Set("t60_sample", 0);
    }

    return result;
}

ValueMap MeasurementAnalyzer::AnalyzeFrequencyResponse(const AudioBuffer& stimulus, const AudioBuffer& response) {
    ValueMap result;

    // In a real implementation, this would compute FFTs and calculate frequency response
    // For now, we'll just return some placeholder values

    // Calculate correlation between signals
    double correlation = 0.0;
    int minSize = 0;

    if (stimulus.data.GetCount() > 0 && response.data.GetCount() > 0) {
        int stimSize = stimulus.data[0].GetCount();
        int respSize = response.data[0].GetCount();
        minSize = min(stimSize, respSize);

        for (int i = 0; i < minSize; i++) {
            correlation += stimulus.data[0][i] * response.data[0][i];
        }
    }

    if (minSize > 0) {
        result.Set("correlation", correlation / minSize);
    } else {
        result.Set("correlation", 0.0);
    }

    return result;
}

double MeasurementAnalyzer::MeasureTHDN(const AudioBuffer& signal, const AudioBuffer& fundamental) {
    // Calculate fundamental power
    double fundPower = 0.0;
    if (fundamental.data.GetCount() > 0) {
        for (int i = 0; i < fundamental.data[0].GetCount(); i++) {
            double sample = fundamental.data[0][i];
            fundPower += sample * sample;
        }
    }

    // Calculate total signal power
    double totalPower = 0.0;
    if (signal.data.GetCount() > 0) {
        for (int i = 0; i < signal.data[0].GetCount(); i++) {
            double sample = signal.data[0][i];
            totalPower += sample * sample;
        }
    }

    // Calculate noise/distortion power
    double noisePower = max(0.0, totalPower - fundPower);

    // Calculate THD+N ratio
    if (fundPower > 0.0) {
        double thdnRatio = noisePower / fundPower;
        return 20.0 * log10(thdnRatio); // Convert to dB
    }

    return -999.0; // Very low value if fundamental power is zero
}

double MeasurementAnalyzer::MeasureIntermodulationDistortion(const AudioBuffer& signal) {
    // This would require more complex analysis
    // For now, return a placeholder value
    return -60.0; // Typical IMD value in dB
}

double MeasurementAnalyzer::MeasureLatency(const AudioBuffer& stimulus, const AudioBuffer& response, double sampleRate) {
    // Find the delay between stimulus and response
    int maxDelay = 0;
    if (stimulus.data.GetCount() > 0 && response.data.GetCount() > 0) {
        int stimSize = stimulus.data[0].GetCount();
        int respSize = response.data[0].GetCount();
        maxDelay = min(stimSize, respSize) / 4; // reasonable maximum delay
    }

    double maxCorrelation = -1.0;
    int bestDelay = 0;

    for (int delay = 0; delay < maxDelay; delay++) {
        double correlation = 0.0;
        int count = 0;

        if (stimulus.data.GetCount() > 0 && response.data.GetCount() > 0) {
            for (int i = delay; i < stimulus.data[0].GetCount() && i - delay < response.data[0].GetCount(); i++) {
                correlation += stimulus.data[0][i] * response.data[0][i - delay];
                count++;
            }
        }

        if (count > 0) {
            correlation /= count; // Normalize
        }

        if (abs(correlation) > maxCorrelation) {
            maxCorrelation = abs(correlation);
            bestDelay = delay;
        }
    }

    // Convert samples to milliseconds
    return (bestDelay / sampleRate) * 1000.0;
}

AudioBuffer MeasurementAnalyzer::ComputeFFT(const AudioBuffer& signal) {
    // In a real implementation, this would perform FFT
    // For now, return an empty buffer
    AudioBuffer empty;
    return empty;
}

double MeasurementAnalyzer::ComputePower(const AudioBuffer& signal) {
    // Calculate the power of the signal
    double sum = 0.0;
    for (int ch = 0; ch < signal.data.GetCount(); ch++) {
        for (int i = 0; i < signal.data[ch].GetCount(); i++) {
            double sample = signal.data[ch][i];
            sum += sample * sample;
        }
    }
    
    int totalSamples = 0;
    for (int ch = 0; ch < signal.data.GetCount(); ch++) {
        totalSamples += signal.data[ch].GetCount();
    }
    
    return totalSamples > 0 ? sum / totalSamples : 0.0;
}

// Phase analyzer implementation
PhaseAnalyzer::PhaseAnalyzer() {
    // Initialize
}

ValueMap PhaseAnalyzer::AnalyzePhase(const AudioBuffer& signal1, const AudioBuffer& signal2) {
    ValueMap result;

    // Calculate phase difference over time
    double avgPhaseDiff = 0.0;
    int count = 0;

    int minSize = 0;
    if (signal1.data.GetCount() > 0 && signal2.data.GetCount() > 0) {
        int signal1Size = signal1.data[0].GetCount();
        int signal2Size = signal2.data[0].GetCount();
        minSize = min(signal1Size, signal2Size);

        for (int i = 0; i < minSize; i++) {
            // Approximate phase difference using Hilbert transform approach
            double phaseDiff = atan2(signal2.data[0][i], signal1.data[0][i]);
            avgPhaseDiff += phaseDiff;
            count++;
        }
    }

    if (count > 0) {
        avgPhaseDiff /= count;
    }

    result.Set("avg_phase_difference", avgPhaseDiff);

    return result;
}

double PhaseAnalyzer::GetPhaseDifferenceAtFrequency(const AudioBuffer& signal1, const AudioBuffer& signal2,
                                                   double freq, double sampleRate) {
    // Find FFT bin for the given frequency
    int bin = 0;
    if (signal1.data.GetCount() > 0) {
        bin = (int)(freq * signal1.data[0].GetCount() / sampleRate);
        int halfSize = signal1.data[0].GetCount() / 2;
        if (bin >= halfSize) bin = halfSize - 1;
    }

    double omega = 2.0 * M_PI * freq / sampleRate;
    double cosSum = 0.0, sinSum = 0.0;

    if (signal1.data.GetCount() > 0 && signal2.data.GetCount() > 0) {
        int signal1Size = signal1.data[0].GetCount();
        int signal2Size = signal2.data[0].GetCount();
        int minSize = min(signal1Size, signal2Size);

        for (int i = 0; i < minSize; i++) {
            double phase = omega * i;
            cosSum += (signal1.data[0][i] * cos(phase) + signal2.data[0][i] * sin(phase));
            sinSum += (signal1.data[0][i] * sin(phase) - signal2.data[0][i] * cos(phase));
        }
    }

    return atan2(sinSum, cosSum);
}

bool PhaseAnalyzer::IsPhaseCoherent(const AudioBuffer& signal1, const AudioBuffer& signal2,
                                   double coherenceThreshold) {
    // Calculate correlation coefficient
    double sum1 = 0.0, sum2 = 0.0, sum12 = 0.0;
    double mean1 = 0.0, mean2 = 0.0;

    int minSize = 0;
    if (signal1.data.GetCount() > 0 && signal2.data.GetCount() > 0) {
        int signal1Size = signal1.data[0].GetCount();
        int signal2Size = signal2.data[0].GetCount();
        minSize = min(signal1Size, signal2Size);

        // Calculate means
        for (int i = 0; i < minSize; i++) {
            mean1 += signal1.data[0][i];
            mean2 += signal2.data[0][i];
        }
        mean1 /= minSize;
        mean2 /= minSize;

        // Calculate correlation
        for (int i = 0; i < minSize; i++) {
            double diff1 = signal1.data[0][i] - mean1;
            double diff2 = signal2.data[0][i] - mean2;
            sum1 += diff1 * diff1;
            sum2 += diff1 * diff2;
        }
    }

    if (sum1 > 0 && sum2 > 0) {
        double correlation = sum12 / sqrt(sum1 * sum2);
        return abs(correlation) >= coherenceThreshold;
    }

    return false;
}

ValueMap PhaseAnalyzer::GetPhaseCorrelationData(const AudioBuffer& signal1, const AudioBuffer& signal2) {
    ValueMap result;

    // Calculate full phase correlation
    double correlation = 0.0;
    int minSize = 0;

    if (signal1.data.GetCount() > 0 && signal2.data.GetCount() > 0) {
        int signal1Size = signal1.data[0].GetCount();
        int signal2Size = signal2.data[0].GetCount();
        minSize = min(signal1Size, signal2Size);

        for (int i = 0; i < minSize; i++) {
            correlation += signal1.data[0][i] * signal2.data[0][i];
        }
    }

    if (minSize > 0) {
        result.Set("correlation", correlation / minSize);
    } else {
        result.Set("correlation", 0.0);
    }

    return result;
}

double PhaseAnalyzer::CalculatePhaseAtBin(const Complex& fft1, const Complex& fft2, int bin) {
    // Calculate phase difference for a specific FFT bin
    double phase1 = arg(fft1);
    double phase2 = arg(fft2);
    return phase2 - phase1;
}

// Delay solver implementation
DelaySolver::DelaySolver() : algorithm(0) {
    // Default to cross-correlation
}

double DelaySolver::SolveDelay(const AudioBuffer& reference, const AudioBuffer& delayed, double sampleRate) {
    if (algorithm == 0) { // Cross-correlation
        int maxDelay = 0;
        if (reference.data.GetCount() > 0 && delayed.data.GetCount() > 0) {
            int refSize = reference.data[0].GetCount();
            int delSize = delayed.data[0].GetCount();
            maxDelay = min(refSize, delSize) / 4; // reasonable maximum delay
        }

        double maxCorrelation = -1.0;
        int bestDelay = 0;

        for (int delay = -maxDelay; delay < maxDelay; delay++) {
            double correlation = 0.0;
            int count = 0;

            if (delay >= 0) {
                if (reference.data.GetCount() > 0 && delayed.data.GetCount() > 0) {
                    int refSize = reference.data[0].GetCount();
                    int delSize = delayed.data[0].GetCount();
                    for (int i = 0; i < refSize - delay && i < delSize; i++) {
                        correlation += reference.data[0][i + delay] * delayed.data[0][i];
                        count++;
                    }
                }
            } else {
                if (reference.data.GetCount() > 0 && delayed.data.GetCount() > 0) {
                    int refSize = reference.data[0].GetCount();
                    int delSize = delayed.data[0].GetCount();
                    for (int i = 0; i < delSize + delay && i < refSize; i++) {
                        correlation += reference.data[0][i] * delayed.data[0][i - delay];
                        count++;
                    }
                }
            }

            if (count > 0) {
                correlation /= count; // Normalize
            }

            if (abs(correlation) > maxCorrelation) {
                maxCorrelation = abs(correlation);
                bestDelay = delay;
            }
        }

        return bestDelay;  // Return delay in samples
    }

    // Other algorithms would be implemented here
    return 0.0;
}

Vector<double> DelaySolver::SolveDelays(const Vector<AudioBuffer>& referenceSignals,
                                       const Vector<AudioBuffer>& delayedSignals, double sampleRate) {
    Vector<double> delays;
    int minCount = min(referenceSignals.GetCount(), delayedSignals.GetCount());

    for (int i = 0; i < minCount; i++) {
        delays.Add(SolveDelay(referenceSignals[i], delayedSignals[i], sampleRate));
    }

    return delays;
}

double DelaySolver::CalculateDelayForDistance(double distanceMeters) {
    // Speed of sound = 343 m/s
    return distanceMeters / 343.0;  // Returns delay in seconds
}

void DelaySolver::SetAlgorithm(int algo) {
    algorithm = max(0, min(2, algo));
}

} // namespace Calibration