#ifndef _DSP_VocalProcessing_h_
#define _DSP_VocalProcessing_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

// Voice feature extraction (pitch, formants, spectral flux)
struct VoiceFeatures {
    double pitch;                    // Fundamental frequency in Hz
    Upp::Vector<double> formants;         // Formant frequencies in Hz
    double spectral_flux;           // Measure of spectral change
    double voicing;                 // Voiced/unvoiced probability
    
    VoiceFeatures() : pitch(0.0), spectral_flux(0.0), voicing(0.0) {}
};

class VoiceFeatureExtractor {
public:
    typedef VoiceFeatureExtractor CLASSNAME;
    
    VoiceFeatureExtractor();
    virtual ~VoiceFeatureExtractor();
    
    // Analyze a block of audio to extract voice features
    VoiceFeatures AnalyzeBlock(const BufferView& input);
    
    // Get the latest pitch track
    double GetPitchTrack() const { return last_pitch; }
    
    // Get formant profile
    const Upp::Vector<double>& GetFormantProfile() const { return last_formants; }
    
    // Configure analysis parameters
    void Configure(int sample_rate, int fft_size);
    
private:
    int sample_rate;
    int fft_size;
    double last_pitch;
    Upp::Vector<double> last_formants;
    double last_spectral_flux;
    
    // Helper methods for feature extraction
    double ExtractPitch(const BufferView& input);
    Upp::Vector<double> ExtractFormants(const BufferView& input);
    double CalculateSpectralFlux(const BufferView& input);
};

// Harmony generation (generates detuned/delayed harmonies)
struct HarmonySetup {
    Upp::Vector<int> intervals;      // Harmonic intervals in semitones
    Upp::Vector<double> volumes;     // Volume levels for each harmony
    Upp::Vector<double> detunes;     // Detune amounts in cents
    Upp::Vector<double> delays;      // Delay amounts in milliseconds
    
    HarmonySetup() {}
};

class HarmonyGenerator {
public:
    typedef HarmonyGenerator CLASSNAME;
    
    HarmonyGenerator();
    virtual ~HarmonyGenerator();
    
    // Generate harmonies based on the input and setup
    BufferView RenderVoices(const BufferView& input, const HarmonySetup& setup);
    
    // Configure the harmony generator
    void Configure(int sample_rate);
    
private:
    int sample_rate;
    Upp::Vector<BufferView> harmony_buffers;  // Buffers for each harmony voice
    
    // Helper methods
    BufferView GenerateHarmonyVoice(const BufferView& input, int interval, double volume, 
                                   double detune, double delay);
};

// Neural style transfer network wrapper
class StyleTransferNet {
public:
    typedef StyleTransferNet CLASSNAME;
    
    StyleTransferNet();
    virtual ~StyleTransferNet();
    
    // Load a neural model for style transfer
    bool LoadModel(const Upp::String& model_path);
    
    // Process a frame of audio through the style transfer network
    BufferView ProcessFrame(const BufferView& input);
    
    // Check if a model is loaded
    bool IsModelLoaded() const { return !model_path.IsEmpty(); }
    
    // Get model information
    Upp::String GetModelInfo() const { return model_path; }
    
private:
    Upp::String model_path;
    bool model_loaded;
    
    // In a real implementation, this would contain neural network runtime objects
};

// Formant morpher (applies vocal tract length transformations)
class FormantMorpher {
public:
    typedef FormantMorpher CLASSNAME;
    
    FormantMorpher();
    virtual ~FormantMorpher();
    
    // Configure morph targets
    void ConfigureTargets(const Upp::Vector<double>& source_formants, 
                         const Upp::Vector<double>& target_formants);
    
    // Process audio with formant morphing
    BufferView Process(const BufferView& input);
    
    // Set morph amount (0.0 = no morph, 1.0 = full morph)
    void SetMorphAmount(double amount) { morph_amount = Upp::max(0.0, Upp::min(1.0, amount)); }
    double GetMorphAmount() const { return morph_amount; }
    
private:
    Upp::Vector<double> source_formants;
    Upp::Vector<double> target_formants;
    double morph_amount;
    
    // Helper methods
    BufferView ApplyFormantShift(const BufferView& input);
};

// Voice encoder (neural codec for voice conversion)
class VoiceEncoder {
public:
    typedef VoiceEncoder CLASSNAME;
    
    VoiceEncoder();
    virtual ~VoiceEncoder();
    
    // Encode audio to latent representation
    BufferView Encode(const BufferView& input);
    
    // Configure encoder parameters
    void Configure(int sample_rate);
    
private:
    int sample_rate;
    
    // In a real implementation, this would contain neural encoder objects
    BufferView latent_representation;
};

// Voice decoder (neural codec for voice conversion)
class VoiceDecoder {
public:
    typedef VoiceDecoder CLASSNAME;
    
    VoiceDecoder();
    virtual ~VoiceDecoder();
    
    // Decode from latent representation to audio
    BufferView Decode(const BufferView& latent);
    
    // Configure decoder parameters
    void Configure(int sample_rate);
    
private:
    int sample_rate;
    
    // In a real implementation, this would contain neural decoder objects
};

}

#endif