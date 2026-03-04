#include "MIDI.h"

CuteMmcEvent::CuteMmcEvent(Command command) : command(command) {}
void CuteMmcEvent::SetCommand(Command command) { this->command = command; }
CuteMmcEvent::Command CuteMmcEvent::GetCommand() const { return command; }
