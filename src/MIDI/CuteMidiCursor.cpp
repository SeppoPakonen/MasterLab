#include "MIDI.h"

CuteMidiCursor::CuteMidiCursor(CuteMidiSequence* sequence) : sequence(sequence) {}
void CuteMidiCursor::SetSequence(CuteMidiSequence* sequence) { this->sequence = sequence; }
CuteMidiSequence* CuteMidiCursor::GetSequence() const { return sequence; }
void CuteMidiCursor::Reset() { index = -1; }
int CuteMidiCursor::Seek(unsigned long time) { (void)time; return ++index; }
