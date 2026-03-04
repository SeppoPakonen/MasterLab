#include "AudioEditing.h"

CuteEditRangeForm::CuteEditRangeForm() { BuildLayout(); }
void CuteEditRangeForm::SetSession(CuteSession* session) { this->session = session; }
CuteSession* CuteEditRangeForm::GetSession() const { return session; }
void CuteEditRangeForm::SetRangeType(RangeType range_type) { this->range_type = range_type; range_list.SetIndex((int)range_type); }
CuteEditRangeForm::RangeType CuteEditRangeForm::GetRangeType() const { return range_type; }
void CuteEditRangeForm::SetStartFrame(int64 start_frame) { this->start_frame = start_frame; start_edit <<= start_frame; }
int64 CuteEditRangeForm::GetStartFrame() const { return start_frame; }
void CuteEditRangeForm::SetEndFrame(int64 end_frame) { this->end_frame = end_frame; end_edit <<= end_frame; }
int64 CuteEditRangeForm::GetEndFrame() const { return end_frame; }
void CuteEditRangeForm::BuildLayout() {
    Title("Cute Edit Range");
    range_list.Add("Session");
    range_list.Add("Loop");
    range_list.Add("Punch");
    range_list.Add("Edit");
    range_list.Add("Custom");
    Add(range_list.TopPos(8, 24).HSizePos(8, 8));
    Add(start_edit.TopPos(40, 24).HSizePos(8, 8));
    Add(end_edit.TopPos(72, 24).HSizePos(8, 8));
    Add(ok_button.SetLabel("OK").BottomPos(8, 24).RightPos(80, 64));
    Add(cancel_button.SetLabel("Cancel").BottomPos(8, 24).RightPos(8, 64));
    SetRect(0, 0, 320, 140);
}
