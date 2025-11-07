#ifndef _AudioFX_DSP_h_
#define _AudioFX_DSP_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

namespace am {
namespace DSP {

// Forward declarations
class SignalBus;
class ParameterSet;
class ModMatrix;
class LatencyBuffer;
class Analyzer;
class PresetManager;

// SignalBus - handles audio signal routing between processing modules
class SignalBus {
public:
	SignalBus(int channels = 2, int max_samples = 8192);
	~SignalBus();
	
	void ResizeBuffers(int new_channels, int new_max_samples);
	void Clear();
	void MixTo(SignalBus& target, double gain = 1.0, int src_start = 0, int dest_start = 0, int sample_count = -1);
	void CopyTo(SignalBus& target, int src_start = 0, int dest_start = 0, int sample_count = -1);
	
	// Audio buffer access
	Vector<double*>& GetBuffers() { return buffers; }
	double* GetChannelBuffer(int channel) { return buffers[channel]; }
	const double* GetChannelBuffer(int channel) const { return buffers[channel]; }
	
	int GetChannelCount() const { return channel_count; }
	int GetMaxSamples() const { return max_samples; }
	
	void SetSampleRate(double rate) { sample_rate = rate; }
	double GetSampleRate() const { return sample_rate; }
	
private:
	Vector<double*> buffers;  // One buffer per channel
	int channel_count;
	int max_samples;
	double sample_rate = 44100.0;  // Default sample rate
};

// ParameterSet - manages a collection of audio parameters
class ParameterSet {
public:
	struct Parameter {
		String name;
		double value = 0.0;
		double min_value = 0.0;
		double max_value = 1.0;
		double default_value = 0.5;
		String unit;  // e.g., "dB", "Hz", "%"
		bool is_automatable = true;
		
		// UI display properties
		String display_name;
		int display_order = 0;
	};
	
	ParameterSet();
	void AddParameter(const String& id, const Parameter& param);
	void RemoveParameter(const String& id);
	
	void SetValue(const String& id, double value);
	double GetValue(const String& id) const;
	void SetNormalizedValue(const String& id, double normalized_value);  // 0.0 to 1.0
	double GetNormalizedValue(const String& id) const;  // 0.0 to 1.0
	
	const VectorMap<String, Parameter>& GetParameters() const { return parameters; }
	
private:
	VectorMap<String, Parameter> parameters;
};

// ModMatrix - modulation matrix for parameter modulation
class ModMatrix {
public:
	struct ModSource {
		enum Type {
			LFO1, LFO2, 
			ENVELOPE_FOLLOWER, 
			KEY_TRACK, 
			VELOCITY, 
			AFTER_TOUCH, 
			PITCH_BEND,
			CC_CONTROLLER,
			CUSTOM
		};
		
		Type type;
		String custom_name;
		double intensity = 1.0;
	};
	
	struct ModDestination {
		String parameter_id;  // ID in ParameterSet
		double amount = 0.0;  // Modulation amount
	};
	
	struct ModConnection {
		String source_id;      // Unique ID for the source
		ModSource source;
		String dest_id;        // Unique ID for the destination
		ModDestination dest;
		bool enabled = true;
	};
	
	ModMatrix();
	void AddConnection(const ModConnection& connection);
	void RemoveConnection(const String& source_id, const String& dest_id);
	
	void Process(FrameContext& ctx);  // Called during audio processing
	void SetSourceValue(const String& source_id, double value);
	double GetSourceValue(const String& source_id) const;
	
private:
	VectorMap<String, ModConnection> connections;
	VectorMap<String, double> source_values;
};

// LatencyBuffer - handles latency compensation
class LatencyBuffer {
public:
	LatencyBuffer();
	~LatencyBuffer();
	
	void SetLatency(int samples);
	int GetLatency() const { return latency_samples; }
	
	void Process(double** input, double** output, int channels, int sample_count);
	void Process(float** input, float** output, int channels, int sample_count);
	
private:
	void ResizeBuffers(int channels, int sample_count);
	
	Vector<Vector<double>> delay_buffers;  // One buffer per channel
	Vector<int> write_positions;          // Write position per channel
	int latency_samples = 0;
	int max_latency = 0;
};

// Analyzer - provides analysis services
class Analyzer {
public:
	enum Type {
		SPECTRUM,
		WAVEFORM,
		LEVEL_METER,
		PHASE_METER,
		THD_ANALYZER
	};
	
	Analyzer(Type type);
	~Analyzer();
	
	void Process(const double* const* input, int channels, int sample_count, double sample_rate);
	void Process(const float* const* input, int channels, int sample_count, double sample_rate);
	
	// Get analysis results
	Value GetResult();  // Returns appropriate analysis data based on Type
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	Type analyzer_type;
	Value results;  // Analysis results stored appropriately
	
	// Analysis-specific parameters
	VectorMap<String, double> parameters;
};

// PresetManager - manages presets with automation bridging
class PresetManager {
public:
	struct Preset {
		String name;
		String category;
		String description;
		ValueMap parameter_values;  // Parameter ID to value mapping
		ValueMap automation_data;   // Automation data if needed
	};
	
	PresetManager();
	~PresetManager();
	
	// Preset operations
	void AddPreset(const Preset& preset);
	void RemovePreset(const String& name);
	void ApplyPreset(const String& name, ParameterSet& params);
	void SavePreset(const String& name, const ParameterSet& params, const String& filepath);
	void LoadPreset(const String& name, ParameterSet& params, const String& filepath);
	
	Vector<String> GetPresetNames() const;
	Vector<String> GetPresetNamesByCategory(const String& category) const;
	
	// Automation bridging to UI::RackView - using void* to avoid circular dependency
	void RegisterAutomationBridge(void* rack_view);
	void UnregisterAutomationBridge(void* rack_view);
	void NotifyParameterChange(const String& param_id, double new_value);
	
private:
	VectorMap<String, Preset> presets;
	Vector<void*> rack_views;  // For automation bridging - using void* to avoid circular dependency
};

// VoiceFeatureExtractor - extracts features from voice signals
class VoiceFeatureExtractor {
public:
	enum FeatureType {
		PITCH,
		FORMANTS,
		SPECTRAL_CENTROID,
		ZERO_CROSSING_RATE,
		MFCC,  // Mel-Frequency Cepstral Coefficients
		CHROMA
	};
	
	VoiceFeatureExtractor();
	~VoiceFeatureExtractor();
	
	void Process(const double* input, int sample_count, double sample_rate);
	Value GetFeature(FeatureType type) const;
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	VectorMap<String, double> parameters;
	ValueMap features;  // FeatureType to extracted feature value
};

// HarmonyGenerator - generates harmonies based on input
class HarmonyGenerator {
public:
	enum HarmonyMode {
		CHORD_FOLLOWING,
		INTELLIGENT_VOICING,
		FIXED_INTERVAL
	};
	
	HarmonyGenerator();
	~HarmonyGenerator();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetHarmonyMode(HarmonyMode mode);
	void SetInterval(int semitones);  // For FIXED_INTERVAL mode
	void SetChord(const String& chord);  // For CHORD_FOLLOWING mode
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	HarmonyMode mode = CHORD_FOLLOWING;
	int interval = 7;  // Fifth by default
	String chord = "C";
	VectorMap<String, double> parameters;
};

// StyleTransferNet - neural network for style transfer
class StyleTransferNet {
public:
	enum StyleType {
		VOCAL_STYLE,
		INSTRUMENT_STYLE,
		REVERB_STYLE,
		COMPRESSION_STYLE
	};
	
	StyleTransferNet();
	~StyleTransferNet();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetStyle(StyleType type, const String& style_name);
	void Train(const Vector<double*>& training_data, int data_count);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	StyleType style_type = VOCAL_STYLE;
	String style_name = "Pop";
	VectorMap<String, double> parameters;
};

// VoiceEncoder/Decoder - for voice processing and encoding
class VoiceEncoder {
public:
	enum EncodingType {
		LPC,  // Linear Predictive Coding
		CEPSTRAL,
		FORMANT_BASED
	};
	
	VoiceEncoder();
	~VoiceEncoder();
	
	int Encode(const double* input, int sample_count, double sample_rate, void* output_buffer, int buffer_size);
	void SetEncodingType(EncodingType type);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	EncodingType encoding_type = LPC;
	VectorMap<String, double> parameters;
};

class VoiceDecoder {
public:
	VoiceDecoder();
	~VoiceDecoder();
	
	int Decode(const void* input_buffer, int buffer_size, double* output, int max_samples, double sample_rate);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	VectorMap<String, double> parameters;
};

// FormantMorpher - morphs formants between different vocal characteristics
class FormantMorpher {
public:
	enum MorphType {
		PRESERVE_TIMBRE,
		PRESERVE_PITCH,
		BALANCED
	};
	
	FormantMorpher();
	~FormantMorpher();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetMorphTarget(const String& target_name);  // e.g., "male", "female", "child"
	void SetMorphType(MorphType type);
	void SetAmount(double amount);  // 0.0 to 1.0
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	String morph_target = "neutral";
	MorphType morph_type = BALANCED;
	double amount = 0.5;  // Default to 50% morph
	VectorMap<String, double> parameters;
};

// LUFSMeter - measures loudness according to LUFS standard
class LUFSMeter {
public:
	enum MeterMode {
		MOMENTARY,   // 400ms window
		SHORT_TERM,  // 3s window
		INTEGRATED,  // Full program
		QUASI_PEAK   // Quasi-peak measurement
	};
	
	LUFSMeter();
	~LUFSMeter();
	
	void Process(const double* input, int sample_count, double sample_rate);
	double GetLoudness(MeterMode mode) const;
	
	// Get integrated loudness statistics
	double GetIntegratedLoudness() const;
	double GetRange() const;  // Loudness range
	double GetTruePeak() const;
	double GetMaxMomentary() const;
	double GetMaxShortTerm() const;
	
	void Reset();
	
private:
	double integrated_loudness = -70.0;  // Default low value
	double range = 0.0;
	double true_peak = 0.0;
	double max_momentary = -70.0;
	double max_short_term = -70.0;
	
	// Internal processing buffers
	Vector<double> momentary_buffer;   // 400ms window
	Vector<double> short_term_buffer;  // 3s window
	int momentary_pos = 0;
	int short_term_pos = 0;
	int sample_rate = 44100;
};

// ISPDetector - inter-sample peak detector
class ISPDetector {
public:
	ISPDetector();
	~ISPDetector();
	
	void Process(const double* input, int sample_count, double sample_rate);
	double GetISP() const;  // Get inter-sample peak value
	bool HasClipping() const;
	
	void Reset();
	
private:
	double max_isp = 0.0;
	bool has_clipping = false;
};

// AutoGainScheduler - automatic gain control
class AutoGainScheduler {
public:
	AutoGainScheduler();
	~AutoGainScheduler();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetTargetLoudness(double lufs);  // Target loudness in LUFS
	void SetAttackTime(double ms);
	void SetReleaseTime(double ms);
	
	double GetAppliedGain() const;
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	double target_loudness = -16.0;  // Default -16 LUFS
	double attack_time_ms = 10.0;
	double release_time_ms = 100.0;
	double current_gain = 1.0;
	VectorMap<String, double> parameters;
};

// MasterAssistant - intelligent mastering assistant
class MasterAssistant {
public:
	enum MasterMode {
		REFERENCE_BASED,
		PRESET_BASED,
		LIVE_ADJUST
	};
	
	MasterAssistant();
	~MasterAssistant();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetMasterMode(MasterMode mode);
	void SetReferenceTrack(const String& track_name);  // For REFERENCE_BASED mode
	void SetPreset(const String& preset_name);         // For PRESET_BASED mode
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	MasterMode mode = PRESET_BASED;
	String reference_track;
	String preset_name = "Balanced";
	VectorMap<String, double> parameters;
};

// Stabilizer - dynamic range stabilizer
class Stabilizer {
public:
	Stabilizer();
	~Stabilizer();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetThreshold(double db);
	void SetRatio(double ratio);
	void SetKnee(double db);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	double threshold_db = -12.0;
	double ratio = 2.0;
	double knee_db = 2.0;
	VectorMap<String, double> parameters;
};

// ImpactShaper - impact and transience shaper
class ImpactShaper {
public:
	enum ShapeMode {
		ATTACK_ENHANCE,
		DECAY_CONTROL,
		TRANSIENT_SHAPER
	};
	
	ImpactShaper();
	~ImpactShaper();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetShapeMode(ShapeMode mode);
	void SetAmount(double amount);  // 0.0 to 1.0
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	ShapeMode mode = ATTACK_ENHANCE;
	double amount = 0.5;
	VectorMap<String, double> parameters;
};

// PriorityAllocator - frequency band priority allocator
class PriorityAllocator {
public:
	PriorityAllocator();
	~PriorityAllocator();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void SetPriorityBand(int band_index, double priority);  // 0.0 to 1.0
	void SetCrossoverFrequencies(const Vector<double>& freqs);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	Vector<double> band_priorities;
	Vector<double> crossover_freqs;
	VectorMap<String, double> parameters;
};

// DitherEngine - dithering engine for bit depth reduction
class DitherEngine {
public:
	enum DitherType {
		RECTANGULAR,
		TRIANGULAR,
		SHIBATA,
		POWERSUM
	};
	
	DitherEngine();
	~DitherEngine();
	
	void Process(float* samples, int count, int source_bits, int target_bits);
	void SetDitherType(DitherType type);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	DitherType dither_type = SHIBATA;
	VectorMap<String, double> parameters;
};

// MotionSequencer - creates evolving parameter sequences
class MotionSequencer {
public:
	struct Step {
		double value = 0.0;
		double duration = 0.25;  // In beats
		bool active = true;
	};
	
	MotionSequencer();
	~MotionSequencer();
	
	void Process(FrameContext& ctx);
	void SetSteps(const Vector<Step>& steps);
	void SetTempo(double bpm);
	void SetPlaybackRate(double rate);  // 1.0 = normal, 0.5 = half speed, etc.
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	Vector<Step> steps;
	double tempo_bpm = 120.0;
	double playback_rate = 1.0;
	int current_step = 0;
	double step_progress = 0.0;
	VectorMap<String, double> parameters;
};

// SceneMorph - morphs between different parameter scenes
class SceneMorph {
public:
	struct Scene : public Upp::Moveable<Scene> {
		String name;
		ValueMap parameters;  // Parameter ID to value mapping
		
		typedef Scene CLASSNAME;  // Make this struct compatible with U++ containers
	};
	
	SceneMorph();
	~SceneMorph();
	
	void Process(FrameContext& ctx);
	void AddScene(const Scene& scene);
	void SetCurrentScene(int scene_index);
	void SetMorphAmount(double amount);  // 0.0 to 1.0 between current and next scene
	void SetCrossfadeEnabled(bool enabled);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	Vector<Scene> scenes;
	int current_scene = 0;
	double morph_amount = 0.0;
	bool crossfade_enabled = false;
	VectorMap<String, double> parameters;
};



// StepSequencer - classic step sequencer
class StepSequencer {
public:
	enum GateMode {
		TRIGGER,
		GATE,
		CONTINUOUS
	};
	
	StepSequencer();
	~StepSequencer();
	
	void Process(FrameContext& ctx);
	void SetStep(int index, double value, bool gate = true);
	void SetGateMode(GateMode mode);
	void SetTempo(double bpm);
	void SetSteps(int count);
	void SetOctave(int octave_offset);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	Vector<double> step_values;
	Vector<bool> step_gates;
	GateMode gate_mode = TRIGGER;
	double tempo_bpm = 120.0;
	int total_steps = 16;
	int current_step = 0;
	int octave_offset = 0;
	VectorMap<String, double> parameters;
};

// ModuleSwitcher - switches between different processing modules
class ModuleSwitcher {
public:
	enum SwitchMode {
		TOGGLE,
		CYCLE,
		SELECT
	};
	
	ModuleSwitcher();
	~ModuleSwitcher();
	
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	void AddModule(const String& name, Function<void(const double*, double*, int, double)> processor);
	void SetCurrentModule(int index);
	void SetCurrentModule(const String& name);
	void SetSwitchMode(SwitchMode mode);
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	Vector<String> module_names;
	Vector<Function<void(const double*, double*, int, double)>> processors;
	int current_module = 0;
	SwitchMode switch_mode = TOGGLE;
	VectorMap<String, double> parameters;
};

// MacroController - high-level parameter controller
class MacroController {
public:
	struct MacroParameter : public Upp::Moveable<MacroParameter> {
		String parameter_id;
		double min_value = 0.0;
		double max_value = 1.0;
		double default_value = 0.5;
		double current_value = 0.5;
		
		typedef MacroParameter CLASSNAME;  // Make this struct compatible with U++ containers
	};
	
	MacroController();
	~MacroController();
	
	void Process(FrameContext& ctx);
	void AddParameter(const String& macro_name, const MacroParameter& param);
	void SetMacroValue(const String& macro_name, double value);
	double GetMacroValue(const String& macro_name) const;
	
	void SetParameter(const String& name, double value);
	double GetParameter(const String& name) const;
	
private:
	VectorMap<String, Vector<MacroParameter>> macro_params;
	VectorMap<String, double> macro_values;
	VectorMap<String, double> parameters;
};



}  // namespace DSP
}  // namespace am



// UI namespace forward declarations for UI::RackView
namespace am {
namespace UI {
	class RackView;
	class SceneManager;
	class XYPAD;
}
}

#endif