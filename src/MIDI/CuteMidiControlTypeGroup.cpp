#include "MIDI.h"

CuteMidiControlTypeGroup::CuteMidiControlTypeGroup() {
    Add(type_list.SizePos());
    type_list.Add("Controller");
    type_list.Add("Note On");
    type_list.Add("Note Off");
}
void CuteMidiControlTypeGroup::SetControlType(int control_type) { this->control_type = control_type; type_list.SetIndex(control_type); }
int CuteMidiControlTypeGroup::GetControlType() const { return control_type; }
