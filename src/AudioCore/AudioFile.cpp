#include "AudioFile.h"
#include "WavFile.h"
#include "OggFile.h"

namespace am {

bool AudioFile::Load(const String& path, AudioBuffer& buffer)
{
	String ext = ToLower(GetFileExt(path));
	
	if (ext == ".wav") {
		return WavFile::Load(path, buffer);
	} else if (ext == ".ogg") {
		return OggFile::Load(path, buffer);
	}
	
	return false;
}

}
