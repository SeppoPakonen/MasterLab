#ifndef _FileIO_WavFile_h_
#define _FileIO_WavFile_h_

#include <Core/Core.h>
#include <AudioCore/AudioBuffer.h>

namespace am {

using namespace Upp;

class WavFile {
public:
	static bool Load(const String& path, AudioBuffer& buffer);
	// Basic writing support could be added later
};

}

#endif
