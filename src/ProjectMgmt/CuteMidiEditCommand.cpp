#include "ProjectMgmt.h"

CuteMidiEditCommand::CuteMidiEditCommand(const String& name, CuteMidiClip* clip, CommandType command_type) : CuteCommand(name), clip(clip), command_type(command_type) {}
bool CuteMidiEditCommand::Redo() { return clip != nullptr || command_type == None; }
bool CuteMidiEditCommand::Undo() { return clip != nullptr || command_type == None; }
CuteMidiEditCommand::CommandType CuteMidiEditCommand::GetCommandType() const { return command_type; }
