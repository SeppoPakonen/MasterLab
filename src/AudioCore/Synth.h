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

} // namespace Synth
} // namespace am

#endif
