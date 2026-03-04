#include "AudioCore.h"

CuteSessionCursor::CuteSessionCursor(CuteSession* session, int64 frame) : session(session), frame(frame) {}
CuteSession* CuteSessionCursor::GetSession() const { return session; }
void CuteSessionCursor::Seek(int64 frame, bool sync) { this->frame = frame; if (sync) sync_type = 1; }
int64 CuteSessionCursor::GetFrame() const { return frame; }
int64 CuteSessionCursor::GetFrameTime() const { return frame; }
int64 CuteSessionCursor::GetFrameTimeEx() const { return frame; }
void CuteSessionCursor::SetSyncType(int sync_type) { this->sync_type = sync_type; }
int CuteSessionCursor::GetSyncType() const { return sync_type; }
void CuteSessionCursor::AddTrack(const String& track_name) { cursor_tracks.Add(track_name); }
void CuteSessionCursor::UpdateTrack(int index, const String& track_name) { if (index >= 0 && index < cursor_tracks.GetCount()) cursor_tracks[index] = track_name; }
void CuteSessionCursor::RemoveTrack(int index) { if (index >= 0 && index < cursor_tracks.GetCount()) cursor_tracks.Remove(index); }
