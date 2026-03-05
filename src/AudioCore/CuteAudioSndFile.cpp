#include "AudioCore.h"

CuteAudioSndFile::CuteAudioSndFile() {}
CuteAudioSndFile::~CuteAudioSndFile() {}
bool CuteAudioSndFile::Open(const String& file_name, int mode) { this->file_name = file_name; this->mode = mode; return true; }
void CuteAudioSndFile::Close() { file_name.Clear(); mode = 0; }
int CuteAudioSndFile::Read(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
int CuteAudioSndFile::Write(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
bool CuteAudioSndFile::Seek(unsigned long offset) { (void)offset; return true; }
int CuteAudioSndFile::GetMode() const { return mode; }
unsigned short CuteAudioSndFile::GetChannels() const { return channels; }
unsigned long CuteAudioSndFile::GetFrames() const { return frames; }
unsigned int CuteAudioSndFile::GetSampleRate() const { return sample_rate; }
String CuteAudioSndFile::GetDescription() const { return "libsndfile-backed audio file implementation"; }
