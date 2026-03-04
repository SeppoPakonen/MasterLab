#ifndef _AudioCore_AudioFile_h_
#define _AudioCore_AudioFile_h_

#include <Core/Core.h>
#include "AudioBuffer.h"

namespace am {

using namespace Upp;

class AudioFile {
public:
	static bool Load(const String& path, AudioBuffer& buffer);
};

}

#endif
