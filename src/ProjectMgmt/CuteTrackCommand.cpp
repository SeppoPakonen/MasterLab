#include "ProjectMgmt.h"

CuteTrackCommand::CuteTrackCommand(const String& name, CuteSession* session) : name(name), session(session) {}
CuteTrackCommand::~CuteTrackCommand() {}
bool CuteTrackCommand::Redo() { return true; }
bool CuteTrackCommand::Undo() { return true; }

CuteAddTrackCommand::CuteAddTrackCommand(CuteSession* session, const String& track_name)
    : CuteTrackCommand("Add Track", session), track_name(track_name) {}
bool CuteAddTrackCommand::Redo() { if (session) { session->AddTrack(track_name); track_index = session->GetTrackCount() - 1; } return true; }
bool CuteAddTrackCommand::Undo() { if (session && track_index >= 0) session->UnlinkTrack(track_index); return true; }

CuteRemoveTrackCommand::CuteRemoveTrackCommand(CuteSession* session, int track_index)
    : CuteTrackCommand("Remove Track", session), track_index(track_index) {}
bool CuteRemoveTrackCommand::Redo() { if (session && track_index >= 0 && track_index < session->GetTrackCount()) { removed_track_name = session->GetTrackName(track_index); session->UnlinkTrack(track_index); } return true; }
bool CuteRemoveTrackCommand::Undo() { if (session && track_index >= 0) session->InsertTrack(track_index, removed_track_name); return true; }

CuteMoveTrackCommand::CuteMoveTrackCommand(CuteSession* session, int from_index, int to_index)
    : CuteTrackCommand("Move Track", session), from_index(from_index), to_index(to_index) {}
bool CuteMoveTrackCommand::Redo() { if (session) session->MoveTrack(from_index, to_index); return true; }
bool CuteMoveTrackCommand::Undo() { if (session) session->MoveTrack(to_index, from_index); return true; }
