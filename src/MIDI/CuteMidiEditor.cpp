#include "MIDI.h"

CuteMidiEditor::CuteMidiEditor() {}
void CuteMidiEditor::SetClip(CuteMidiClip* clip) { this->clip = clip; }
CuteMidiClip* CuteMidiEditor::GetClip() const { return clip; }
void CuteMidiEditor::SetZoom(int zoom) { this->zoom = minmax(zoom, (int)ZoomMin, (int)ZoomMax); }
int CuteMidiEditor::GetZoom() const { return zoom; }
void CuteMidiEditor::SetTool(Tool tool) { this->tool = tool; }
CuteMidiEditor::Tool CuteMidiEditor::GetTool() const { return tool; }
