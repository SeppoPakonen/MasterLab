#ifndef _AudioCore_Synth_h_
#define _AudioCore_Synth_h_

// Note: Requires AudioCore/AudioCore.h for Upp core types and support classes.

namespace am {
namespace Synth {

struct VoiceHandle {
	int id = -1;
	int note = 0;
	double velocity = 0.0;
	bool active = false;
	bool releasing = false;
};

class VoiceManager {
public:
	VoiceManager();

	void Configure(int max_voices);
	VoiceHandle* NoteOn(int note, double velocity);
	void NoteOff(int note);
	void AllNotesOff();

	template <class Fn>
	void ForEachActive(Fn&& fn) {
		for(int i = 0; i < voices.GetCount(); ++i) {
			VoiceHandle& handle = voices[i];
			if(handle.active)
				fn(handle);
		}
	}

	int GetMaxVoices() const { return max_voices; }
	int GetActiveVoiceCount() const { return active_voice_count; }

private:
	int FindVoiceByNote(int note) const;
	int FindFreeVoice() const;

	Upp::Vector<VoiceHandle> voices;
	int max_voices = 0;
	int active_voice_count = 0;
	int next_id = 1;
};

// Modulation Matrix for Synth
class ModMatrix {
public:
	enum Source {
		LFO1,
		LFO2,
		ENVELOPE1,
		ENVELOPE2,
		KEY_TRACK,
		VELOCITY,
		AFTER_TOUCH,
		PITCH_BEND,
		CC_CONTROLLER,
		POLY_PRESSURE
	};
	
	enum Destination {
		FILTER_CUTOFF,
		OSC1_PITCH,
		OSC2_PITCH,
		OSC1_VOLUME,
		OSC2_VOLUME,
		LFO1_RATE,
		LFO2_RATE,
		AMP_LEVEL
	};
	
	struct Connection {
		Source source;
		Destination dest;
		double amount = 0.0;
		bool enabled = true;
	};
	
	ModMatrix();
	void AddConnection(const Connection& conn);
	void RemoveConnection(int index);
	void ClearConnections();
	void Process();
	
	void SetSourceValue(Source source, double value);
	double GetSourceValue(Source source) const;
	
private:
	Vector<Connection> connections;
	VectorMap<int, double> source_values; // Changed to use int as key instead of enum
};

// Envelope Bank - collection of envelopes
class EnvelopeBank {
public:
	enum EnvelopeType {
		ADSR,       // Attack, Decay, Sustain, Release
		FREQUENCY,  // Frequency envelope
		AMOUNT      // Generic amount envelope
	};
	
	struct EnvelopeParams {
		double attack = 0.01;    // seconds
		double decay = 0.3;      // seconds
		double sustain = 0.7;    // level (0-1)
		double release = 0.5;    // seconds
		double velocity_sens = 0.5; // velocity sensitivity
	};
	
	EnvelopeBank();
	~EnvelopeBank();
	
	void SetParameters(int env_index, const EnvelopeParams& params);
	void NoteOn(int env_index, double velocity = 1.0);
	void NoteOff(int env_index);
	void Process(int env_index, double* output, int sample_count);
	
	// Get current envelope value
	double GetLevel(int env_index) const;
	
private:
	struct EnvelopeState {
		EnvelopeParams params;
		enum State { ATTACK, DECAY, SUSTAIN, RELEASE, IDLE } state = IDLE;
		double level = 0.0;
		double target = 0.0;
		double rate = 0.0;
		double velocity = 1.0;
	};
	
	Vector<EnvelopeState> states;
};

// LFO Bank - collection of low frequency oscillators
class LFOBank {
public:
	enum Waveform {
		SINE,
		TRIANGLE,
		SQUARE,
		SAW_UP,
		SAW_DOWN,
		RANDOM
	};
	
	struct LFOParams {
		Waveform waveform = SINE;
		double rate = 2.0;        // Hz
		double depth = 1.0;       // 0-1
		double phase = 0.0;       // 0-1
		bool sync_to_tempo = false;
		double tempo_sync_value = 4.0; // e.g., 4 for quarter note
	};
	
	LFOBank();
	~LFOBank();
	
	void SetParameters(int lfo_index, const LFOParams& params);
	void Process(int lfo_index, double* output, int sample_count, double sample_rate);
	
private:
	struct LFOState {
		LFOParams params;
		double phase = 0.0;
	};
	
	Vector<LFOState> states;
};

// Wavetable Oscillator
class WavetableOsc {
public:
	WavetableOsc();
	~WavetableOsc();
	
	void SetWavetable(const Vector<Vector<double>>& wavetable);
	void SetFrequency(double freq);
	void SetPhase(double phase);
	void SetWavetablePosition(double position); // 0.0 to 1.0
	void Process(double* output, int sample_count, double sample_rate);
	
private:
	Vector<Vector<double>> wavetable;
	double frequency = 440.0;
	double phase = 0.0;
	double wavetable_position = 0.0;
};

// Virtual Analog Oscillator
class OscillatorVA {
public:
	enum Waveform {
		SINE,
		TRIANGLE,
		SQUARE,
		SAW_UP,
		SAW_DOWN,
		NOISE
	};
	
	OscillatorVA();
	~OscillatorVA();
	
	void SetWaveform(Waveform wf);
	void SetFrequency(double freq);
	void SetPulseWidth(double pw); // Only for square wave (0.0 to 1.0)
	void SetPhase(double phase);
	void Process(double* output, int sample_count, double sample_rate);
	
private:
	Waveform waveform = SINE;
	double frequency = 440.0;
	double pulse_width = 0.5;
	double phase = 0.0;
};

// Filter Cascade - multiple filters in series
class FilterCascade {
public:
	enum FilterType {
		LOW_PASS,
		HIGH_PASS,
		BAND_PASS,
		NOTCH,
		PEAK,
		LOW_SHELF,
		HIGH_SHELF
	};
	
	struct FilterParams {
		FilterType type = LOW_PASS;
		double cutoff = 1000.0;  // Hz
		double resonance = 0.7;   // Q factor
		double gain = 0.0;        // dB (for shelving/peaking)
	};
	
	FilterCascade();
	~FilterCascade();
	
	void SetFilterCount(int count);
	void SetFilterParams(int filter_index, const FilterParams& params);
	void Process(double* input_output, int sample_count, double sample_rate);
	
private:
	struct FilterState {
		FilterParams params;
		double x1 = 0.0, x2 = 0.0; // Input delay line
		double y1 = 0.0, y2 = 0.0; // Output delay line
		double a0 = 1.0, a1 = 0.0, a2 = 0.0; // Filter coefficients
		double b1 = 0.0, b2 = 0.0;
	};
	
	Vector<FilterState> filters;
};

// Unison Stack - for chorus-like effects
class UnisonStack {
public:
	UnisonStack();
	~UnisonStack();
	
	void SetVoiceCount(int count); // Number of unison voices
	void SetDetune(double detune); // Detune amount in cents
	void SetSpread(double spread); // Panning spread (0.0 to 1.0)
	void Process(const double* input, double* output, int sample_count, double sample_rate);
	
private:
	int voice_count = 3;
	double detune_cents = 10.0;
	double spread = 0.5;
	Vector<double> detune_offsets;
	Vector<double> pan_positions;
};

// Formant Shaper - shapes formants
class FormantShaper {
public:
	enum Vowel {
		A,
		E,
		I,
		O,
		U
	};
	
	FormantShaper();
	~FormantShaper();
	
	void SetVowel(Vowel v);
	void SetVowelByIndex(int index); // 0-4 for A-E-I-O-U
	void SetFormantShift(double shift); // -1.0 to 1.0, where 0 is neutral
	void Process(double* input_output, int sample_count, double sample_rate);
	
private:
	Vector<double> formant_frequencies; // Formant frequencies
	Vector<double> formant_gains;       // Formant gains
	double shift_amount = 0.0;
};

} // namespace Synth
} // namespace am

#endif
