#include "AudioCore.h"

CuteAudioMeter::CuteAudioMeter() {}
CuteAudioMeter::~CuteAudioMeter() {}
bool CuteAudioMeter::Open(const String& file_name, int mode) { this->file_name = file_name; this->mode = mode; return true; }
void CuteAudioMeter::Close() { file_name.Clear(); mode = 0; }
int CuteAudioMeter::Read(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
int CuteAudioMeter::Write(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
bool CuteAudioMeter::Seek(unsigned long offset) { (void)offset; return true; }
String CuteAudioMeter::GetDescription() const { return "audio meter widget and monitor bridge"; }
