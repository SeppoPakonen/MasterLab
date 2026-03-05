#include "ProjectWindow.h"

CuteTrackButton::CuteTrackButton() {}
void CuteTrackButton::SetTrack(CuteTrack* track) { this->track = track; }
CuteTrack* CuteTrackButton::GetTrack() const { return track; }
void CuteTrackButton::SetButtonColor(Color color) { button_color = color; }
Color CuteTrackButton::GetButtonColor() const { return button_color; }
