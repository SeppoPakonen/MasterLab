#include "AudioCore.h"

CuteSession::Properties::Properties() {}
void CuteSession::Properties::Clear() { session_dir.Clear(); session_name.Clear(); description.Clear(); sample_rate = 48000; }
CuteSession::Properties& CuteSession::Properties::Copy(const Properties& properties) { *this = properties; return *this; }

CuteSession::Document::Document(CuteSession* session, CuteFiles* files) : session(session), files(files) {}
CuteSession* CuteSession::Document::GetSession() const { return session; }
CuteFiles* CuteSession::Document::GetFiles() const { return files; }

CuteSession::CuteSession() {}
bool CuteSession::Init() { return true; }
bool CuteSession::Open() { return true; }
void CuteSession::Close() {}
void CuteSession::Clear() { properties.Clear(); track_names.Clear(); }
void CuteSession::SetSessionDir(const String& session_dir) { properties.session_dir = session_dir; }
const String& CuteSession::GetSessionDir() const { return properties.session_dir; }
void CuteSession::SetSessionName(const String& session_name) { properties.session_name = session_name; }
const String& CuteSession::GetSessionName() const { return properties.session_name; }
CuteSession::Properties& CuteSession::GetProperties() { return properties; }
const CuteSession::Properties& CuteSession::GetProperties() const { return properties; }
void CuteSession::AddTrack(const String& track_name) { track_names.Add(track_name); }
void CuteSession::InsertTrack(int index, const String& track_name) { if (index < 0 || index > track_names.GetCount()) index = track_names.GetCount(); track_names.Insert(index, track_name); }
void CuteSession::MoveTrack(int from, int to) { if (from < 0 || from >= track_names.GetCount() || to < 0 || to >= track_names.GetCount() || from == to) return; String track_name = track_names[from]; track_names.Remove(from); track_names.Insert(to, track_name); }
void CuteSession::UnlinkTrack(int index) { if (index >= 0 && index < track_names.GetCount()) track_names.Remove(index); }
int CuteSession::GetTrackCount() const { return track_names.GetCount(); }
const String& CuteSession::GetTrackName(int index) const { return track_names[index]; }
CuteSessionCursor* CuteSession::CreateSessionCursor(int64 frame) { return new CuteSessionCursor(this, frame); }
