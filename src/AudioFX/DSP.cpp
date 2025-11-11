#include "DSP.h"

namespace DSP {

// Only include implementations that are defined in the DSP namespace in DSP.h
// (i.e., FIRDesigner, IIRDesigner, AmbisonicsEncoder, BinauralRenderer, SurroundMeterBridge,
//  and other classes that are specifically declared in the DSP namespace in DSP.h)

// FIRDesigner implementation
FIRDesigner::FIRDesigner() {
    // Initialize
}

Vector<double> FIRDesigner::DesignLowPass(int order, double cutoffFreq, double sampleRate) {
    Vector<double> coefficients;
    coefficients.SetCount(order + 1);

    double omega = 2.0 * M_PI * cutoffFreq / sampleRate;

    // Generate sinc function
    for (int n = 0; n <= order; n++) {
        int center = order / 2;
        int shifted_n = n - center;

        if (shifted_n == 0) {
            coefficients[n] = omega / M_PI;
        } else {
            coefficients[n] = sin(omega * shifted_n) / (M_PI * shifted_n);
        }
    }

    // Apply windowing
    ApplyWindow(coefficients, 1); // Hamming window by default

    return coefficients;
}

Vector<double> FIRDesigner::DesignHighPass(int order, double cutoffFreq, double sampleRate) {
    // Start with lowpass and convert to highpass
    Vector<double> lowpass = DesignLowPass(order, cutoffFreq, sampleRate);
    Vector<double> coefficients;  // Fixed: use pick() for vectors to avoid copy
    coefficients <<= lowpass;  // Deep copy using <<= operator

    // Convert to highpass by spectral inversion
    for (int i = 0; i < coefficients.GetCount(); i++) {
        if (i == order / 2) {
            coefficients[i] = 1.0 - lowpass[i];
        } else {
            coefficients[i] = -lowpass[i];
        }
    }

    return coefficients;
}

Vector<double> FIRDesigner::DesignBandPass(int order, double lowFreq, double highFreq, double sampleRate) {
    // Design lowpass for high frequency
    Vector<double> lowpassHigh = DesignLowPass(order, highFreq, sampleRate);

    // Design lowpass for low frequency
    Vector<double> lowpassLow = DesignLowPass(order, lowFreq, sampleRate);

    // Subtract to get bandpass
    Vector<double> coefficients;
    coefficients.SetCount(order + 1);

    for (int i = 0; i < order + 1; i++) {
        coefficients[i] = lowpassHigh[i] - lowpassLow[i];
    }

    return coefficients;
}

Vector<double> FIRDesigner::DesignBandStop(int order, double lowFreq, double highFreq, double sampleRate) {
    // Start with bandpass and convert to bandstop
    Vector<double> bandpass = DesignBandPass(order, lowFreq, highFreq, sampleRate);
    Vector<double> coefficients;  // Fixed: use pick() for vectors to avoid copy
    coefficients <<= bandpass;  // Deep copy using <<= operator

    for (int i = 0; i < coefficients.GetCount(); i++) {
        if (i == order / 2) {
            coefficients[i] = 1.0 - bandpass[i];
        } else {
            coefficients[i] = -bandpass[i];
        }
    }

    return coefficients;
}

void FIRDesigner::ApplyWindow(Vector<double>& coefficients, int windowType) {
    switch (windowType) {
        case 0: // Rectangular
            break; // No windowing
        case 1: // Hamming
            ApplyWindowHamming(coefficients);
            break;
        case 2: // Hann
            ApplyWindowHann(coefficients);
            break;
        case 3: // Blackman
            ApplyWindowBlackman(coefficients);
            break;
    }
}

void FIRDesigner::ApplyWindowHamming(Vector<double>& coefficients) {
    int length = coefficients.GetCount();
    for (int i = 0; i < length; i++) {
        double w = 0.54 - 0.46 * cos(2.0 * M_PI * i / (length - 1));
        coefficients[i] *= w;
    }
}

void FIRDesigner::ApplyWindowHann(Vector<double>& coefficients) {
    int length = coefficients.GetCount();
    for (int i = 0; i < length; i++) {
        double w = 0.5 * (1.0 - cos(2.0 * M_PI * i / (length - 1)));
        coefficients[i] *= w;
    }
}

void FIRDesigner::ApplyWindowBlackman(Vector<double>& coefficients) {
    int length = coefficients.GetCount();
    for (int i = 0; i < length; i++) {
        double w = 0.52 - 0.48 * cos(2.0 * M_PI * i / (length - 1)) + 0.08 * cos(4.0 * M_PI * i / (length - 1));
        coefficients[i] *= w;
    }
}

// IIRDesigner implementation
IIRDesigner::IIRDesigner() : b0(1.0), b1(0.0), b2(0.0), a1(0.0), a2(0.0), x1(0.0), x2(0.0), y1(0.0), y2(0.0) {
    // Initialize with unity gain coefficients
}

void IIRDesigner::DesignLowPass(double freq, double q, double sampleRate) {
    // Biquad low-pass filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = sn / (2.0 * q);

    double scale = 1.0 / (1.0 + alpha);

    b0 = (1.0 - cs) * 0.5 * scale;
    b1 = (1.0 - cs) * scale;
    b2 = b0;  // same as b0
    a1 = -2.0 * cs * scale;
    a2 = (1.0 - alpha) * scale;
}

void IIRDesigner::DesignHighPass(double freq, double q, double sampleRate) {
    // Biquad high-pass filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = sn / (2.0 * q);

    double scale = 1.0 / (1.0 + alpha);

    b0 = (1.0 + cs) * 0.5 * scale;
    b1 = -(1.0 + cs) * scale;
    b2 = b0;  // same as b0
    a1 = -2.0 * cs * scale;
    a2 = (1.0 - alpha) * scale;
}

void IIRDesigner::DesignBandPass(double freq, double q, double sampleRate) {
    // Biquad band-pass filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = sn / (2.0 * q);

    double scale = 1.0 / (1.0 + alpha);

    b0 = alpha * scale;
    b1 = 0.0;
    b2 = -alpha * scale;
    a1 = -2.0 * cs * scale;
    a2 = (1.0 - alpha) * scale;
}

void IIRDesigner::DesignBandStop(double freq, double q, double sampleRate) {
    // Biquad band-stop filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double alpha = sn / (2.0 * q);

    double scale = 1.0 / (1.0 + alpha);

    b0 = 1.0 * scale;
    b1 = -2.0 * cs * scale;
    b2 = 1.0 * scale;
    a1 = -2.0 * cs * scale;
    a2 = (1.0 - alpha) * scale;
}

void IIRDesigner::DesignPeakingEQ(double freq, double q, double gain, double sampleRate) {
    // Biquad peaking EQ filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double A = pow(10.0, gain/40.0);
    double alpha = sn / (2.0 * q);

    double scale = 1.0 / (1.0 + alpha/A);

    b0 = (1.0 + alpha * A) * scale;
    b1 = (-2.0 * cs) * scale;
    b2 = (1.0 - alpha * A) * scale;
    a1 = (-2.0 * cs) * scale;
    a2 = (1.0 - alpha / A) * scale;
}

void IIRDesigner::DesignLowShelf(double freq, double slope, double gain, double sampleRate) {
    // Biquad low-shelf filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double A = pow(10.0, gain/40.0);
    double beta = sqrt((A + 1.0/A) * (1.0/slope - 1.0) + 2.0);

    double scale = 1.0 / (A + 1.0 + (A - 1.0) * cs + beta * sn);

    b0 = A * ((A + 1.0) - (A - 1.0) * cs + beta * sn) * scale;
    b1 = 2.0 * A * ((A - 1.0) - (A + 1.0) * cs) * scale;
    b2 = A * ((A + 1.0) - (A - 1.0) * cs - beta * sn) * scale;
    a1 = -2.0 * ((A - 1.0) + (A + 1.0) * cs) * scale;
    a2 = ((A + 1.0) + (A - 1.0) * cs - beta * sn) * scale;
}

void IIRDesigner::DesignHighShelf(double freq, double slope, double gain, double sampleRate) {
    // Biquad high-shelf filter design using bilinear transform
    double omega = 2.0 * M_PI * freq / sampleRate;
    double sn = sin(omega);
    double cs = cos(omega);
    double A = pow(10.0, gain/40.0);
    double beta = sqrt((A + 1.0/A) * (1.0/slope - 1.0) + 2.0);

    double scale = 1.0 / (A + 1.0 - (A - 1.0) * cs + beta * sn);

    b0 = A * ((A + 1.0) + (A - 1.0) * cs + beta * sn) * scale;
    b1 = -2.0 * A * ((A - 1.0) + (A + 1.0) * cs) * scale;
    b2 = A * ((A + 1.0) + (A - 1.0) * cs - beta * sn) * scale;
    a1 = 2.0 * ((A - 1.0) - (A + 1.0) * cs) * scale;
    a2 = ((A + 1.0) - (A - 1.0) * cs - beta * sn) * scale;
}

ValueMap IIRDesigner::GetCoefficients() const {
    ValueMap coeffs;
    coeffs.Set("b0", b0);
    coeffs.Set("b1", b1);
    coeffs.Set("b2", b2);
    coeffs.Set("a1", a1);
    coeffs.Set("a2", a2);
    return coeffs;
}

double IIRDesigner::ProcessSample(double input) {
    // Direct Form II transposed implementation
    double output = b0 * input + x1;
    x1 = b1 * input - a1 * output + x2;
    x2 = b2 * input - a2 * output;

    return output;
}

// AmbisonicsEncoder implementation
AmbisonicsEncoder::AmbisonicsEncoder() : order(kFirstOrder), normalizationType(0) {
    // Default to first-order SN3D
}

void AmbisonicsEncoder::SetOrder(AmbisonicOrder ord) {
    order = ord;
}

void AmbisonicsEncoder::EncodeSignal(const AudioBuffer& input, Vector<AudioBuffer>& output,
                                     double azimuth, double elevation) {
    // Calculate the number of required output channels
    int channelCount = GetOutputChannelCount();
    output.SetCount(channelCount);

    // Initialize output buffers
    for (int i = 0; i < channelCount; i++) {
        output[i].SetCount(input.GetCount());
    }

    // Convert angles to radians
    double az = azimuth * M_PI / 180.0;
    double el = elevation * M_PI / 180.0;

    // For first-order ambisonics (W, X, Y, Z)
    if (order >= kFirstOrder) {
        // W (omni) - stays the same
        output[0] <<= input;  // Use <<= for deep copy instead of assignment

        // X (front-back) - cosine of azimuth
        for (int i = 0; i < input.GetCount(); i++) {
            output[1][i] = input[i] * cos(el) * cos(az);
        }

        // Y (left-right) - sine of azimuth
        for (int i = 0; i < input.GetCount(); i++) {
            output[2][i] = input[i] * cos(el) * sin(az);
        }

        // Z (up-down) - sine of elevation
        for (int i = 0; i < input.GetCount(); i++) {
            output[3][i] = input[i] * sin(el);
        }
    }

    // Add higher-order components for second and third order
    if (order >= kSecondOrder) {
        // Second-order components would go here
    }

    if (order >= kThirdOrder) {
        // Third-order components would go here
    }
}

int AmbisonicsEncoder::GetOutputChannelCount() const {
    // For Nth order: (N+1)² channels
    int n = static_cast<int>(order);
    return (n + 1) * (n + 1);
}

void AmbisonicsEncoder::SetNormalizationType(int type) {
    normalizationType = max(0, min(2, type));
}

// BinauralRenderer implementation
BinauralRenderer::BinauralRenderer() : hrtfLoaded(false), useITD(true), interpolationMethod(1) {
    // Initialize default values
}

bool BinauralRenderer::LoadHRTF(const String& filePath) {
    // In a real implementation, this would load HRTF data from file
    // For now, just return true to indicate success
    String mutablePath = filePath; // Fixed: avoid assigning to const parameter
    hrtfLoaded = true;
    return true;
}

void BinauralRenderer::Process(const AudioBuffer& input, AudioBuffer& leftOutput, AudioBuffer& rightOutput,
                               double azimuth, double elevation) {
    // In a real implementation, this would apply HRTF convolution
    // For now, we'll implement a simple panning approach

    leftOutput.SetCount(input.GetCount());
    rightOutput.SetCount(input.GetCount());

    // Simple azimuth panning
    double leftGain = sqrt(0.5 * (1.0 - azimuth / 180.0));  // Convert azimuth (-180 to 180) to gain
    double rightGain = sqrt(0.5 * (1.0 + azimuth / 180.0));

    for (int i = 0; i < input.GetCount(); i++) {
        leftOutput[i] = input[i] * leftGain;
        rightOutput[i] = input[i] * rightGain;
    }

    // In a real implementation, elevation would affect HRTF selection
    // and ITD would add sample delays
    if (useITD) {
        // Simple ITD implementation for center panned sounds
        if (abs(azimuth) < 10.0) { // Only for center sounds
            // Add a tiny delay for center position (in samples)
            double delaySamples = 0.6; // About 0.6 samples at 44.1kHz ≈ 13.6 microseconds
            if (delaySamples > 0.5) {
                // Apply the delay by shifting samples
                int delayInt = (int)delaySamples;
                double delayFrac = delaySamples - delayInt;

                // This is a simplified implementation
                for (int i = delayInt; i < leftOutput.GetCount(); i++) {
                    leftOutput[i] += leftOutput[i - delayInt] * (1.0 - delayFrac);
                }
            }
        }
    }
}

void BinauralRenderer::SetITD(bool enabled) {
    useITD = enabled;
}

void BinauralRenderer::SetInterpolationMethod(int method) {
    interpolationMethod = max(0, min(2, method));
}

// SurroundMeterBridge implementation
SurroundMeterBridge::SurroundMeterBridge() : integrationTime(300.0) { // 300ms integration time
    // Initialize
}

void SurroundMeterBridge::SetChannelConfig(const String& config) {
    channelConfig = config;

    // Set up channel levels based on configuration
    if (config == "5.1") {
        channelLevels.SetCount(6); // L, R, C, LFE, Ls, Rs
    } else if (config == "7.1") {
        channelLevels.SetCount(8); // L, R, C, LFE, Ls, Rs, Lrs, Rrs
    } else if (config == "7.1.4") { // Dolby Atmos 7.1.4
        channelLevels.SetCount(12); // 7.1 + 4 height channels
    } else {
        channelLevels.SetCount(2); // Default to stereo
    }
}

ValueMap SurroundMeterBridge::ProcessWithMetering(const Vector<AudioBuffer>& input) {
    ValueMap meterData;

    // Calculate RMS level for each channel
    for (int ch = 0; ch < min(input.GetCount(), channelLevels.GetCount()); ch++) {
        double sum = 0.0;
        int count = 0;

        for (double sample : input[ch]) {
            sum += sample * sample;
            count++;
        }

        if (count > 0) {
            channelLevels[ch] = sqrt(sum / count);  // RMS
            meterData.Set("ch" + IntStr(ch), channelLevels[ch]);
        }
    }

    return meterData;
}

double SurroundMeterBridge::GetChannelLevel(int channelIndex) const {
    if (channelIndex >= 0 && channelIndex < channelLevels.GetCount()) {
        return channelLevels[channelIndex];
    }
    return 0.0;
}

void SurroundMeterBridge::SetIntegrationTime(double ms) {
    integrationTime = max(10.0, min(2000.0, ms)); // Clamp between 10ms and 2000ms
}

}