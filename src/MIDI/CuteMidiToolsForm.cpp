#include "MIDI.h"

CuteMidiToolsForm::CuteMidiToolsForm() { Add(tool_list.TopPos(8,24).HSizePos(8,8)); Add(amount.TopPos(40,24).HSizePos(8,8)); Add(apply_button.SetLabel("Apply").BottomPos(8,24).RightPos(80,64)); Add(cancel_button.SetLabel("Cancel").BottomPos(8,24).RightPos(8,64)); SetRect(0,0,320,140); }
void CuteMidiToolsForm::SetClip(CuteMidiClip* clip) { this->clip = clip; }
CuteMidiClip* CuteMidiToolsForm::GetClip() const { return clip; }
