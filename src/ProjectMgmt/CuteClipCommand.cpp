#include "ProjectMgmt.h"
#include <AudioCore/AudioCore.h>

class CuteTrack {};
CuteClipCommand::CuteClipCommand(const String& name) : CuteCommand(name) {}
CuteClipCommand::~CuteClipCommand() {}
void CuteClipCommand::AddClip(CuteClip* clip, CuteTrack* track) { Item item; item.clip = clip; item.track = track; items.Add(item); }
bool CuteClipCommand::Redo() { return true; }
bool CuteClipCommand::Undo() { return true; }
