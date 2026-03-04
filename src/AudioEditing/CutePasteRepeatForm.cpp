#include "AudioEditing.h"

CutePasteRepeatForm::CutePasteRepeatForm() { Add(repeat_count_edit.TopPos(8,24).HSizePos(8,8)); Add(repeat_period_edit.TopPos(40,24).HSizePos(8,8)); Add(ok_button.SetLabel("OK").BottomPos(8,24).RightPos(80,64)); Add(cancel_button.SetLabel("Cancel").BottomPos(8,24).RightPos(8,64)); SetRect(0,0,320,140); }
void CutePasteRepeatForm::SetRepeatCount(unsigned short repeat_count) { this->repeat_count = repeat_count; repeat_count_edit <<= (int)repeat_count; }
unsigned short CutePasteRepeatForm::GetRepeatCount() const { return repeat_count; }
void CutePasteRepeatForm::SetRepeatPeriod(unsigned long repeat_period) { this->repeat_period = repeat_period; repeat_period_edit <<= (int)repeat_period; }
unsigned long CutePasteRepeatForm::GetRepeatPeriod() const { return repeat_period; }
