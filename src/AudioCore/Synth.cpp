#include "AudioCore.h"

namespace am {
namespace Synth {

VoiceManager::VoiceManager() {
}

void VoiceManager::Configure(int max_voices_) {
	max_voices = Upp::clamp(max_voices_, 1, 256);
	voices.SetCount(max_voices);
	next_id = 1;
	for(int i = 0; i < voices.GetCount(); ++i) {
		voices[i] = VoiceHandle();
		voices[i].id = next_id++;
	}
	active_voice_count = 0;
}

VoiceHandle* VoiceManager::NoteOn(int note, double velocity) {
	if(max_voices <= 0) {
		return nullptr;
	}

	int voice_index = FindVoiceByNote(note);
	if(voice_index < 0)
		voice_index = FindFreeVoice();

	if(voice_index < 0)
		return nullptr;

	VoiceHandle& handle = voices[voice_index];
	handle.note = note;
	handle.velocity = Upp::clamp(velocity, 0.0, 1.0);
	if(!handle.active) {
		handle.active = true;
		handle.releasing = false;
		++active_voice_count;
	}
	return &handle;
}

void VoiceManager::NoteOff(int note) {
	int voice_index = FindVoiceByNote(note);
	if(voice_index < 0)
		return;

	VoiceHandle& handle = voices[voice_index];
	if(handle.active) {
		handle.active = false;
		handle.releasing = true;
		if(active_voice_count > 0)
			--active_voice_count;
	}
}

void VoiceManager::AllNotesOff() {
	for(VoiceHandle& handle : voices) {
		handle.active = false;
		handle.releasing = false;
	}
	active_voice_count = 0;
}

int VoiceManager::FindVoiceByNote(int note) const {
	for(int i = 0; i < voices.GetCount(); ++i) {
		if(voices[i].active && voices[i].note == note)
			return i;
	}
	return -1;
}

int VoiceManager::FindFreeVoice() const {
	for(int i = 0; i < voices.GetCount(); ++i) {
		if(!voices[i].active)
			return i;
	}
	return -1;
}

// ModMatrix implementation
ModMatrix::ModMatrix() {
	// Initialize with default source values
	// Initialize all source values to 0.0
	for(int i = 0; i < 10; i++) { // 10 sources defined
		source_values.GetAdd(i) = 0.0;
	}
}

void ModMatrix::AddConnection(const Connection& conn) {
	connections.Add(conn);
}

void ModMatrix::RemoveConnection(int index) {
	if(index >= 0 && index < connections.GetCount()) {
		connections.Remove(index);
	}
}

void ModMatrix::ClearConnections() {
	connections.Clear();
}

void ModMatrix::Process() {
	// Process all modulation connections
	for(auto& conn : connections) {
		if(conn.enabled) {
			double source_val = source_values.Get((int)conn.source, 0.0);
			// Apply modulation to destination (this would interface with synth parameters)
		}
	}
}

void ModMatrix::SetSourceValue(Source source, double value) {
	source_values.GetAdd((int)source) = value;
}

double ModMatrix::GetSourceValue(Source source) const {
	return source_values.Get((int)source, 0.0);
}

// EnvelopeBank implementation
EnvelopeBank::EnvelopeBank() {
	// Initialize with 4 envelopes by default
	states.SetCount(4);
}

EnvelopeBank::~EnvelopeBank() {
	// Destructor implementation
}

void EnvelopeBank::SetParameters(int env_index, const EnvelopeParams& params) {
	if(env_index >= 0 && env_index < states.GetCount()) {
		states[env_index].params = params;
	}
}

void EnvelopeBank::NoteOn(int env_index, double velocity) {
	if(env_index >= 0 && env_index < states.GetCount()) {
		auto& state = states[env_index];
		state.velocity = velocity;
		state.state = EnvelopeState::ATTACK;
		state.level = 0.0;
		// Calculate rate for attack phase
		if(state.params.attack > 0.001) { // Avoid division by zero
			state.rate = 1.0 / (state.params.attack * 44100.0 / 1000.0); // Normalize to sample rate
		} else {
			state.rate = 1.0; // Instant attack
		}
	}
}

void EnvelopeBank::NoteOff(int env_index) {
	if(env_index >= 0 && env_index < states.GetCount()) {
		auto& state = states[env_index];
		state.state = EnvelopeState::RELEASE;
		// Calculate rate for release phase
		if(state.params.release > 0.001) { // Avoid division by zero
			state.rate = 1.0 / (state.params.release * 44100.0 / 1000.0); // Normalize to sample rate
		} else {
			state.rate = 1.0; // Instant release
		}
	}
}

void EnvelopeBank::Process(int env_index, double* output, int sample_count) {
	if(env_index >= 0 && env_index < states.GetCount()) {
		auto& state = states[env_index];
		
		for(int i = 0; i < sample_count; i++) {
			switch(state.state) {
				case EnvelopeState::ATTACK:
					state.level += state.rate;
					if(state.level >= 1.0) {
						state.level = 1.0;
						state.state = EnvelopeState::DECAY;
						// Calculate rate for decay phase
						if(state.params.decay > 0.001) {
							state.rate = 1.0 / (state.params.decay * 44100.0 / 1000.0);
						} else {
							state.level = state.params.sustain;
							state.state = EnvelopeState::SUSTAIN;
						}
					}
					break;
					
				case EnvelopeState::DECAY:
					state.level -= state.rate;
					if(state.level <= state.params.sustain) {
						state.level = state.params.sustain;
						state.state = EnvelopeState::SUSTAIN;
					}
					break;
					
				case EnvelopeState::SUSTAIN:
					// Level stays at sustain
					break;
					
				case EnvelopeState::RELEASE:
					state.level -= state.rate;
					if(state.level <= 0.0) {
						state.level = 0.0;
						state.state = EnvelopeState::IDLE;
					}
					break;
					
				case EnvelopeState::IDLE:
					// Level stays at 0
					state.level = 0.0;
					break;
			}
			
			output[i] = state.level;
		}
	}
}

double EnvelopeBank::GetLevel(int env_index) const {
	if(env_index >= 0 && env_index < states.GetCount()) {
		return states[env_index].level;
	}
	return 0.0;
}

// LFOBank implementation
LFOBank::LFOBank() {
	// Initialize with 4 LFOs by default
	states.SetCount(4);
}

LFOBank::~LFOBank() {
	// Destructor implementation
}

void LFOBank::SetParameters(int lfo_index, const LFOParams& params) {
	if(lfo_index >= 0 && lfo_index < states.GetCount()) {
		states[lfo_index].params = params;
		// Reset phase when parameters change
		states[lfo_index].phase = params.phase;
	}
}

void LFOBank::Process(int lfo_index, double* output, int sample_count, double sample_rate) {
	if(lfo_index >= 0 && lfo_index < states.GetCount()) {
		auto& state = states[lfo_index];
		auto& params = state.params;
		
		for(int i = 0; i < sample_count; i++) {
			// Calculate LFO value based on waveform
			double lfo_value = 0.0;
			double normalized_phase = state.phase;
			
			switch(params.waveform) {
				case SINE:
					lfo_value = sin(2.0 * M_PI * normalized_phase);
					break;
				case TRIANGLE:
					lfo_value = 2.0 * fabs(2.0 * normalized_phase - 1.0) - 1.0;
					break;
				case SQUARE:
					lfo_value = (normalized_phase < 0.5) ? 1.0 : -1.0;
					break;
				case SAW_UP:
					lfo_value = 2.0 * normalized_phase - 1.0;
					break;
				case SAW_DOWN:
					lfo_value = 1.0 - 2.0 * normalized_phase;
					break;
				case RANDOM:
					// In a real implementation, this would use a smooth random interpolation
					lfo_value = 2.0 * rand() / RAND_MAX - 1.0;
					break;
			}
			
			// Apply depth
			output[i] = lfo_value * params.depth;
			
			// Advance phase
			double phase_inc = params.rate / sample_rate;
			state.phase += phase_inc;
			if(state.phase >= 1.0) state.phase -= 1.0;
		}
	}
}

// WavetableOsc implementation
WavetableOsc::WavetableOsc() {
	// Initialize with a basic sine wavetable
	Vector<double> sine_table;
	sine_table.SetCount(1024);
	for(int i = 0; i < 1024; i++) {
		sine_table[i] = sin(2.0 * M_PI * i / 1024.0);
	}
	wavetable.Add(pick(sine_table)); // Use pick to move the vector instead of copying
}

WavetableOsc::~WavetableOsc() {
	// Destructor implementation
}

void WavetableOsc::SetWavetable(const Vector<Vector<double>>& wavetable) {
	this->wavetable <<= wavetable;
}

void WavetableOsc::SetFrequency(double freq) {
	frequency = freq;
}

void WavetableOsc::SetPhase(double phase) {
	this->phase = phase;
}

void WavetableOsc::SetWavetablePosition(double position) {
	wavetable_position = max(0.0, min(1.0, position)); // Clamp between 0 and 1
}

void WavetableOsc::Process(double* output, int sample_count, double sample_rate) {
	if(wavetable.GetCount() == 0) return;
	
	double phase_inc = frequency * 1024.0 / sample_rate; // Scale to wavetable size
	
	for(int i = 0; i < sample_count; i++) {
		// Calculate the index in the wavetable
		double float_index = phase * 1024.0;
		int index = (int)float_index;
		double frac = float_index - index;
		
		// Get the appropriate wavetable based on position
		int wavetable_idx = (int)(wavetable_position * (wavetable.GetCount() - 1));
		if(wavetable_idx >= wavetable.GetCount()) wavetable_idx = wavetable.GetCount() - 1;
		const Vector<double>& table = wavetable[wavetable_idx];
		
		// Linear interpolation between samples
		int next_index = (index + 1) % table.GetCount();
		output[i] = table[index] * (1.0 - frac) + table[next_index] * frac;
		
		// Advance phase
		phase += phase_inc / 1024.0;
		if(phase >= 1.0) phase -= 1.0;
	}
}

// OscillatorVA implementation
OscillatorVA::OscillatorVA() {
	// Initialize with default values
}

OscillatorVA::~OscillatorVA() {
	// Destructor implementation
}

void OscillatorVA::SetWaveform(Waveform wf) {
	waveform = wf;
}

void OscillatorVA::SetFrequency(double freq) {
	frequency = freq;
}

void OscillatorVA::SetPulseWidth(double pw) {
	pulse_width = max(0.01, min(0.99, pw)); // Clamp between 0.01 and 0.99 to avoid division by zero
}

void OscillatorVA::SetPhase(double phase) {
	this->phase = phase;
}

void OscillatorVA::Process(double* output, int sample_count, double sample_rate) {
	double phase_inc = frequency / sample_rate;
	
	for(int i = 0; i < sample_count; i++) {
		double value = 0.0;
		
		switch(waveform) {
			case SINE:
				value = sin(2.0 * M_PI * phase);
				break;
			case TRIANGLE:
				{
					double p = phase;
					if(p < 0.25) value = 4.0 * p;
					else if(p < 0.75) value = 2.0 - 4.0 * p;
					else value = 4.0 * p - 4.0;
				}
				break;
			case SQUARE:
				value = (phase < pulse_width) ? 1.0 : -1.0;
				break;
			case SAW_UP:
				value = 2.0 * phase - 1.0;
				break;
			case SAW_DOWN:
				value = 1.0 - 2.0 * phase;
				break;
			case NOISE:
				value = 2.0 * rand() / RAND_MAX - 1.0;
				break;
		}
		
		output[i] = value;
		
		// Advance phase
		phase += phase_inc;
		if(phase >= 1.0) phase -= 1.0;
	}
}

// FilterCascade implementation
FilterCascade::FilterCascade() {
	// Initialize with 2 filters by default
	filters.SetCount(2);
}

FilterCascade::~FilterCascade() {
	// Destructor implementation
}

void FilterCascade::SetFilterCount(int count) {
	filters.SetCount(count);
	for(int i = 0; i < filters.GetCount(); i++) {
		// Initialize default parameters
		filters[i].params.cutoff = 1000.0;
		filters[i].params.resonance = 0.7;
		// Initialize other default values
	}
}

void FilterCascade::SetFilterParams(int filter_index, const FilterParams& params) {
	if(filter_index >= 0 && filter_index < filters.GetCount()) {
		filters[filter_index].params = params;
		
		// Calculate filter coefficients based on parameters
		// This is a simplified implementation - real implementation would use proper biquad formulas
		double omega = 2.0 * M_PI * params.cutoff / 44100.0; // Assuming 44.1kHz sample rate for simplicity
		double sin_omega = sin(omega);
		double cos_omega = cos(omega);
		double alpha = sin_omega / (2.0 * params.resonance);
		
		// Calculate coefficients for low-pass filter (other types would have different formulas)
		double scale = 1.0 / (1.0 + alpha);
		
		if(params.type == LOW_PASS) {
			filters[filter_index].b1 = 1.0 - cos_omega;
			filters[filter_index].b2 = filters[filter_index].b1;
			filters[filter_index].a1 = -2.0 * cos_omega;
			filters[filter_index].a2 = 1.0 - alpha;
		}
		// Other filter types would need different coefficient calculations
	}
}

void FilterCascade::Process(double* input_output, int sample_count, double sample_rate) {
	for(int f = 0; f < filters.GetCount(); f++) {
		auto& filter = filters[f];
		
		for(int i = 0; i < sample_count; i++) {
			// Apply biquad filter
			double input = input_output[i];
			double output = filter.b1 * input + filter.b2 * filter.x1 - filter.a1 * filter.y1 - filter.a2 * filter.y2;
			
			// Update delay line
			filter.x2 = filter.x1;
			filter.x1 = input;
			filter.y2 = filter.y1;
			filter.y1 = output;
			
			// Update the input for the next filter
			input_output[i] = output;
		}
	}
}

// UnisonStack implementation
UnisonStack::UnisonStack() {
	SetVoiceCount(3); // Default to 3 unison voices
}

UnisonStack::~UnisonStack() {
	// Destructor implementation
}

void UnisonStack::SetVoiceCount(int count) {
	voice_count = max(1, count);
	detune_offsets.SetCount(voice_count);
	pan_positions.SetCount(voice_count);
	
	// Calculate detune offsets and pan positions
	for(int i = 0; i < voice_count; i++) {
		// Distribute detune symmetrically
		double detune_pos = -0.5 + (double)i / (voice_count - 1); // -0.5 to 0.5
		detune_offsets[i] = detune_pos * detune_cents;
		
		// Distribute pans across stereo field
		double pan_pos = -0.5 + (double)i / (voice_count - 1); // -0.5 to 0.5
		pan_positions[i] = pan_pos * spread;
	}
}

void UnisonStack::SetDetune(double detune) {
	detune_cents = detune;
	// Recalculate detune_offsets
	for(int i = 0; i < voice_count; i++) {
		double detune_pos = -0.5 + (double)i / (max(voice_count - 1, 1)); // -0.5 to 0.5
		detune_offsets[i] = detune_pos * detune_cents;
	}
}

void UnisonStack::SetSpread(double spread) {
	this->spread = max(0.0, min(1.0, spread)); // Clamp between 0 and 1
	// Recalculate pan positions
	for(int i = 0; i < voice_count; i++) {
		double pan_pos = -0.5 + (double)i / (max(voice_count - 1, 1)); // -0.5 to 0.5
		pan_positions[i] = pan_pos * this->spread;
	}
}

void UnisonStack::Process(const double* input, double* output, int sample_count, double sample_rate) {
	// Clear output
	memset(output, 0, sample_count * sizeof(double) * 2); // 2 channels for stereo
	
	// Process each unison voice
	for(int v = 0; v < voice_count; v++) {
		// Calculate frequency multiplier from detune (in cents)
		double freq_mult = pow(2.0, detune_offsets[v] / 1200.0);
		
		// Create a temporary buffer for this voice
		Vector<double> voice_buffer(sample_count);
		
		// Process the voice with detuning
		double phase = 0.0;
		double phase_inc_base = 1.0 / sample_rate; // This would be relative to input frequency
		
		for(int i = 0; i < sample_count; i++) {
			// In a real implementation, this would actually detune the signal
			// For now, this is a simplified approach
			voice_buffer[i] = input[i];
		}
		
		// Apply stereo positioning
		double left_gain = sqrt(0.5 * (1.0 - pan_positions[v]));
		double right_gain = sqrt(0.5 * (1.0 + pan_positions[v]));
		
		// Mix to stereo output (interleaved: L, R, L, R, ...)
		for(int i = 0; i < sample_count; i++) {
			output[i*2] += voice_buffer[i] * left_gain;     // Left channel
			output[i*2+1] += voice_buffer[i] * right_gain;  // Right channel
		}
	}
}

// FormantShaper implementation
FormantShaper::FormantShaper() {
	// Initialize with formant frequencies for vowel 'A'
	formant_frequencies.SetCount(5);
	formant_gains.SetCount(5);
	
	// Typical formant frequencies for 'A' vowel (Hz)
	formant_frequencies[0] = 850;  // F1
	formant_frequencies[1] = 1610; // F2
	formant_frequencies[2] = 2450; // F3
	formant_frequencies[3] = 3250; // F4
	formant_frequencies[4] = 4280; // F5
	
	// Initialize gains to 1.0
	for(int i = 0; i < 5; i++) {
		formant_gains[i] = 1.0;
	}
}

FormantShaper::~FormantShaper() {
	// Destructor implementation
}

void FormantShaper::SetVowel(Vowel v) {
	switch(v) {
		case A:
			// Already set as default
			formant_frequencies[0] = 850;  // F1
			formant_frequencies[1] = 1610; // F2
			formant_frequencies[2] = 2450; // F3
			formant_frequencies[3] = 3250; // F4
			formant_frequencies[4] = 4280; // F5
			break;
		case E:
			formant_frequencies[0] = 600;  // F1
			formant_frequencies[1] = 1900; // F2
			formant_frequencies[2] = 2600; // F3
			formant_frequencies[3] = 3200; // F4
			formant_frequencies[4] = 4000; // F5
			break;
		case I:
			formant_frequencies[0] = 300;  // F1
			formant_frequencies[1] = 2300; // F2
			formant_frequencies[2] = 3000; // F3
			formant_frequencies[3] = 3600; // F4
			formant_frequencies[4] = 4400; // F5
			break;
		case O:
			formant_frequencies[0] = 500;  // F1
			formant_frequencies[1] = 900;  // F2
			formant_frequencies[2] = 2300; // F3
			formant_frequencies[3] = 3100; // F4
			formant_frequencies[4] = 4000; // F5
			break;
		case U:
			formant_frequencies[0] = 300;  // F1
			formant_frequencies[1] = 870;  // F2
			formant_frequencies[2] = 2250; // F3
			formant_frequencies[3] = 3200; // F4
			formant_frequencies[4] = 4200; // F5
			break;
	}
}

void FormantShaper::SetVowelByIndex(int index) {
	if(index >= 0 && index < 5) {
		Vowel v = (Vowel)index;
		SetVowel(v);
	}
}

void FormantShaper::SetFormantShift(double shift) {
	shift_amount = max(-1.0, min(1.0, shift)); // Clamp between -1 and 1
	// In a real implementation, this would shift all formant frequencies by a ratio
	// e.g., shift of 0.1 might increase all formant frequencies by 10%
}

void FormantShaper::Process(double* input_output, int sample_count, double sample_rate) {
	// In a real implementation, this would apply formant filtering to the signal
	// For now, we'll just apply a simple effect to demonstrate the concept
	
	for(int i = 0; i < sample_count; i++) {
		// Apply formant shaping based on the current settings
		// This is a simplified implementation - real formant shaping is much more complex
		input_output[i] *= (0.95 + 0.1 * fabs(shift_amount)); // Apply a simple gain adjustment
	}
}

} // namespace Synth
} // namespace am
