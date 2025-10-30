#ifndef _TransportUI_Metronome_h_
#define _TransportUI_Metronome_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class Metronome {
public:
	void Enable(bool enable);
	bool IsEnabled() const { return enabled; }
	void SetVolume(double volume);
	double GetVolume() const { return volume; }
	void SetSound(const Upp::String& soundPath);
	Upp::String GetSound() const { return sound_path; }
	
private:
	bool enabled = false;
	double volume = 0.5;
	Upp::String sound_path;
};

}

#endif