#include "ProjectWindow.h"

CuteTrack::CuteTrack() {}
void CuteTrack::SetTrackId(int track_id) { this->track_id = track_id; }
int CuteTrack::GetTrackId() const { return track_id; }
void CuteTrack::SetTrackType(TrackType track_type) { this->track_type = track_type; }
CuteTrack::TrackType CuteTrack::GetTrackType() const { return track_type; }
void CuteTrack::SetName(const String& name) { this->name = name; }
const String& CuteTrack::GetName() const { return name; }
void CuteTrack::SetColor(Color color) { this->color = color; }
Color CuteTrack::GetColor() const { return color; }
void CuteTrack::SetMuted(bool muted) { this->muted = muted; }
bool CuteTrack::IsMuted() const { return muted; }
void CuteTrack::SetSolo(bool solo) { this->solo = solo; }
bool CuteTrack::IsSolo() const { return solo; }
void CuteTrack::SetArmed(bool armed) { this->armed = armed; }
bool CuteTrack::IsArmed() const { return armed; }
