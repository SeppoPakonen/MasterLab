#include "ProjectWindow.h"

CuteTrackView::CuteTrackView() {
    Add(track_table.SizePos());
    track_table.AddColumn("Track");
    track_table.AddColumn("Type");
}
void CuteTrackView::SetTrackList(CuteTrackList* track_list) { this->track_list = track_list; RefreshTracks(); }
CuteTrackList* CuteTrackView::GetTrackList() const { return track_list; }
void CuteTrackView::RefreshTracks() {
    track_table.Clear();
    if (!track_list) return;
    for (int i = 0; i < track_list->GetCount(); ++i) {
        const CuteTrack* track = track_list->GetTrack(i);
        track_table.Add(track ? track->GetName() : String(), track ? AsString((int)track->GetTrackType()) : String());
    }
}
void CuteTrackView::SetCurrentTrack(int index) { current_track = index; track_table.SetCursor(index); }
int CuteTrackView::GetCurrentTrack() const { return current_track; }
