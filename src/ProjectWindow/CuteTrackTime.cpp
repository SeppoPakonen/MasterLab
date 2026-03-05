#include "ProjectWindow.h"

CuteTrackTime::CuteTrackTime() {}
void CuteTrackTime::SetFrame(int64 frame) { this->frame = frame; }
int64 CuteTrackTime::GetFrame() const { return frame; }
void CuteTrackTime::SetTick(int64 tick) { this->tick = tick; }
int64 CuteTrackTime::GetTick() const { return tick; }
void CuteTrackTime::SetBar(int bar) { this->bar = bar; }
int CuteTrackTime::GetBar() const { return bar; }
void CuteTrackTime::SetBeat(int beat) { this->beat = beat; }
int CuteTrackTime::GetBeat() const { return beat; }
String CuteTrackTime::AsText() const { return Format("%d.%d @ %lld", bar, beat, (long long)frame); }
