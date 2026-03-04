#include "MIDI.h"

CuteMidiTimer::CuteMidiTimer() {}
void CuteMidiTimer::Start() { running = true; }
void CuteMidiTimer::Stop() { running = false; }
bool CuteMidiTimer::IsRunning() const { return running; }
