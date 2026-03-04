#include "OggFile.h"
#include "stb_vorbis.h" // Include the custom stb_vorbis.h

// Ensure STB_VORBIS_IMPLEMENTATION is defined in only one compilation unit.
// For now, it's defined in stb_vorbis_impl.cpp.

namespace am {

bool OggFile::Load(const String& path, AudioBuffer& buffer)
{
	int channels;
	int sample_rate;
	int samples_len;
	float *decoded_samples; // stb_vorbis_decode_filename returns float *
	STBVorbisError error;
	
	decoded_samples = stb_vorbis_decode_filename(path.ToStd().c_str(), &channels, &sample_rate, &samples_len, &error);
	
	if (decoded_samples == NULL) {
		// Error occurred during decoding
		Upp::Cerr() << "STB Vorbis Error: " << (int)error << "\n"; // Cast error to int for output
		return false;
	}
	
	buffer.Resize(channels, samples_len);
	buffer.rate = sample_rate;
	
	// Copy float samples directly (stb_vorbis_decode_filename returns float*)
	for (int i = 0; i < samples_len; ++i) {
		for (int c = 0; c < channels; ++c) {
			buffer.data[c][i] = decoded_samples[i * channels + c];
		}
	}
	
	free(decoded_samples); // Free the memory allocated by stb_vorbis
	return true;
}

}
