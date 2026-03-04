#include "MIDI.h"

CuteMidiThumbView::CuteMidiThumbView() {}
void CuteMidiThumbView::SetEditor(CuteMidiEditor* editor) { this->editor = editor; }
CuteMidiEditor* CuteMidiThumbView::GetEditor() const { return editor; }
