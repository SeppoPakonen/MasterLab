#include "AudioEditing.h"

CuteTakeRangeForm::CuteTakeRangeForm() { Title("Take Range"); }
void CuteTakeRangeForm::SetClip(CuteAudioClip* clip) { this->clip = clip; }
CuteAudioClip* CuteTakeRangeForm::GetClip() const { return clip; }
int64 CuteTakeRangeForm::GetTakeStart() const { return take_start; }
int64 CuteTakeRangeForm::GetTakeEnd() const { return take_end; }
int CuteTakeRangeForm::GetCurrentTake() const { return current_take; }
