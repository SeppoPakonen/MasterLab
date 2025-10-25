#ifndef _Video_AudioFromVideo_h_
#define _Video_AudioFromVideo_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class AudioFromVideo {
public:
	AudioFromVideo();
	bool ExtractAudio(const String& videoPath, const String& audioPath);
	void SetExtractQuality(int quality);
	int GetExtractQuality() const { return extract_quality; }
	
private:
	int extract_quality = 96;  // kbps
};

}

#endif