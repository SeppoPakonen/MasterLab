#include "VSTConnections.h"

namespace VSTConnections {
class CuteBus {};
CuteBusForm::CuteBusForm() {}
void CuteBusForm::SetBus(CuteBus* bus) { this->bus = bus; }
CuteBus* CuteBusForm::GetBus() const { return bus; }
bool CuteBusForm::IsDirty() const { return dirty_count != 0; }
unsigned int CuteBusForm::GetFlags() const { return 0; }
void CuteBusForm::ShowBus(CuteBus* bus) { this->bus = bus; }
bool CuteBusForm::UpdateBus(CuteBus* bus) { this->bus = bus; return true; }
void CuteBusForm::UpdateMidiInstruments() {}
void CuteBusForm::UpdateMidiSysex() {}
void CuteBusForm::ResetPluginLists() {}
void CuteBusForm::RefreshBuses() {}
void CuteBusForm::Reject() {}
void CuteBusForm::SelectBus() {}
void CuteBusForm::MoveUpBus() {}
void CuteBusForm::MoveDownBus() {}
void CuteBusForm::CreateBus() {}
void CuteBusForm::UpdateBus() {}
void CuteBusForm::DeleteBus() {}
void CuteBusForm::Changed() { dirty_count++; }
void CuteBusForm::StabilizeForm() {}
void CuteBusForm::ContextMenu() {}
void CuteBusForm::MidiSysex() {}
}
