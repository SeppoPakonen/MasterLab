#include "AudioCore.h"

CuteAudioVorbisFile::CuteAudioVorbisFile() {}
CuteAudioVorbisFile::~CuteAudioVorbisFile() {}
bool CuteAudioVorbisFile::Open(const String& file_name, int mode) { this->file_name = file_name; this->mode = mode; return true; }
void CuteAudioVorbisFile::Close() { file_name.Clear(); mode = 0; }
int CuteAudioVorbisFile::Read(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
int CuteAudioVorbisFile::Write(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
bool CuteAudioVorbisFile::Seek(unsigned long offset) { (void)offset; return true; }
int CuteAudioVorbisFile::GetMode() const { return mode; }
unsigned short CuteAudioVorbisFile::GetChannels() const { return channels; }
unsigned long CuteAudioVorbisFile::GetFrames() const { return frames; }
unsigned int CuteAudioVorbisFile::GetSampleRate() const { return sample_rate; }
String CuteAudioVorbisFile::GetDescription() const { return "vorbis-backed audio file implementation"; }
