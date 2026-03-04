#include "ProjectMgmt.h"

CuteMidiControlObserverCommand::CuteMidiControlObserverCommand(const String& name, CuteMidiControlObserver* observer) : CuteCommand(name), observer(observer) {}
CuteMidiControlObserverMapCommand::CuteMidiControlObserverMapCommand(CuteMidiControlObserver* observer) : CuteMidiControlObserverCommand("Map MIDI Control", observer) {}
bool CuteMidiControlObserverMapCommand::Redo() { return observer != nullptr; }
bool CuteMidiControlObserverMapCommand::Undo() { return observer != nullptr; }
CuteMidiControlObserverUnmapCommand::CuteMidiControlObserverUnmapCommand(CuteMidiControlObserver* observer) : CuteMidiControlObserverCommand("Unmap MIDI Control", observer) {}
bool CuteMidiControlObserverUnmapCommand::Redo() { return observer != nullptr; }
bool CuteMidiControlObserverUnmapCommand::Undo() { return observer != nullptr; }
