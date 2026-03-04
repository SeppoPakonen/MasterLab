#include "MIDI.h"

CuteMidiEditTime::CuteMidiEditTime() {}
void CuteMidiEditTime::SetEditor(CuteMidiEditor* editor) { this->editor = editor; }
CuteMidiEditor* CuteMidiEditTime::GetEditor() const { return editor; }
void CuteMidiEditTime::SetFrame(unsigned long frame) { this->frame = frame; }
unsigned long CuteMidiEditTime::GetFrame() const { return frame; }
