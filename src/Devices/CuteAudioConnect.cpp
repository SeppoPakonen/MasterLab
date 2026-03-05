#include "Devices.h"

Vector<String> CuteAudioConnect::icons;
int CuteAudioConnect::icon_ref_count = 0;

CuteAudioPortItem::CuteAudioPortItem(CuteAudioClientItem* client_item, unsigned long port_flags)
	: port_flags(port_flags) {
	(void)client_item;
}

CuteAudioPortItem::~CuteAudioPortItem() {
}

void CuteAudioPortItem::UpdatePortName() {
}

CuteAudioClientItem::CuteAudioClientItem(CuteAudioClientListView* client_list_view) {
	(void)client_list_view;
}

CuteAudioClientItem::~CuteAudioClientItem() {
}

void CuteAudioClientItem::UpdateClientName() {
}

CuteAudioClientListView::CuteAudioClientListView() {
}

CuteAudioClientListView::~CuteAudioClientListView() {
}

void* CuteAudioClientListView::GetJackClient() const {
	return nullptr;
}

int CuteAudioClientListView::UpdateClientPorts() {
	return 0;
}

CuteAudioConnect::CuteAudioConnect(CuteAudioClientListView* output_list_view, CuteAudioClientListView* input_list_view, CuteConnectorView* connector_view)
	: output_list_view(output_list_view), input_list_view(input_list_view), connector_view(connector_view) {
	CreateIcons();
}

CuteAudioConnect::~CuteAudioConnect() {
	DeleteIcons();
}

void* CuteAudioConnect::GetJackClient() const {
	return nullptr;
}

String CuteAudioConnect::GetIcon(int icon_index) {
	if(icon_index < 0 || icon_index >= icons.GetCount())
		return String();
	return icons[icon_index];
}

bool CuteAudioConnect::ConnectPorts(CutePortListItem* output_port, CutePortListItem* input_port) {
	(void)output_port;
	(void)input_port;
	return true;
}

bool CuteAudioConnect::DisconnectPorts(CutePortListItem* output_port, CutePortListItem* input_port) {
	(void)output_port;
	(void)input_port;
	return true;
}

void CuteAudioConnect::UpdateConnections() {
}

void CuteAudioConnect::DisconnectPortsUpdate(CutePortListItem* output_port, CutePortListItem* input_port) {
	(void)output_port;
	(void)input_port;
}

void CuteAudioConnect::CreateIcons() {
	if(icon_ref_count++ == 0) {
		icons.SetCount(IconCount);
		icons[ClientIn] = "audio-client-in";
		icons[ClientOut] = "audio-client-out";
		icons[PortIn] = "audio-port-in";
		icons[PortOut] = "audio-port-out";
		icons[PortPhysIn] = "audio-port-phys-in";
		icons[PortPhysOut] = "audio-port-phys-out";
	}
}

void CuteAudioConnect::DeleteIcons() {
	if(--icon_ref_count <= 0) {
		icon_ref_count = 0;
		icons.Clear();
	}
}
