#include "AudioCore.h"

static const int CUTE_RAMP_LENGTH = 32;

CuteAudioBufferThread::CuteAudioBufferThread(unsigned int sync_size)
	: sync_size(8) {
	while(this->sync_size < sync_size)
		this->sync_size <<= 1;
	sync_mask = this->sync_size - 1;
	sync_items.SetCount(this->sync_size, nullptr);
}

CuteAudioBufferThread::~CuteAudioBufferThread() {
	run_state = false;
	sync_items.Clear();
}

void CuteAudioBufferThread::SetRunState(bool run_state) {
	this->run_state = run_state;
}

bool CuteAudioBufferThread::GetRunState() const {
	return run_state;
}

void CuteAudioBufferThread::Sync(CuteAudioBuffer* audio_buffer) {
	if(!audio_buffer) {
		sync_read = sync_write;
		return;
	}
	unsigned int next_write = (sync_write + 1) & sync_mask;
	if(next_write != sync_read) {
		sync_items[sync_write] = audio_buffer;
		sync_write = next_write;
	}
}

void CuteAudioBufferThread::SyncExport() {
	Process();
}

void CuteAudioBufferThread::CheckSyncSize(unsigned int requested_size) {
	if(requested_size <= sync_size - 4)
		return;
	unsigned int next_size = sync_size << 1;
	while(next_size < requested_size)
		next_size <<= 1;
	sync_items.SetCount(next_size, nullptr);
	sync_size = next_size;
	sync_mask = next_size - 1;
}

void CuteAudioBufferThread::Run() {
	run_state = true;
	while(run_state)
		Process();
}

void CuteAudioBufferThread::Process() {
	while(sync_read != sync_write) {
		CuteAudioBuffer* audio_buffer = sync_items[sync_read];
		if(audio_buffer)
			audio_buffer->Sync();
		sync_read = (sync_read + 1) & sync_mask;
	}
}

CuteAudioBuffer::CuteAudioBuffer(CuteAudioBufferThread* sync_thread, unsigned short channels)
	: sync_thread(sync_thread), channels(channels) {
	buffer_size = CUTE_RAMP_LENGTH;
}

CuteAudioBuffer::~CuteAudioBuffer() {
	Close();
}

CuteAudioFile* CuteAudioBuffer::GetFile() const { return file; }
unsigned short CuteAudioBuffer::GetChannels() const { return channels; }
unsigned long CuteAudioBuffer::GetFrames() const { return file_length; }
unsigned int CuteAudioBuffer::GetBufferSize() const { return buffer_size; }
float CuteAudioBuffer::GetResampleRatio() const { return 1.0f; }
bool CuteAudioBuffer::Open(const String& file_name, int mode) { (void)file_name; (void)mode; return true; }
void CuteAudioBuffer::Close() { file = nullptr; }
int CuteAudioBuffer::Read(float** frames, unsigned int frame_count, unsigned int offset) { (void)frames; (void)frame_count; (void)offset; return 0; }
int CuteAudioBuffer::Write(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset) { (void)frames; (void)frame_count; (void)channels; (void)offset; return 0; }
int CuteAudioBuffer::ReadMix(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset, float gain) { (void)frames; (void)frame_count; (void)channels; (void)offset; (void)gain; return 0; }
int CuteAudioBuffer::ReadMux(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset, float gain) { (void)frames; (void)frame_count; (void)channels; (void)offset; (void)gain; return 0; }
bool CuteAudioBuffer::Seek(unsigned long frame) { offset = frame; return true; }
void CuteAudioBuffer::Reset(bool looping) { (void)looping; }
void CuteAudioBuffer::SetOffset(unsigned long offset) { this->offset = offset; }
unsigned long CuteAudioBuffer::GetOffset() const { return offset; }
void CuteAudioBuffer::SetLength(unsigned long length) { this->length = length; }
unsigned long CuteAudioBuffer::GetLength() const { return length; }
unsigned long CuteAudioBuffer::GetFileLength() const { return file_length; }
void CuteAudioBuffer::SetGain(float gain) { this->gain = gain; }
float CuteAudioBuffer::GetGain() const { return gain; }
void CuteAudioBuffer::SetPanning(float panning) { this->panning = panning; }
float CuteAudioBuffer::GetPanning() const { return panning; }
float CuteAudioBuffer::GetChannelGain(unsigned short index) const { (void)index; return gain; }
void CuteAudioBuffer::SetLoop(unsigned long loop_start, unsigned long loop_end) { this->loop_start = loop_start; this->loop_end = loop_end; }
unsigned long CuteAudioBuffer::GetLoopStart() const { return loop_start; }
unsigned long CuteAudioBuffer::GetLoopEnd() const { return loop_end; }
void CuteAudioBuffer::SetTimeStretch(float time_stretch) { this->time_stretch = time_stretch; }
float CuteAudioBuffer::GetTimeStretch() const { return time_stretch; }
bool CuteAudioBuffer::IsTimeStretch() const { return time_stretch != 1.0f; }
void CuteAudioBuffer::SetPitchShift(float pitch_shift) { this->pitch_shift = pitch_shift; }
float CuteAudioBuffer::GetPitchShift() const { return pitch_shift; }
bool CuteAudioBuffer::IsPitchShift() const { return pitch_shift != 1.0f; }
void CuteAudioBuffer::SetSyncFlag(SyncFlag flag, bool is_on) { if(is_on) sync_flags |= flag; else sync_flags &= ~flag; }
bool CuteAudioBuffer::IsSyncFlag(SyncFlag flag) const { return (sync_flags & flag) != 0; }
void CuteAudioBuffer::InitSync() { SetSyncFlag(InitSync); }
void CuteAudioBuffer::Sync() { SetSyncFlag(ReadSync, false); SetSyncFlag(WaitSync, false); }
bool CuteAudioBuffer::InSync(unsigned long frame_start, unsigned long frame_end) { (void)frame_start; (void)frame_end; return true; }
void CuteAudioBuffer::SyncExport() { Sync(); }
void CuteAudioBuffer::SetPeakFile(CuteAudioPeakFile* peak_file) { this->peak_file = peak_file; }
CuteAudioPeakFile* CuteAudioBuffer::GetPeakFile() const { return peak_file; }
