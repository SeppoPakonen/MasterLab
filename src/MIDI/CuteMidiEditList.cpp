#include "MIDI.h"

CuteMidiEditList::CuteMidiEditList() { Add(list.SizePos()); }
void CuteMidiEditList::SetEditor(CuteMidiEditor* editor) { this->editor = editor; }
CuteMidiEditor* CuteMidiEditList::GetEditor() const { return editor; }
