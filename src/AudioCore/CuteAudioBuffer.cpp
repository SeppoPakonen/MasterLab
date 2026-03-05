#include "AudioCore.h"

CuteAudioBufferThread::CuteAudioBufferThread(unsigned int sync_size)
	: sync_size(sync_size), sync_mask(sync_size ? sync_size - 1 : 0) {}

CuteAudioBufferThread::~CuteAudioBufferThread() {}

void CuteAudioBufferThread::SetRunState(bool run_state) {
	this->run_state = run_state;
}

bool CuteAudioBufferThread::GetRunState() const {
	return run_state;
}

void CuteAudioBufferThread::Sync(CuteAudioBuffer* audio_buffer) {
	if(audio_buffer)
		sync_items.Add(audio_buffer);
}

void CuteAudioBufferThread::SyncExport() {
	Process();
}

void CuteAudioBufferThread::CheckSyncSize(unsigned int sync_size) {
	this->sync_size = sync_size;
	sync_mask = sync_size ? sync_size - 1 : 0;
}

void CuteAudioBufferThread::Run() {
	Process();
}

void CuteAudioBufferThread::Process() {
	for(int i = 0; i < sync_items.GetCount(); ++i) {
		if(sync_items[i])
			sync_items[i]->Sync();
	}
}

CuteAudioBuffer::CuteAudioBuffer(CuteAudioBufferThread* sync_thread, unsigned short channels)
	: sync_thread(sync_thread), channels(channels) {}

CuteAudioBuffer::~CuteAudioBuffer() {}

CuteAudioFile* CuteAudioBuffer::GetFile() const {
	return file;
}

unsigned short CuteAudioBuffer::GetChannels() const {
	return channels;
}

unsigned long CuteAudioBuffer::GetFrames() const {
	return length;
}

unsigned int CuteAudioBuffer::GetBufferSize() const {
	return buffer_size;
}

float CuteAudioBuffer::GetResampleRatio() const {
	return 1.0f;
}

bool CuteAudioBuffer::Open(const String& file_name, int mode) {
	(void)file_name;
	(void)mode;
	return true;
}

void CuteAudioBuffer::Close() {}

int CuteAudioBuffer::Read(float** frames, unsigned int frame_count, unsigned int offset) {
	(void)frames;
	(void)offset;
	return (int)frame_count;
}

int CuteAudioBuffer::Write(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset) {
	(void)frames;
	(void)channels;
	(void)offset;
	length = max<unsigned long>(length, this->offset + frame_count);
	return (int)frame_count;
}

int CuteAudioBuffer::ReadMix(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset, float gain) {
	(void)channels;
	(void)gain;
	return Read(frames, frame_count, offset);
}

int CuteAudioBuffer::ReadMux(float** frames, unsigned int frame_count, unsigned short channels, unsigned int offset, float gain) {
	(void)channels;
	(void)gain;
	return Read(frames, frame_count, offset);
}

bool CuteAudioBuffer::Seek(unsigned long frame) {
	offset = frame;
	return true;
}

void CuteAudioBuffer::Reset(bool looping) {
	(void)looping;
	offset = 0;
}

void CuteAudioBuffer::SetOffset(unsigned long offset) {
	this->offset = offset;
}

unsigned long CuteAudioBuffer::GetOffset() const {
	return offset;
}

void CuteAudioBuffer::SetLength(unsigned long length) {
	this->length = length;
}

unsigned long CuteAudioBuffer::GetLength() const {
	return length;
}

unsigned long CuteAudioBuffer::GetFileLength() const {
	return file_length;
}

void CuteAudioBuffer::SetGain(float gain) {
	this->gain = gain;
}

float CuteAudioBuffer::GetGain() const {
	return gain;
}

void CuteAudioBuffer::SetPanning(float panning) {
	this->panning = panning;
}

float CuteAudioBuffer::GetPanning() const {
	return panning;
}

float CuteAudioBuffer::GetChannelGain(unsigned short index) const {
	(void)index;
	return gain;
}

void CuteAudioBuffer::SetLoop(unsigned long loop_start, unsigned long loop_end) {
	this->loop_start = loop_start;
	this->loop_end = loop_end;
}

unsigned long CuteAudioBuffer::GetLoopStart() const {
	return loop_start;
}

unsigned long CuteAudioBuffer::GetLoopEnd() const {
	return loop_end;
}

void CuteAudioBuffer::SetTimeStretch(float time_stretch) {
	this->time_stretch = time_stretch;
}

float CuteAudioBuffer::GetTimeStretch() const {
	return time_stretch;
}

bool CuteAudioBuffer::IsTimeStretch() const {
	return time_stretch != 1.0f;
}

void CuteAudioBuffer::SetPitchShift(float pitch_shift) {
	this->pitch_shift = pitch_shift;
}

float CuteAudioBuffer::GetPitchShift() const {
	return pitch_shift;
}

bool CuteAudioBuffer::IsPitchShift() const {
	return pitch_shift != 1.0f;
}

void CuteAudioBuffer::SetSyncFlag(SyncFlag flag, bool is_on) {
	if(is_on)
		sync_flags |= flag;
	else
		sync_flags &= ~flag;
}

bool CuteAudioBuffer::IsSyncFlag(SyncFlag flag) const {
	return (sync_flags & flag) != 0;
}

void CuteAudioBuffer::InitSync() {
	SetSyncFlag(InitSyncFlag);
}

void CuteAudioBuffer::Sync() {}

bool CuteAudioBuffer::InSync(unsigned long frame_start, unsigned long frame_end) {
	(void)frame_start;
	(void)frame_end;
	return true;
}

void CuteAudioBuffer::SyncExport() {}

void CuteAudioBuffer::SetPeakFile(CuteAudioPeakFile* peak_file) {
	this->peak_file = peak_file;
}

CuteAudioPeakFile* CuteAudioBuffer::GetPeakFile() const {
	return peak_file;
}
