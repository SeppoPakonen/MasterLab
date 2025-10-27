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

} // namespace Synth
} // namespace am
