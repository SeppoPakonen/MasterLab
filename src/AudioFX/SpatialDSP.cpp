#include "SpatialDSP.h"
#include <Math/FFT.h>

namespace DSP {

// FIRDesigner implementation
FIRDesigner::FIRDesigner() : window_type(2), ripple_db(0.1), transition_bw(500.0) { // Default Hann window
    // Initialize
}

FIRDesigner::~FIRDesigner() {
    // Cleanup
}

Vector<double> FIRDesigner::DesignLowPass(int filter_length, double cutoff_freq, double sample_rate) {
    Vector<double> h(filter_length);
    double omega_c = 2.0 * M_PI * cutoff_freq / sample_rate;
    
    // Design ideal low-pass filter impulse response
    int center = filter_length / 2;
    for (int n = 0; n < filter_length; n++) {
        int shifted_n = n - center;
        if (shifted_n == 0) {
            h[n] = omega_c / M_PI;
        } else {
            h[n] = sin(omega_c * shifted_n) / (M_PI * shifted_n);
        }
    }
    
    // Apply window to truncate infinite impulse response
    return ApplyWindow(h, window_type);
}

Vector<double> FIRDesigner::DesignHighPass(int filter_length, double cutoff_freq, double sample_rate) {
    // Design high-pass as 1 - low-pass (complementary filter)
    Vector<double> lp_filter = DesignLowPass(filter_length, cutoff_freq, sample_rate);
    Vector<double> hp_filter(filter_length);
    
    for (int i = 0; i < filter_length; i++) {
        if (i == filter_length / 2) {
            hp_filter[i] = 1.0 - lp_filter[i];  // DC = 0 for HP
        } else {
            hp_filter[i] = -lp_filter[i];       // Negate for complementary response
        }
    }
    
    return hp_filter;
}

Vector<double> FIRDesigner::DesignBandPass(int filter_length, double low_freq, double high_freq, double sample_rate) {
    // Design as difference of low-pass filters
    Vector<double> low_freq_filter = DesignLowPass(filter_length, low_freq, sample_rate);
    Vector<double> high_freq_filter = DesignLowPass(filter_length, high_freq, sample_rate);
    
    Vector<double> bp_filter(filter_length);
    for (int i = 0; i < filter_length; i++) {
        bp_filter[i] = high_freq_filter[i] - low_freq_filter[i];
    }
    
    return bp_filter;
}

Vector<double> FIRDesigner::DesignBandStop(int filter_length, double low_freq, double high_freq, double sample_rate) {
    // Design as complement of band-pass
    Vector<double> bp_filter = DesignBandPass(filter_length, low_freq, high_freq, sample_rate);
    Vector<double> bs_filter(filter_length);
    
    for (int i = 0; i < filter_length; i++) {
        if (i == filter_length / 2) {
            bs_filter[i] = 1.0 - bp_filter[i];  // Pass DC
        } else {
            bs_filter[i] = -bp_filter[i];       // Negate for complementary response
        }
    }
    
    return bs_filter;
}

Vector<double> FIRDesigner::ApplyWindow(const Vector<double>& ideal_impulse, int window_type) {
    Vector<double> windowed_impulse;
    windowed_impulse <<= ideal_impulse; // Use U++ vector copy operator
    int length = ideal_impulse.GetCount();
    
    for (int i = 0; i < length; i++) {
        double win_val = WindowValue(i, length, window_type);
        windowed_impulse[i] *= win_val;
    }
    
    return windowed_impulse;
}

double FIRDesigner::WindowValue(int n, int length, int window_type) {
    double w = 1.0; // Rectangular window by default
    
    switch(window_type) {
        case 0: // Rectangular (already set)
            break;
        case 1: // Hamming
            w = 0.54 - 0.46 * cos(2.0 * M_PI * n / (length - 1));
            break;
        case 2: // Hann
            w = 0.5 * (1.0 - cos(2.0 * M_PI * n / (length - 1)));
            break;
        case 3: // Blackman
            w = 0.42 - 0.5 * cos(2.0 * M_PI * n / (length - 1)) + 
                0.08 * cos(4.0 * M_PI * n / (length - 1));
            break;
    }
    
    return w;
}

void FIRDesigner::ApplyFilter(const Vector<double>& input, 
                              Vector<double>& output,
                              const Vector<double>& filter_coeffs) {
    int input_len = input.GetCount();
    int coeff_len = filter_coeffs.GetCount();
    
    output.SetCount(input_len);
    
    // Direct convolution implementation
    for (int n = 0; n < input_len; n++) {
        output[n] = 0.0;
        for (int k = 0; k < coeff_len; k++) {
            if (n >= k) {
                output[n] += input[n - k] * filter_coeffs[k];
            }
        }
    }
}

// IIRDesigner implementation
IIRDesigner::IIRDesigner() {
    // Initialize
}

IIRDesigner::~IIRDesigner() {
    // Cleanup
}

IIRDesigner::IIRCoefficients IIRDesigner::DesignButterworth(int order, double cutoff_freq, double sample_rate, bool highpass) {
    IIRCoefficients coeffs;
    
    // Calculate prototype poles for Butterworth filter
    Vector<Complex> poles;
    for (int k = 0; k < order; k++) {
        // Poles of analog prototype (s-plane)
        double angle = M_PI/2.0 + (2*k + 1)*M_PI/(2*order);
        poles.Add(Complex(cos(angle), sin(angle))); // Unit circle for Butterworth
    }
    
    // Transform to lowpass with desired cutoff (pre-warping for bilinear transform)
    double warped_freq = 2.0 * sample_rate * tan(M_PI * cutoff_freq / sample_rate);
    
    // Scale poles by cutoff frequency
    for (auto& pole : poles) {
        pole *= warped_freq;
    }
    
    // Apply bilinear transform to convert to digital domain
    // This would require more complex math to convert poles/zeros to transfer function coefficients
    // Simplified implementation: create a basic filter
    coeffs.b.SetCount(order + 1);
    coeffs.a.SetCount(order + 1);
    
    // Initialize with basic values (would be properly calculated in full implementation)
    for (int i = 0; i <= order; i++) {
        coeffs.b[i] = 1.0 / (order + 1); // Simplified: uniform coefficients
        coeffs.a[i] = (i == 0) ? 1.0 : 0.0; // For now, basic identity
    }
    
    coeffs.gain = 1.0; // Default gain
    
    // For a highpass, we would need to transform the lowpass design
    if (highpass) {
        // This would involve more complex transformation in a full implementation
    }
    
    return coeffs;
}

// AmbisonicsEncoder implementation
AmbisonicsEncoder::AmbisonicsEncoder() : distance_attenuation(true), near_field_effect(false), 
                                        order(FIRST_ORDER), reference_distance(1.0) {
    // Initialize
}

AmbisonicsEncoder::~AmbisonicsEncoder() {
    // Cleanup
}

Vector<double> AmbisonicsEncoder::EncodePointSource(double azimuth, double elevation, double distance, Order order) {
    Vector<double> ambi_components;
    int channel_count = GetChannelCount(order);
    ambi_components.SetCount(channel_count);
    
    // Convert degrees to radians
    double az_rad = azimuth * M_PI / 180.0;
    double el_rad = elevation * M_PI / 180.0;
    
    // W (0th order - omnidirectional)
    ambi_components[0] = 1.0;
    
    if (order >= FIRST_ORDER) {
        // X (1st order - front-back)  
        ambi_components[1] = cos(el_rad) * sin(az_rad);
        // Y (1st order - left-right)
        ambi_components[2] = cos(el_rad) * cos(az_rad);
        // Z (1st order - up-down)
        ambi_components[3] = sin(el_rad);
    }
    
    // For higher orders, additional components would be calculated here
    // Second order: R, S, T, U, V
    // Third order: K, L, M, N, O, P, Q
    // These involve higher-order spherical harmonics
    
    // Apply distance attenuation if enabled
    if (distance_attenuation) {
        double gain = CalculateDistanceGain(distance);
        for (int i = 0; i < ambi_components.GetCount(); i++) {
            ambi_components[i] *= gain;
        }
    }
    
    return ambi_components;
}

int AmbisonicsEncoder::GetChannelCount(Order order) const {
    switch (order) {
        case FIRST_ORDER: return 4;  // W, X, Y, Z
        case SECOND_ORDER: return 9; // + R, S, T, U, V  
        case THIRD_ORDER: return 16; // + K, L, M, N, O, P, Q
        default: return 4;
    }
}

double AmbisonicsEncoder::CalculateDistanceGain(double distance) const {
    if (distance <= reference_distance) return 1.0;
    return reference_distance / distance;  // Inverse distance law
}

// BinauralRenderer implementation
BinauralRenderer::BinauralRenderer() : crossfeed_enabled(true), pinna_simulation(false), interp_method(1) {
    // Initialize
}

BinauralRenderer::~BinauralRenderer() {
    // Cleanup
}

bool BinauralRenderer::LoadHRTFDatabase(const String& database_path) {
    // In a real implementation, this would load HRTF data from a database
    // For now, we'll just return true to indicate success
    return true;
}

void BinauralRenderer::RenderBinaural(const Vector<double>& input, 
                                      Vector<double>& left_output, 
                                      Vector<double>& right_output,
                                      double azimuth, double elevation, double distance) {
    // Find closest HRTF based on position
    int hrir_idx = GetHRIRIndex(azimuth, elevation);
    
    if (hrir_idx >= 0 && hrir_idx < hrir_data.GetCount()) {
        // Apply HRIR to input (left ear)
        ApplyHRIR(input, left_output, hrir_data[hrir_idx]);
        
        // For right ear, we'd use a different HRIR
        // Simplified implementation: use same HRIR for now
        ApplyHRIR(input, right_output, hrir_data[hrir_idx]);
        
        // Apply distance effects
        double gain = 1.0 / max(1.0, distance); // Simplified distance law
        for (int i = 0; i < left_output.GetCount(); i++) {
            left_output[i] *= gain;
            right_output[i] *= gain;
        }
    } else {
        // Default behavior: copy input to both outputs
        left_output <<= input;
        right_output <<= input;
    }
}

void BinauralRenderer::ApplyHRIR(const Vector<double>& input,
                                 Vector<double>& output,
                                 const BufferView& hrir) {
    // Convolve input with HRIR
    int input_len = input.GetCount();
    int hrir_len = hrir.GetCount();
    int output_len = input_len + hrir_len - 1;
    
    output.SetCount(output_len);
    for (int i = 0; i < output_len; i++) {
        output[i] = 0.0;
        for (int j = 0; j < hrir_len; j++) {
            int input_idx = i - j;
            if (input_idx >= 0 && input_idx < input_len) {
                output[i] += input[input_idx] * hrir[j];
            }
        }
    }
}

int BinauralRenderer::GetHRIRIndex(double azimuth, double elevation) const {
    // Simplified lookup: find nearest HRIR based on azimuth and elevation
    // In a real implementation, this would be more sophisticated
    return 0; // For now, return first available HRIR
}

// HeadTracker implementation
HeadTracker::HeadTracker() : is_calibrated(false), sim_azimuth_offset(0.0), 
                           sim_elevation_offset(0.0), sim_distance_offset(0.0) {
    // Initialize with default position
    current_position.position = Point3D(0, 0, 0);
    current_position.rotation_azimuth = 0.0;
    current_position.rotation_elevation = 0.0;
    current_position.rotation_roll = 0.0;
    current_position.timestamp = GetSysTime();
    
    calibrated_reference = current_position;
}

HeadTracker::~HeadTracker() {
    // Cleanup
}

void HeadTracker::Calibrate(const HeadPosition& reference_pos) {
    calibrated_reference = reference_pos;
    is_calibrated = true;
}

Point3D HeadTracker::GetPositionOffset() const {
    Point3D offset;
    offset.x = current_position.position.x - calibrated_reference.position.x;
    offset.y = current_position.position.y - calibrated_reference.position.y;
    offset.z = current_position.position.z - calibrated_reference.position.z;
    
    return offset;
}

Matrix3D HeadTracker::GetRotationMatrix() const {
    // Create rotation matrix from Euler angles (azimuth, elevation, roll)
    Matrix3D rot;
    
    // Simplified implementation: return identity matrix
    // A full implementation would compute the proper rotation matrix
    rot.SetIdentity();
    
    return rot;
}

// SurroundMeterBridge implementation
SurroundMeterBridge::SurroundMeterBridge() : analysis_window(1024), analysis_overlap(0.5) {
    // Initialize with standard frequency bands
    frequency_bands.Add(100.0);   // LF
    frequency_bands.Add(300.0);   // Low-mid
    frequency_bands.Add(1000.0);  // Mid
    frequency_bands.Add(3000.0);  // High-mid
    frequency_bands.Add(10000.0); // HF
}

SurroundMeterBridge::~SurroundMeterBridge() {
    // Cleanup
}

SurroundMeterBridge::FieldAnalysis SurroundMeterBridge::AnalyzeSurroundField(
    const Vector<Vector<double>>& channel_inputs, double sample_rate) {
    
    FieldAnalysis analysis;
    
    // Calculate basic spatial parameters from multichannel input
    int channel_count = channel_inputs.GetCount();
    if (channel_count == 0) return analysis;
    
    // Calculate width based on L/R energy comparison
    if (channel_count >= 2) {
        analysis.width = CalculateWidth(channel_inputs);
    }
    
    // Calculate depth based on front/back energy comparison (if available)
    if (channel_count >= 6) {  // Assume 5.1 config has front and rear channels
        analysis.depth = CalculateDepth(channel_inputs);
    }
    
    // Calculate localization based on inter-channel coherence
    analysis.localization = CalculateSpaciousness(channel_inputs);
    
    // Front-rear, left-right, and top-bottom balances (simplified)
    if (channel_count >= 2) {
        double left_energy = 0.0, right_energy = 0.0;
        for (double sample : channel_inputs[0]) left_energy += sample * sample;
        for (double sample : channel_inputs[1]) right_energy += sample * sample;
        analysis.left_right_balance = (left_energy - right_energy) / (left_energy + right_energy + 1e-10);
    }
    
    analysis.timestamp = GetSysTime();
    
    current_analysis = analysis;
    return analysis;
}

double SurroundMeterBridge::CalculateWidth(const Vector<Vector<double>>& channels) const {
    if (channels.GetCount() < 2) return 0.0;
    
    // Simplified width calculation based on inter-channel differences
    double width_metric = 0.0;
    int common_length = min(channels[0].GetCount(), channels[1].GetCount());
    
    for (int i = 0; i < common_length; i++) {
        double sum = channels[0][i] + channels[1][i];
        double diff = channels[0][i] - channels[1][i];
        width_metric += abs(diff) / (abs(sum) + 1e-10); // Avoid division by zero
    }
    
    // Normalize and return value between 0 and 1
    return min(1.0, width_metric / common_length);
}

double SurroundMeterBridge::CalculateDepth(const Vector<Vector<double>>& channels) const {
    // Simplified depth calculation (front-rear based)
    if (channels.GetCount() < 6) return 0.0; // Need at least 5.1 for depth
    
    double front_energy = 0.0, rear_energy = 0.0;
    
    // Sum front channels (FL, FC, FR)
    for (int i = 0; i < 3; i++) {
        if (i < channels.GetCount()) {
            for (double sample : channels[i]) {
                front_energy += sample * sample;
            }
        }
    }
    
    // Sum rear channels (RL, RR)
    for (int i = 4; i < 6 && i < channels.GetCount(); i++) {
        for (double sample : channels[i]) {
            rear_energy += sample * sample;
        }
    }
    
    // Calculate depth as ratio of rear to total
    return rear_energy / (front_energy + rear_energy + 1e-10);
}

double SurroundMeterBridge::CalculateSpaciousness(const Vector<Vector<double>>& channels) const {
    // Simplified spaciousness calculation
    if (channels.GetCount() < 2) return 0.0;
    
    double spaciousness = 0.0;
    
    // Calculate inter-channel decorrelation
    int common_length = min(channels[0].GetCount(), channels[1].GetCount());
    double sum_product = 0.0;
    double left_energy = 0.0, right_energy = 0.0;
    
    for (int i = 0; i < common_length; i++) {
        sum_product += channels[0][i] * channels[1][i];
        left_energy += channels[0][i] * channels[0][i];
        right_energy += channels[1][i] * channels[1][i];
    }
    
    double coherence = abs(sum_product) / (sqrt(left_energy * right_energy) + 1e-10);
    spaciousness = 1.0 - coherence; // Less coherent = more spacious
    
    return min(1.0, max(0.0, spaciousness));
}

}