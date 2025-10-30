#include "TransportUI.h"
namespace am {

void Metronome::Enable(bool enable) {
	enabled = enable;
}

void Metronome::SetVolume(double volume) {
	this->volume = Upp::clamp(volume, 0.0, 1.0);
}

void Metronome::SetSound(const Upp::String& soundPath) {
	sound_path = soundPath;
}

}