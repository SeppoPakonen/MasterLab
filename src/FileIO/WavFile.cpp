#include "WavFile.h"

namespace am {

struct WavHeader {
	char riff[4];
	uint32_t size;
	char wave[4];
	char fmt[4];
	uint32_t fmtSize;
	uint16_t format;
	uint16_t channels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
};

bool WavFile::Load(const String& path, AudioBuffer& buffer)
{
	FileIn in(path);
	if (!in) {
		Upp::Cerr() << "Could not open file: " << path << "\n";
		return false;
	}

	WavHeader h;
	if (in.Get(&h, sizeof(h)) != sizeof(h)) {
		Upp::Cerr() << "Could not read WAV header\n";
		return false;
	}

	char riff[5], wave[5];
	memcpy(riff, h.riff, 4); riff[4] = 0;
	memcpy(wave, h.wave, 4); wave[4] = 0;
	
	Upp::Cout() << "RIFF ID: " << riff << ", WAVE ID: " << wave << "\n";

	if (memcmp(h.riff, "RIFF", 4) != 0 || memcmp(h.wave, "WAVE", 4) != 0) {
		Upp::Cerr() << "Not a valid RIFF/WAVE file\n";
		return false;
	}

	// The header struct might have padding or the file might have JUNK chunks
	// Re-seek to after "WAVE" which is at offset 12
	in.Seek(12);

	while (!in.IsEof()) {
		char chunkId[5];
		uint32_t chunkSize;
		if (in.Get(chunkId, 4) != 4) break;
		chunkId[4] = 0;
		if (in.Get(&chunkSize, 4) != 4) break;

		Upp::Cout() << "Found chunk: " << chunkId << ", size: " << chunkSize << "\n";

		if (memcmp(chunkId, "fmt ", 4) == 0) {
			// Read fmt info manually to avoid struct padding issues
			uint16_t format, channels, blockAlign, bitsPerSample;
			uint32_t sampleRate, byteRate;
			
			in.Get(&format, 2);
			in.Get(&channels, 2);
			in.Get(&sampleRate, 4);
			in.Get(&byteRate, 4);
			in.Get(&blockAlign, 2);
			in.Get(&bitsPerSample, 2);
			
			h.format = format;
			h.channels = channels;
			h.sampleRate = sampleRate;
			h.bitsPerSample = bitsPerSample;
			
			Upp::Cout() << "Format: " << format << ", Channels: " << channels << ", Rate: " << sampleRate << ", Bits: " << bitsPerSample << "\n";
			
			if (chunkSize > 16) in.SeekCur(chunkSize - 16);
		} else if (memcmp(chunkId, "data", 4) == 0) {
			int bytesPerSample = h.bitsPerSample / 8;
			if (bytesPerSample == 0) return false;
			
			int frames = chunkSize / (h.channels * bytesPerSample);
			buffer.Resize(h.channels, frames);
			buffer.rate = h.sampleRate;

			Upp::Cout() << "Loading " << frames << " frames...\n";

			if (h.bitsPerSample == 16) {
				for (int i = 0; i < frames; ++i) {
					for (int c = 0; c < h.channels; ++c) {
						int16_t s;
						if (in.Get(&s, 2) != 2) return true; // Partial read
						buffer.data[c].Add((float)s / 32768.0f);
					}
				}
			} else if (h.bitsPerSample == 32 || h.bitsPerSample == 24) {
				if (h.bitsPerSample == 32) {
					for (int i = 0; i < frames; ++i) {
						for (int c = 0; c < h.channels; ++c) {
							float s;
							if (in.Get(&s, 4) != 4) return true;
							buffer.data[c].Add(s);
						}
					}
				} else if (h.bitsPerSample == 24) {
					for (int i = 0; i < frames; ++i) {
						for (int c = 0; c < h.channels; ++c) {
							uint8_t b[3];
							if (in.Get(b, 3) != 3) return true;
							// 24-bit signed integer to float
							int32_t val = (b[0] << 8) | (b[1] << 16) | (b[2] << 24);
							buffer.data[c].Add((float)(val >> 8) / 8388608.0f);
						}
					}
				}
			}
			return true;
		} else {
			in.SeekCur(chunkSize);
		}
		
		// Ensure alignment
		if (chunkSize % 2 != 0) in.SeekCur(1);
	}

	return false;
}

}
