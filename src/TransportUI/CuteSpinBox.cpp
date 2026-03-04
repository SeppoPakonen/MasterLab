#include "TransportUI.h"

CuteSpinBox::CuteSpinBox() {}
void CuteSpinBox::SetEditMode(EditMode edit_mode) { this->edit_mode = edit_mode; }
CuteSpinBox::EditMode CuteSpinBox::GetEditMode() const { return edit_mode; }
CuteTimeSpinBox::CuteTimeSpinBox() {}
void CuteTimeSpinBox::SetTimeScale(CuteTimeScale* time_scale) { this->time_scale = time_scale; }
CuteTimeScale* CuteTimeSpinBox::GetTimeScale() const { return time_scale; }
void CuteTimeSpinBox::SetDisplayFormat(int display_format) { this->display_format = display_format; UpdateDisplayFormat(); }
int CuteTimeSpinBox::GetDisplayFormat() const { return display_format; }
void CuteTimeSpinBox::UpdateDisplayFormat() { SetData(AsString(value)); }
void CuteTimeSpinBox::SetValue(int64 value) { this->value = value; UpdateDisplayFormat(); }
int64 CuteTimeSpinBox::GetValue() const { return value; }
CuteTempoSpinBox::CuteTempoSpinBox() {}
void CuteTempoSpinBox::SetTempo(double tempo) { this->tempo = tempo; SetData(AsString(tempo)); }
double CuteTempoSpinBox::GetTempo() const { return tempo; }
void CuteTempoSpinBox::SetBeatsPerBar(int beats_per_bar) { this->beats_per_bar = beats_per_bar; }
int CuteTempoSpinBox::GetBeatsPerBar() const { return beats_per_bar; }
void CuteTempoSpinBox::SetBeatDivisor(int beat_divisor) { this->beat_divisor = beat_divisor; }
int CuteTempoSpinBox::GetBeatDivisor() const { return beat_divisor; }
