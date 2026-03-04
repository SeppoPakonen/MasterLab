#include "ProjectMgmt.h"
#include <AudioCore/AudioCore.h>

class CuteCurveList {};
CuteCurveBaseCommand::CuteCurveBaseCommand(const String& name) : CuteCommand(name) {}
bool CuteCurveBaseCommand::Redo() { return Execute(true); }
bool CuteCurveBaseCommand::Undo() { return Execute(false); }
bool CuteCurveBaseCommand::Execute(bool redo) { (void)redo; return true; }
CuteCurveCommand::CuteCurveCommand(const String& name, CuteCurve* curve) : CuteCurveBaseCommand(name), curve(curve) {}
CuteCurveListCommand::CuteCurveListCommand(const String& name, CuteCurveList* curve_list) : CuteCurveBaseCommand(name), curve_list(curve_list) {}
CuteCurveSelectCommand::CuteCurveSelectCommand(CuteCurveList* curve_list, CuteCurve* current_curve) : CuteCurveListCommand("Select Curve", curve_list), current_curve(current_curve) {}
bool CuteCurveSelectCommand::Execute(bool redo) { (void)redo; return true; }
CuteCurveModeCommand::CuteCurveModeCommand(CuteCurve* curve, int mode) : CuteCurveCommand("Curve Mode", curve), mode(mode) {}
bool CuteCurveModeCommand::Execute(bool redo) { (void)redo; return true; }
CuteCurveProcessCommand::CuteCurveProcessCommand(CuteCurve* curve, bool process) : CuteCurveCommand("Curve Process", curve), process(process) {}
bool CuteCurveProcessCommand::Execute(bool redo) { (void)redo; return true; }
CuteCurveCaptureCommand::CuteCurveCaptureCommand(CuteCurve* curve, bool capture) : CuteCurveCommand("Curve Capture", curve), capture(capture) {}
bool CuteCurveCaptureCommand::Execute(bool redo) { (void)redo; return true; }
