#include "ExportAudioMixdown.h"

CuteExportForm::CuteExportForm() { BuildLayout(); }
CuteExportForm::~CuteExportForm() {}
void CuteExportForm::SetSession(CuteSession* session) { this->session = session; }
CuteSession* CuteExportForm::GetSession() const { return session; }
void CuteExportForm::SetRangeType(RangeType range_type) { this->range_type = range_type; range_list.SetIndex((int)range_type); }
CuteExportForm::RangeType CuteExportForm::GetRangeType() const { return range_type; }
void CuteExportForm::SetOutputPath(const String& output_path) { this->output_path = output_path; path_edit <<= output_path; }
const String& CuteExportForm::GetOutputPath() const { return output_path; }
void CuteExportForm::BuildLayout() {
    Title("Cute Export");
    range_list.Add("Session");
    range_list.Add("Loop");
    range_list.Add("Punch");
    range_list.Add("Edit");
    range_list.Add("Custom");
    Add(range_list.TopPos(8, 24).HSizePos(8, 8));
    Add(path_edit.TopPos(40, 24).HSizePos(8, 80));
    Add(browse_button.SetLabel("Browse").TopPos(40, 24).RightPos(8, 64));
    Add(export_button.SetLabel("Export").BottomPos(8, 24).RightPos(80, 64));
    Add(cancel_button.SetLabel("Cancel").BottomPos(8, 24).RightPos(8, 64));
    SetRect(0, 0, 420, 140);
}
CuteExportTrackForm::CuteExportTrackForm() { Title("Cute Track Export"); }
CuteExportClipForm::CuteExportClipForm() { Title("Cute Clip Export"); }
