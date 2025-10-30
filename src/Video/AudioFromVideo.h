#ifndef _Video_AudioFromVideo_h_
#define _Video_AudioFromVideo_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class AudioFromVideo {
public:
	AudioFromVideo();
	bool ExtractAudio(const Upp::String& videoPath, const Upp::String& audioPath);
	void SetExtractQuality(int quality);
	int GetExtractQuality() const { return extract_quality; }
	
private:
	int extract_quality = 96;  // kbps
};

}

#endif