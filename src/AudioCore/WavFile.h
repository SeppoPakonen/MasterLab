#ifndef _AudioCore_WavFile_h_
#define _AudioCore_WavFile_h_

#include <Core/Core.h>
#include "AudioBuffer.h"

namespace am {

using namespace Upp;

class WavFile {
public:
	static bool Load(const String& path, AudioBuffer& buffer);
};

}

#endif
