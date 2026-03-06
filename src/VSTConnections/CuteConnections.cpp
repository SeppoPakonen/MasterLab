#include "VSTConnections.h"
#include "CuteConnectForm.h"
namespace VSTConnections {

CuteConnections::CuteConnections() { connect_form = new CuteConnectForm(); }
CuteConnections::~CuteConnections() { delete connect_form; }
CuteConnectForm* CuteConnections::GetConnectForm() const { return connect_form; }
void CuteConnections::ShowBus(CuteBus* bus, int bus_mode) { (void)bus; (void)bus_mode; }
void CuteConnections::RefreshAll() {}
void CuteConnections::Clear() {}
void CuteConnections::Reset() {}
}
