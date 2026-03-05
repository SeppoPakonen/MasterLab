#include "ProjectWindow.h"

CuteTracks::CuteTracks() {}
void CuteTracks::SetTrackList(CuteTrackList* track_list) { this->track_list = track_list; }
CuteTrackList* CuteTracks::GetTrackList() const { return track_list; }
void CuteTracks::SetCurrentTrack(int index) { current_track = index; }
int CuteTracks::GetCurrentTrack() const { return current_track; }
void CuteTracks::SelectAll() { selected_tracks.Clear(); if (!track_list) return; for (int i = 0; i < track_list->GetCount(); ++i) selected_tracks.Add(i); }
void CuteTracks::ClearSelection() { selected_tracks.Clear(); }
