#include "ProjectWindow.h"

CuteTrackList::CuteTrackList() {}
int CuteTrackList::GetCount() const { return tracks.GetCount(); }
void CuteTrackList::AddTrack(const CuteTrack& track) { tracks.Add().SetTrackId(track.GetTrackId()); tracks.Top() = track; }
void CuteTrackList::InsertTrack(int index, const CuteTrack& track) { if (index < 0 || index > tracks.GetCount()) index = tracks.GetCount(); tracks.Insert(index) = track; }
void CuteTrackList::RemoveTrack(int index) { if (index >= 0 && index < tracks.GetCount()) tracks.Remove(index); }
void CuteTrackList::MoveTrack(int from, int to) { if (from < 0 || from >= tracks.GetCount() || to < 0 || to >= tracks.GetCount() || from == to) return; CuteTrack moved = tracks[from]; tracks.Remove(from); tracks.Insert(to) = moved; }
CuteTrack* CuteTrackList::GetTrack(int index) { return index >= 0 && index < tracks.GetCount() ? &tracks[index] : nullptr; }
const CuteTrack* CuteTrackList::GetTrack(int index) const { return index >= 0 && index < tracks.GetCount() ? &tracks[index] : nullptr; }
