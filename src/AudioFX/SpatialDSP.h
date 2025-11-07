#ifndef _AudioFX_SpatialDSP_h_
#define _AudioFX_SpatialDSP_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
#include <DSP/DSP.h>
#include <Devices/Calibration.h>

using namespace Upp;

// 3D Point structure for spatial audio processing
struct Point3D {
    double x, y, z;
    
    Point3D() : x(0.0), y(0.0), z(0.0) {}
    Point3D(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {}
};

// 3x3 Matrix structure for spatial audio processing
struct Matrix3D {
    double m[3][3];
    
    Matrix3D() {
        // Initialize as identity matrix
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }
    
    void SetIdentity() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }
};

namespace DSP {

// FIRDesigner - designs Finite Impulse Response filters for spatial processing
class FIRDesigner {
public:
    typedef FIRDesigner CLASSNAME;
    
    FIRDesigner();
    virtual ~FIRDesigner();
    
    // Design FIR filter using windowing method
    Vector<double> DesignWindowedFilter(int filter_length, 
                                      const Vector<double>& frequency_response,
                                      const Vector<double>& frequency_points);
    
    // Design FIR filter using Parks-McClellan algorithm (remez exchange)
    Vector<double> DesignParksMcClellan(int filter_length,
                                      const Vector<double>& bands,
                                      const Vector<double>& desired,
                                      const Vector<double>& weights);
    
    // Design low-pass/high-pass/band-pass/band-stop FIR filters
    Vector<double> DesignLowPass(int filter_length, double cutoff_freq, double sample_rate);
    Vector<double> DesignHighPass(int filter_length, double cutoff_freq, double sample_rate);
    Vector<double> DesignBandPass(int filter_length, double low_freq, double high_freq, double sample_rate);
    Vector<double> DesignBandStop(int filter_length, double low_freq, double high_freq, double sample_rate);
    
    // Design FIR filter for crossover networks
    Vector<double> DesignCrossoverFilter(int filter_length, 
                                       double crossover_freq, 
                                       double sample_rate, 
                                       int order = 2);
    
    // Apply designed filter to signal
    void ApplyFilter(const Vector<double>& input, 
                    Vector<double>& output,
                    const Vector<double>& filter_coeffs);
    
    // Set design parameters
    void SetWindowType(int type) { window_type = type; } // 0=rectangular, 1=hamming, 2=hann, 3=blackman
    void SetRipple(double db) { ripple_db = db; }
    void SetTransitionBandwidth(double hz) { transition_bw = hz; }
    
private:
    int window_type;          // Window type for windowed filter design
    double ripple_db;         // Ripple in passband (for Parks-McClellan)
    double transition_bw;     // Transition bandwidth (Hz)
    
    // Apply window to ideal impulse response
    Vector<double> ApplyWindow(const Vector<double>& ideal_impulse, int window_type);
    double WindowValue(int n, int length, int window_type);
};

// IIRDesigner - designs Infinite Impulse Response filters for spatial processing
class IIRDesigner {
public:
    typedef IIRDesigner CLASSNAME;
    
    IIRDesigner();
    virtual ~IIRDesigner();
    
    struct IIRCoefficients : public Upp::Moveable<IIRCoefficients> {
        Vector<double> b; // Feedforward coefficients
        Vector<double> a; // Feedback coefficients
        double gain = 1.0; // Overall gain factor
        
        typedef IIRCoefficients CLASSNAME;  // Make this struct compatible with U++ containers
        
        // Proper constructors for U++ compatibility
        IIRCoefficients() : gain(1.0) {}
        
        // Copy constructor using U++ deep copy operator
        IIRCoefficients(const IIRCoefficients& other) : b(), a(), gain(other.gain) {
            b <<= other.b;
            a <<= other.a;
        }
        
        // Assignment operator
        IIRCoefficients& operator=(const IIRCoefficients& other) {
            if (this != &other) {
                gain = other.gain;
                b <<= other.b;
                a <<= other.a;
            }
            return *this;
        }
        
        // Move constructor
        IIRCoefficients(IIRCoefficients&& other) : b(pick(other.b)), a(pick(other.a)), gain(other.gain) {}
        
        // Move assignment operator
        IIRCoefficients& operator=(IIRCoefficients&& other) {
            if (this != &other) {
                b = pick(other.b);
                a = pick(other.a);
                gain = other.gain;
            }
            return *this;
        }
    };
    
    // Design Butterworth filter
    IIRCoefficients DesignButterworth(int order, double cutoff_freq, double sample_rate, bool highpass = false);
    
    // Design Chebyshev Type I filter
    IIRCoefficients DesignChebyshevI(int order, double ripple_db, double cutoff_freq, double sample_rate, bool highpass = false);
    
    // Design Chebyshev Type II filter
    IIRCoefficients DesignChebyshevII(int order, double stopband_atten_db, double cutoff_freq, double sample_rate, bool highpass = false);
    
    // Design Elliptic (Cauer) filter
    IIRCoefficients DesignElliptic(int order, double passband_ripple_db, double stopband_atten_db, 
                                 double cutoff_freq, double sample_rate, bool highpass = false);
    
    // Design Linkwitz-Riley crossover (linear phase)
    Vector<IIRCoefficients> DesignLinkwitzRileyCrossover(int order, double crossover_freq, double sample_rate);
    
    // Apply IIR filter to signal (direct form II transposed)
    void ApplyFilter(const Vector<double>& input,
                    Vector<double>& output,
                    const IIRCoefficients& coeffs);
    
    // Get group delay of filter
    Vector<double> GetGroupDelay(const IIRCoefficients& coeffs, int num_points = 1024);
    
private:
    // Bilinear transform methods
    IIRCoefficients BilinearTransform(const Vector<double>& zeros, 
                                    const Vector<double>& poles, 
                                    double gain, 
                                    double sample_rate, 
                                    double warped_freq = -1.0);
    
    // Convert analog filter prototype to digital
    IIRCoefficients ConvertAnalogToDigital(Vector<Complex> zeros, 
                                         Vector<Complex> poles, 
                                         double gain, 
                                         double sample_rate);
};



// AmbisonicsEncoder - encodes audio signals to ambisonics format
class AmbisonicsEncoder {
public:
    typedef AmbisonicsEncoder CLASSNAME;
    
    AmbisonicsEncoder();
    virtual ~AmbisonicsEncoder();
    
    enum Order {
        FIRST_ORDER = 1,    // W, X, Y, Z
        SECOND_ORDER = 2,   // + R, S, T, U, V
        THIRD_ORDER = 3     // + K, L, M, N, O, P, Q
    };
    
    // Encode a point source to ambisonics format
    Vector<double> EncodePointSource(double azimuth, double elevation, double distance = 1.0, Order order = FIRST_ORDER);
    
    // Encode stereo to ambisonics (stereo upmixing)
    Vector<Vector<double>> EncodeStereoToAmbisonics(const Vector<double>& left, 
                                                   const Vector<double>& right,
                                                   Order order = FIRST_ORDER);
    
    // Encode 5.1 to ambisonics
    Vector<Vector<double>> Encode51ToAmbisonics(const Vector<double>& front_left,
                                               const Vector<double>& front_right,
                                               const Vector<double>& center,
                                               const Vector<double>& lfe,
                                               const Vector<double>& rear_left,
                                               const Vector<double>& rear_right,
                                               Order order = FIRST_ORDER);
    
    // Encode arbitrary speaker arrangement to ambisonics
    Vector<Vector<double>> EncodeSpeakerArray(const Vector<Vector<double>>& speaker_signals,
                                             const Vector<Point>& speaker_positions, // x, y, z coordinates
                                             Order order = FIRST_ORDER);
    
    // Set encoding parameters
    void SetDistanceAttenuation(bool enabled) { distance_attenuation = enabled; }
    void SetNearFieldEffect(bool enabled) { near_field_effect = enabled; }
    void SetOrder(Order order) { this->order = order; }
    
    // Get number of ambisonic channels for order
    int GetChannelCount(Order order) const;
    
private:
    bool distance_attenuation;
    bool near_field_effect;
    Order order;
    double reference_distance;
    
    // Internal encoding functions
    double CalculateDistanceGain(double distance) const;
    Complex CalculateNearFieldEffect(double distance, double freq) const;
};

// BinauralRenderer - processes audio using Head-Related Transfer Functions
class BinauralRenderer {
public:
    typedef BinauralRenderer CLASSNAME;
    
    BinauralRenderer();
    virtual ~BinauralRenderer();
    
    // Load HRTF data
    bool LoadHRTFDatabase(const String& database_path);
    void SetHRTFData(const Vector<BufferView>& hrir_database);  // Head-Related Impulse Responses
    
    // Render audio to binaural output
    void RenderBinaural(const Vector<double>& input, 
                       Vector<double>& left_output, 
                       Vector<double>& right_output,
                       double azimuth, double elevation, double distance = 1.0);
    
    // Render multiple sources to binaural output
    struct AudioSource {
        Vector<double> signal;
        double azimuth;
        double elevation;
        double distance;
        double gain;
    };
    
    void RenderMultipleSources(const Vector<AudioSource>& sources,
                              Vector<double>& left_output,
                              Vector<double>& right_output);
    
    // Set interpolation method for HRTF selection
    void SetInterpolationMethod(int method) { interp_method = method; }  // 0=nearest, 1=linear, 2=bilinear
    
    // Set processing parameters
    void SetCrossfeedEnabled(bool enabled) { crossfeed_enabled = enabled; }
    void SetPinnaSimulation(bool enabled) { pinna_simulation = enabled; }
    
private:
    Vector<BufferView> hrir_data;  // HRTF impulse responses
    bool crossfeed_enabled;
    bool pinna_simulation;
    int interp_method;
    
    // Internal processing
    void ApplyHRIR(const Vector<double>& input,
                   Vector<double>& output,
                   const BufferView& hrir);
    
    // Get appropriate HRTF for position
    int GetHRIRIndex(double azimuth, double elevation) const;
};

// HeadTracker - tracks head position/orientation for spatial rendering
class HeadTracker {
public:
    typedef HeadTracker CLASSNAME;
    
    HeadTracker();
    virtual ~HeadTracker();
    
    struct HeadPosition {
        Point3D position;     // x, y, z coordinates
        double rotation_azimuth;   // yaw (around y-axis)
        double rotation_elevation; // pitch (around x-axis) 
        double rotation_roll;      // roll (around z-axis)
        Time timestamp;
    };
    
    // Get current head position
    HeadPosition GetHeadPosition() const { return current_position; }
    
    // Update head position (from sensors, VR controllers, etc.)
    void SetHeadPosition(const HeadPosition& pos) { current_position = pos; }
    
    // Simulate head movement for testing
    void SimulateMovement(double azimuth_offset, double elevation_offset, double distance_offset = 0.0);
    
    // Calibrate tracker
    void Calibrate(const HeadPosition& reference_pos);
    
    // Reset to calibrated position
    void ResetToCalibrated();
    
    // Get transformation matrices for applying to spatial audio
    Matrix3D GetRotationMatrix() const;
    Point3D GetPositionOffset() const;
    
private:
    HeadPosition current_position;
    HeadPosition calibrated_reference;
    bool is_calibrated;
    
    // Movement simulation
    double sim_azimuth_offset;
    double sim_elevation_offset;
    double sim_distance_offset;
};

// SurroundMeterBridge - measures surround field parameters
class SurroundMeterBridge {
public:
    typedef SurroundMeterBridge CLASSNAME;
    
    SurroundMeterBridge();
    virtual ~SurroundMeterBridge();
    
    struct FieldAnalysis {
        double width;           // Perceived width (0.0-1.0)
        double depth;           // Perceived depth (0.0-1.0)
        double height;          // Perceived height (0.0-1.0)
        double envelopment;     // Spatial envelopment (0.0-1.0)
        double spaciousness;    // Spaciousness (0.0-1.0)
        double localization;    // Directional localization quality (0.0-1.0)
        double front_rear_balance; // Front-rear balance (-1.0 to 1.0)
        double left_right_balance; // Left-right balance (-1.0 to 1.0)
        double top_bottom_balance; // Top-bottom balance (-1.0 to 1.0)
        Time timestamp;         // Time of analysis
    };
    
    // Analyze multichannel input for spatial parameters
    FieldAnalysis AnalyzeSurroundField(const Vector<Vector<double>>& channel_inputs,
                                     double sample_rate);
    
    // Analyze stereo input for pseudo-surround parameters
    FieldAnalysis AnalyzeStereoForSurround(const Vector<double>& left,
                                          const Vector<double>& right,
                                          double sample_rate);
    
    // Set analysis parameters
    void SetAnalysisWindow(int samples) { analysis_window = samples; }
    void SetAnalysisOverlap(double ratio) { analysis_overlap = ratio; }
    void SetFrequencyBands(const Vector<double>& bands) { frequency_bands <<= bands; }
    
    // Get current analysis
    const FieldAnalysis& GetCurrentAnalysis() const { return current_analysis; }
    
private:
    FieldAnalysis current_analysis;
    int analysis_window;
    double analysis_overlap;
    Vector<double> frequency_bands;
    
    // Internal analysis methods
    double CalculateWidth(const Vector<Vector<double>>& channels) const;
    double CalculateDepth(const Vector<Vector<double>>& channels) const;
    double CalculateEnvelopment(const Vector<Vector<double>>& channels) const;
    double CalculateSpaciousness(const Vector<Vector<double>>& channels) const;
};

}

#endif