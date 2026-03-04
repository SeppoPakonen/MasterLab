#include "AudioCore.h"

CuteAudioMonitor::CuteAudioMonitor() {}
CuteAudioMonitor::~CuteAudioMonitor() {}
bool CuteAudioMonitor::Open(const String& file_name, int mode) { this->file_name = file_name; this->mode = mode; return true; }
void CuteAudioMonitor::Close() { file_name.Clear(); mode = 0; }
int CuteAudioMonitor::Read(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
int CuteAudioMonitor::Write(float** frames, unsigned int frame_count) { (void)frames; return (int)frame_count; }
bool CuteAudioMonitor::Seek(unsigned long offset) { (void)offset; return true; }
String CuteAudioMonitor::GetDescription() const { return "sample processor for gain and peak tracking"; }
