#include "OggFile.h"
#include <vorbis/vorbis.h>

namespace am {

bool OggFile::Load(const String& path, AudioBuffer& buffer)
{
	StbVorbis vorbis;
	if (!vorbis.Open(path)) {
		return false;
	}
	
	int channels = vorbis.GetChannels();
	int sampleRate = vorbis.GetSampleRate();
	int64 frames = vorbis.GetCount();
	
	buffer.Resize(channels, frames);
	buffer.rate = sampleRate;
	
	// StbVorbis reads into an interleaved buffer
	Vector<float> tempBuffer;
	tempBuffer.SetCount(frames * channels);
	
	int readFrames = vorbis.Read(tempBuffer.Begin(), frames);
	if (readFrames <= 0) {
		return false;
	}

	for (int c = 0; c < channels; ++c) {
		for (int i = 0; i < readFrames; ++i) {
			buffer.data[c][i] = tempBuffer[i * channels + c];
		}
	}
	
	return true;
}

}
