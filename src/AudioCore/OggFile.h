#ifndef _AudioCore_OggFile_h_
#define _AudioCore_OggFile_h_

#include <Core/Core.h>
#include "AudioBuffer.h"
#include "stb_vorbis.h" // Include stb_vorbis.h here

namespace am {

using namespace Upp;

class OggFile {
public:
	static bool Load(const String& path, AudioBuffer& buffer);
};

}

#endif
