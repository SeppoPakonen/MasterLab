#include "ProjectMgmt.h"

CuteSessionCommand::CuteSessionCommand(const String& name, CuteSession* session) : name(name), session(session) {}
CuteSessionCommand::~CuteSessionCommand() {}
const String& CuteSessionCommand::GetName() const { return name; }
CuteSession* CuteSessionCommand::GetSession() const { return session; }
bool CuteSessionCommand::Redo() { return true; }
bool CuteSessionCommand::Undo() { return true; }

CuteSessionLoopCommand::CuteSessionLoopCommand(CuteSession* session, int64 start_frame, int64 end_frame)
    : CuteSessionCommand("Session Loop", session), start_frame(start_frame), end_frame(end_frame) {}
bool CuteSessionLoopCommand::Redo() { return true; }
bool CuteSessionLoopCommand::Undo() { return true; }

CuteSessionPunchCommand::CuteSessionPunchCommand(CuteSession* session, int64 start_frame, int64 end_frame)
    : CuteSessionCommand("Session Punch", session), start_frame(start_frame), end_frame(end_frame) {}
bool CuteSessionPunchCommand::Redo() { return true; }
bool CuteSessionPunchCommand::Undo() { return true; }

CuteSessionEditCommand::CuteSessionEditCommand(CuteSession* session, const CuteSession::Properties& properties)
    : CuteSessionCommand("Session Edit", session), after_properties(properties) {
    if (session)
        before_properties = session->GetProperties();
}
bool CuteSessionEditCommand::Redo() { if (session) session->GetProperties() = after_properties; return true; }
bool CuteSessionEditCommand::Undo() { if (session) session->GetProperties() = before_properties; return true; }
