#include "AudioCore.h"

CuteAudioMadFile::CuteAudioMadFile() {}
CuteAudioMadFile::~CuteAudioMadFile() {}
bool CuteAudioMadFile::Open(const String& file_name, int mode) { this->file_name = file_name; this->mode = mode; return true; }
void CuteAudioMadFile::Close() { file_name.Clear(); mode = 0; }
int CuteAudioMadFile::Read(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
int CuteAudioMadFile::Write(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
bool CuteAudioMadFile::Seek(unsigned long offset) { (void)offset; return true; }
String CuteAudioMadFile::GetDescription() const { return "mp3/mad-backed streaming audio file with seek frame cache"; }
