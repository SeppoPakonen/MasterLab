#ifndef _Video_ReplaceAudio_h_
#define _Video_ReplaceAudio_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class ReplaceAudio {
public:
	ReplaceAudio();
	bool Replace(const String& videoPath, const String& audioPath, const String& outputPath);
	void SetSyncMode(int mode);
	int GetSyncMode() const { return sync_mode; }
	
private:
	int sync_mode = 0;  // 0=auto, 1=manual
};

}

#endif