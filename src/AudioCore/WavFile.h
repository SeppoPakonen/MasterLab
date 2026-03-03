#ifndef _MasterLab_WavFile_h_
#define _MasterLab_WavFile_h_

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
