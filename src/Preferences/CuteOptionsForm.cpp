#include "Preferences.h"

CuteOptionsForm::CuteOptionsForm() { Add(tabs.VSizePos(0,32).HSizePos()); Add(ok_button.SetLabel("OK").BottomPos(4,24).RightPos(80,64)); Add(cancel_button.SetLabel("Cancel").BottomPos(4,24).RightPos(8,64)); SetRect(0,0,760,520); }
void CuteOptionsForm::SetOptions(CuteOptions* options) { this->options = options; }
CuteOptions* CuteOptionsForm::GetOptions() const { return options; }
bool CuteOptionsForm::IsDirtyMeterColors() const { return dirty_meter_colors != 0; }
bool CuteOptionsForm::IsDirtyCustomColorThemes() const { return dirty_custom_color_themes != 0; }
