#include "ProjectMgmt.h"

CuteBusCommand::CuteBusCommand(const String& name, CuteBus* bus) : CuteCommand(name), bus(bus) {}
CuteCreateBusCommand::CuteCreateBusCommand(CuteBus* bus) : CuteBusCommand("Create Bus", bus) {}
bool CuteCreateBusCommand::Redo() { return bus != nullptr; }
bool CuteCreateBusCommand::Undo() { return bus != nullptr; }
CuteUpdateBusCommand::CuteUpdateBusCommand(CuteBus* bus) : CuteBusCommand("Update Bus", bus) {}
bool CuteUpdateBusCommand::Redo() { return bus != nullptr; }
bool CuteUpdateBusCommand::Undo() { return bus != nullptr; }
CuteDeleteBusCommand::CuteDeleteBusCommand(CuteBus* bus) : CuteBusCommand("Delete Bus", bus) {}
bool CuteDeleteBusCommand::Redo() { return bus != nullptr; }
bool CuteDeleteBusCommand::Undo() { return bus != nullptr; }
CuteMoveBusCommand::CuteMoveBusCommand(CuteBus* bus, int delta) : CuteBusCommand("Move Bus", bus), delta(delta) {}
bool CuteMoveBusCommand::Redo() { return bus != nullptr || delta == 0; }
bool CuteMoveBusCommand::Undo() { return bus != nullptr || delta == 0; }
CuteBusMonitorCommand::CuteBusMonitorCommand(CuteBus* bus, bool monitor) : CuteBusCommand("Bus Monitor", bus), monitor(monitor) {}
bool CuteBusMonitorCommand::Redo() { if(bus) bus->SetMonitor(monitor); return bus != nullptr; }
bool CuteBusMonitorCommand::Undo() { if(bus) bus->SetMonitor(!monitor); return bus != nullptr; }
CuteBusGainCommand::CuteBusGainCommand(CuteBus* bus, double gain) : CuteBusCommand("Bus Gain", bus), gain(gain) {}
bool CuteBusGainCommand::Redo() { if(bus) bus->SetGain(gain); return bus != nullptr; }
bool CuteBusGainCommand::Undo() { return bus != nullptr; }
CuteBusPanningCommand::CuteBusPanningCommand(CuteBus* bus, double panning) : CuteBusCommand("Bus Panning", bus), panning(panning) {}
bool CuteBusPanningCommand::Redo() { if(bus) bus->SetPanning(panning); return bus != nullptr; }
bool CuteBusPanningCommand::Undo() { return bus != nullptr; }
