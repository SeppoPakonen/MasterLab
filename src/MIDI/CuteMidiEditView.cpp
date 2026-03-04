#include "MIDI.h"

CuteMidiEditView::CuteMidiEditView() {}
void CuteMidiEditView::SetEditor(CuteMidiEditor* editor) { this->editor = editor; }
CuteMidiEditor* CuteMidiEditView::GetEditor() const { return editor; }
void CuteMidiEditView::SetSequence(CuteMidiSequence* sequence) { this->sequence = sequence; }
CuteMidiSequence* CuteMidiEditView::GetSequence() const { return sequence; }
