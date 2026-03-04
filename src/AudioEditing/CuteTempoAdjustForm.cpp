#include "AudioEditing.h"

CuteTempoAdjustForm::ClipWidget::ClipWidget() {}
CuteTempoAdjustForm::CuteTempoAdjustForm() { Title("Tempo Adjust"); Add(clip_widget.SizePos()); }
void CuteTempoAdjustForm::SetClip(CuteAudioClip* clip) { this->clip = clip; }
CuteAudioClip* CuteTempoAdjustForm::GetClip() const { return clip; }
CuteAudioClip* CuteTempoAdjustForm::GetAudioClip() const { return clip; }
void CuteTempoAdjustForm::SetRangeStart(int64 range_start) { this->range_start = range_start; }
int64 CuteTempoAdjustForm::GetRangeStart() const { return range_start; }
void CuteTempoAdjustForm::SetRangeLength(int64 range_length) { this->range_length = range_length; }
int64 CuteTempoAdjustForm::GetRangeLength() const { return range_length; }
void CuteTempoAdjustForm::SetRangeBeats(int range_beats) { this->range_beats = range_beats; }
int CuteTempoAdjustForm::GetRangeBeats() const { return range_beats; }
double CuteTempoAdjustForm::GetTempo() const { return tempo; }
int CuteTempoAdjustForm::GetBeatsPerBar() const { return beats_per_bar; }
int CuteTempoAdjustForm::GetBeatDivisor() const { return beat_divisor; }
CuteTimeScale* CuteTempoAdjustForm::GetTimeScale() const { return time_scale; }
