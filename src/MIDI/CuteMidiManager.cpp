#include "MIDI.h"

CuteMidiInputBuffer::CuteMidiInputBuffer(unsigned int buffer_size) : CuteMidiBuffer(buffer_size) {}
CuteMidiOutputBuffer::CuteMidiOutputBuffer() {}
void CuteMidiOutputBuffer::ProcessSync() {}
CuteMidiManager::CuteMidiManager() {}
CuteMidiManager::~CuteMidiManager() {}
void CuteMidiManager::Open() { opened = true; }
void CuteMidiManager::Close() { opened = false; }
bool CuteMidiManager::IsOpen() const { return opened; }
void CuteMidiManager::ProcessSync() {}
