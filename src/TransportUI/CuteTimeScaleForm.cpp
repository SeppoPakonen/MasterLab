#include "TransportUI.h"

CuteTimeScaleForm::CuteTimeScaleForm() { Title("Time Scale"); Sizeable().Zoomable(); }
void CuteTimeScaleForm::SetTimeScale(CuteTimeScale* time_scale) { this->time_scale = time_scale; }
CuteTimeScale* CuteTimeScaleForm::GetTimeScale() const { return time_scale; }
void CuteTimeScaleForm::SetFrame(int64 frame) { this->frame = frame; }
int64 CuteTimeScaleForm::GetFrame() const { return frame; }
int CuteTimeScaleForm::GetBar() const { return (int)(frame / (48000 * 4)); }
bool CuteTimeScaleForm::IsDirty() const { return dirty_flags != 0; }
