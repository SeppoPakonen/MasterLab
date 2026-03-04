#ifndef _AudioCore_CuteAudioBuffer_h_
#define _AudioCore_CuteAudioBuffer_h_

class CuteAudioPeakFile;
class CuteAudioBuffer;
class CuteAudioFile;
class CuteTimeStretcher;

class CuteAudioBufferThread {
public:
	CuteAudioBufferThread(unsigned int sync_size = 8);
	~CuteAudioBufferThread();

	void SetRunState(bool run_state);
	bool GetRunState() const;
	void Sync(CuteAudioBuffer* audio_buffer = nullptr);
	void SyncExport();
	void CheckSyncSize(unsigned int sync_size);
	void Run();
	void Process();

private:
	unsigned int sync_size;
	unsigned int sync_mask;
	Vector<CuteAudioBuffer*> sync_items;
	volatile unsigned int sync_read = 0;
	volatile unsigned int sync_write = 0;
	volatile bool run_state = false;
};

class CuteAudioBuffer {
public:
	enum SyncFlag {
		InitSyncFlag = 1,
		ReadSync = 2,
		WaitSync = 4,
		CloseSync = 8,
	};

	CuteAudioBuffer(CuteAudioBufferThread* sync_thread, unsigned short channels);
	~CuteAudioBuffer();

	CuteAudioFile* GetFile() const;
	unsigned short GetChannels() const;
	unsigned long GetFrames() const;
	unsigned int GetBufferSize() const;
	float GetResampleRatio() const;
	bool Open(const String& file_name, int mode = 0);
	void Close();
	int Read(float** frames, unsigned int frame_count, unsigned int offset = 0);
	int Write(float** frames, unsigned int frame_count, unsigned short channels = 0, unsigned int offset = 0);
	int ReadMix(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset, float gain);
	int ReadMux(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset, float gain);
	bool Seek(unsigned long frame);
	void Reset(bool looping);
	void SetOffset(unsigned long offset);
	unsigned long GetOffset() const;
	void SetLength(unsigned long length);
	unsigned long GetLength() const;
	unsigned long GetFileLength() const;
	void SetGain(float gain);
	float GetGain() const;
	void SetPanning(float panning);
	float GetPanning() const;
	float GetChannelGain(unsigned short index) const;
	void SetLoop(unsigned long loop_start, unsigned long loop_end);
	unsigned long GetLoopStart() const;
	unsigned long GetLoopEnd() const;
	void SetTimeStretch(float time_stretch);
	float GetTimeStretch() const;
	bool IsTimeStretch() const;
	void SetPitchShift(float pitch_shift);
	float GetPitchShift() const;
	bool IsPitchShift() const;
	void SetSyncFlag(SyncFlag flag, bool is_on = true);
	bool IsSyncFlag(SyncFlag flag) const;
	void InitSync();
	void Sync();
	bool InSync(unsigned long frame_start, unsigned long frame_end);
	void SyncExport();
	void SetPeakFile(CuteAudioPeakFile* peak_file);
	CuteAudioPeakFile* GetPeakFile() const;

private:
	CuteAudioBufferThread* sync_thread = nullptr;
	CuteAudioFile* file = nullptr;
	CuteAudioPeakFile* peak_file = nullptr;
	unsigned short channels = 0;
	unsigned int buffer_size = 0;
	unsigned long offset = 0;
	unsigned long length = 0;
	unsigned long file_length = 0;
	unsigned long loop_start = 0;
	unsigned long loop_end = 0;
	float gain = 1.0f;
	float panning = 0.0f;
	float time_stretch = 1.0f;
	float pitch_shift = 1.0f;
	int sync_flags = 0;
};

#endif
