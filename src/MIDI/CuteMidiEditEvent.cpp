#include "MIDI.h"

CuteMidiEditEventScale::CuteMidiEditEventScale() {}
void CuteMidiEditEventScale::SetZoom(int zoom) { this->zoom = zoom; }
int CuteMidiEditEventScale::GetZoom() const { return zoom; }
CuteMidiEditEvent::CuteMidiEditEvent() {}
void CuteMidiEditEvent::SetEditor(CuteMidiEditor* editor) { this->editor = editor; }
CuteMidiEditor* CuteMidiEditEvent::GetEditor() const { return editor; }
void CuteMidiEditEvent::RefreshView() { Refresh(); }
