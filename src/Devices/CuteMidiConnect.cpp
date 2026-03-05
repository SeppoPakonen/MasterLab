#include "Devices.h"

Vector<String> CuteMidiConnect::icons;
int CuteMidiConnect::icon_ref_count = 0;

CuteMidiPortItem::CuteMidiPortItem(CuteMidiClientItem* client_item, unsigned long port_flags) : port_flags(port_flags) { (void)client_item; }
CuteMidiPortItem::~CuteMidiPortItem() {}
void CuteMidiPortItem::UpdatePortName() {}

CuteMidiClientItem::CuteMidiClientItem(CuteMidiClientListView* client_list_view) { (void)client_list_view; }
CuteMidiClientItem::~CuteMidiClientItem() {}
void CuteMidiClientItem::UpdateClientName() {}

CuteMidiClientListView::CuteMidiClientListView() {}
CuteMidiClientListView::~CuteMidiClientListView() {}
void* CuteMidiClientListView::GetAlsaClient() const { return nullptr; }
int CuteMidiClientListView::UpdateClientPorts() { return 0; }

CuteMidiConnect::CuteMidiConnect(CuteMidiClientListView* output_list_view, CuteMidiClientListView* input_list_view, CuteConnectorView* connector_view)
    : output_list_view(output_list_view), input_list_view(input_list_view), connector_view(connector_view) { CreateIcons(); }
CuteMidiConnect::~CuteMidiConnect() { DeleteIcons(); }
void* CuteMidiConnect::GetAlsaClient() const { return nullptr; }
String CuteMidiConnect::GetIcon(int icon_index) { return icon_index >= 0 && icon_index < icons.GetCount() ? icons[icon_index] : String(); }
bool CuteMidiConnect::ConnectPorts(CutePortListItem* output_port, CutePortListItem* input_port) { (void)output_port; (void)input_port; return true; }
bool CuteMidiConnect::DisconnectPorts(CutePortListItem* output_port, CutePortListItem* input_port) { (void)output_port; (void)input_port; return true; }
void CuteMidiConnect::UpdateConnections() {}
void CuteMidiConnect::DisconnectPortsUpdate(CutePortListItem* output_port, CutePortListItem* input_port) { (void)output_port; (void)input_port; }
void CuteMidiConnect::CreateIcons() { if(icon_ref_count++ == 0) { icons.SetCount(IconCount); icons[ClientInput] = "midi-client-input"; icons[ClientOutput] = "midi-client-output"; icons[PortInput] = "midi-port-input"; icons[PortOutput] = "midi-port-output"; icons[PortPhysicalInput] = "midi-port-physical-input"; icons[PortPhysicalOutput] = "midi-port-physical-output"; } }
void CuteMidiConnect::DeleteIcons() { if(--icon_ref_count <= 0) { icon_ref_count = 0; icons.Clear(); } }
