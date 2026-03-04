#include "AudioCore.h"

static const int CUTE_SAMPLE_RATE = 44100;
static const int CUTE_BUFFER_SIZE = 1024;
static const int CUTE_BLOCK_SIZE = 64;

static inline void StandardBufferAdd(float** buffer, float** frames, unsigned int frame_count, unsigned short buffer_count, unsigned short channel_count, unsigned int offset) {
	unsigned short buffer_index = 0;
	for(unsigned short channel_index = 0; channel_index < channel_count; ++channel_index) {
		float* output = buffer[buffer_index] + offset;
		float* input = frames[channel_index] + offset;
		for(unsigned int frame_index = 0; frame_index < frame_count; ++frame_index)
			*output++ += *input++;
		if(++buffer_index >= buffer_count)
			buffer_index = 0;
	}
}

class CuteAudioExportBuffer {
public:
	CuteAudioExportBuffer(unsigned short channels, unsigned int buffer_size)
		: channels(channels), buffer_size(buffer_size) {
		buffer.SetCount(channels);
		for(int i = 0; i < buffer.GetCount(); i++) {
			buffer[i] = new float[buffer_size];
			memset(buffer[i], 0, sizeof(float) * buffer_size);
		}
	}

	~CuteAudioExportBuffer() {
		for(int i = 0; i < buffer.GetCount(); i++)
			delete[] buffer[i];
	}

	unsigned short GetChannels() const { return channels; }
	unsigned int GetBufferSize() const { return buffer_size; }
	float** GetBuffer() { return buffer.Begin(); }
	void Clear() {
		for(int i = 0; i < buffer.GetCount(); i++)
			memset(buffer[i], 0, sizeof(float) * buffer_size);
	}
	void Add(float** frames, unsigned int frame_count, unsigned short frame_channels, unsigned int offset = 0) {
		StandardBufferAdd(GetBuffer(), frames, frame_count, channels, frame_channels, offset);
	}

private:
	unsigned short channels = 0;
	unsigned int buffer_size = 0;
	Vector<float*> buffer;
};

class CuteAudioEngineProxy {
public:
	void NotifyShutEvent() {}
	void NotifyXrunEvent() {}
	void NotifyPortEvent() {}
	void NotifyBuffEvent(unsigned int buffer_size) { (void)buffer_size; }
	void NotifySessEvent(void* session_arg) { (void)session_arg; }
	void NotifySyncEvent(unsigned long play_head, bool is_playing) { (void)play_head; (void)is_playing; }
	void NotifyPropEvent() {}
	void NotifySelfEvent() {}
};

class CuteAudioEngine {
public:
	CuteAudioEngine()
		: sample_rate(CUTE_SAMPLE_RATE), buffer_size(CUTE_BUFFER_SIZE), block_size(CUTE_BLOCK_SIZE) {
	}

	bool Init() { return true; }
	const CuteAudioEngineProxy* GetProxy() const { return &proxy; }
	int Process(unsigned int frame_count) { (void)frame_count; return 0; }
	void Timebase(unsigned long play_head, int is_new_pos) { (void)play_head; (void)is_new_pos; }
	unsigned int GetSampleRate() const { return sample_rate; }
	unsigned int GetBufferSize() const { return buffer_size; }
	unsigned int GetBlockSize() const { return block_size; }

private:
	CuteAudioEngineProxy proxy;
	unsigned int sample_rate = 0;
	unsigned int buffer_size = 0;
	unsigned int block_size = 0;
};
