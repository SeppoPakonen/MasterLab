#include "AudioCore.h"

CuteAudioPeak::CuteAudioPeak() {}
CuteAudioPeak::~CuteAudioPeak() {}
bool CuteAudioPeak::Open(const String& file_name, int mode) { this->file_name = file_name; this->mode = mode; return true; }
void CuteAudioPeak::Close() { file_name.Clear(); mode = 0; }
int CuteAudioPeak::Read(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
int CuteAudioPeak::Write(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
bool CuteAudioPeak::Seek(unsigned long offset) { (void)offset; return true; }
String CuteAudioPeak::GetDescription() const { return "peak-file cache and background peak generation"; }
