#include "MIDI.h"

CuteMidiControlForm::CuteMidiControlForm() {
    Title("Cute MIDI Control");
    Add(control_type.TopPos(8, 24).LeftPos(8, 120));
    Add(control_channel.TopPos(8, 24).LeftPos(136, 60));
    Add(control_param.TopPos(40, 24).HSizePos(8, 8));
    Add(logarithmic.TopPos(72, 20).LeftPos(8, 160));
    Add(inverted.TopPos(96, 20).LeftPos(8, 160));
    Add(bipolar.TopPos(120, 20).LeftPos(8, 160));
    Add(ok_button.SetLabel("OK").BottomPos(8, 24).RightPos(80, 64));
    Add(cancel_button.SetLabel("Cancel").BottomPos(8, 24).RightPos(8, 64));
    SetRect(0, 0, 360, 190);
}
void CuteMidiControlForm::SetControl(const CuteMidiControl::MapVal& map_val) { logarithmic = map_val.logarithmic; inverted = map_val.inverted; bipolar = map_val.bipolar; }
CuteMidiControl::MapVal CuteMidiControlForm::GetControl() const { CuteMidiControl::MapVal map_val; map_val.logarithmic = logarithmic; map_val.inverted = inverted; map_val.bipolar = bipolar; return map_val; }
