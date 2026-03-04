#include "ProjectMgmt.h"

CuteTimeScaleNodeCommand::CuteTimeScaleNodeCommand(const String& name, CuteTimeScale* time_scale, int64 frame, double tempo, int beat_type, int beats_per_bar, int beat_divisor)
    : name(name), time_scale(time_scale), frame(frame), tempo(tempo), beat_type(beat_type), beats_per_bar(beats_per_bar), beat_divisor(beat_divisor) {}
CuteTimeScaleNodeCommand::~CuteTimeScaleNodeCommand() {}
bool CuteTimeScaleNodeCommand::Redo() { return true; }
bool CuteTimeScaleNodeCommand::Undo() { return true; }
CuteTimeScale* CuteTimeScaleNodeCommand::GetTimeScale() const { return time_scale; }
int64 CuteTimeScaleNodeCommand::GetFrame() const { return frame; }
double CuteTimeScaleNodeCommand::GetTempo() const { return tempo; }
int CuteTimeScaleNodeCommand::GetBeatType() const { return beat_type; }
int CuteTimeScaleNodeCommand::GetBeatsPerBar() const { return beats_per_bar; }
int CuteTimeScaleNodeCommand::GetBeatDivisor() const { return beat_divisor; }
bool CuteTimeScaleAddNodeCommand::Redo() { return true; }
bool CuteTimeScaleAddNodeCommand::Undo() { return true; }
bool CuteTimeScaleUpdateNodeCommand::Redo() { return true; }
bool CuteTimeScaleUpdateNodeCommand::Undo() { return true; }
bool CuteTimeScaleRemoveNodeCommand::Redo() { return true; }
bool CuteTimeScaleRemoveNodeCommand::Undo() { return true; }
bool CuteTimeScaleMoveNodeCommand::Redo() { return true; }
bool CuteTimeScaleMoveNodeCommand::Undo() { return true; }

CuteTimeScaleMarkerCommand::CuteTimeScaleMarkerCommand(const String& name, CuteTimeScale* time_scale, int64 frame, const String& text, Color color, int accidentals, int mode)
    : name(name), time_scale(time_scale), frame(frame), text(text), color(color), accidentals(accidentals), mode(mode) {}
CuteTimeScaleMarkerCommand::~CuteTimeScaleMarkerCommand() {}
bool CuteTimeScaleMarkerCommand::Redo() { return true; }
bool CuteTimeScaleMarkerCommand::Undo() { return true; }
bool CuteTimeScaleAddMarkerCommand::Redo() { return true; }
bool CuteTimeScaleAddMarkerCommand::Undo() { return true; }
bool CuteTimeScaleUpdateMarkerCommand::Redo() { return true; }
bool CuteTimeScaleUpdateMarkerCommand::Undo() { return true; }
bool CuteTimeScaleRemoveMarkerCommand::Redo() { return true; }
bool CuteTimeScaleRemoveMarkerCommand::Undo() { return true; }
bool CuteTimeScaleAddKeySignatureCommand::Redo() { return true; }
bool CuteTimeScaleAddKeySignatureCommand::Undo() { return true; }
bool CuteTimeScaleUpdateKeySignatureCommand::Redo() { return true; }
bool CuteTimeScaleUpdateKeySignatureCommand::Undo() { return true; }
bool CuteTimeScaleRemoveKeySignatureCommand::Redo() { return true; }
bool CuteTimeScaleRemoveKeySignatureCommand::Undo() { return true; }
