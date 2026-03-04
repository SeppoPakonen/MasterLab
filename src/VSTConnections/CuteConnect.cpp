#include "VSTConnections.h"

namespace VSTConnections {

CutePortListItem::CutePortListItem() {}
CutePortListItem::~CutePortListItem() {}
void CutePortListItem::SetPortName(const String& port_name) { this->port_name = port_name; }
const String& CutePortListItem::GetPortName() const { return port_name; }
void CutePortListItem::SetClientName(const String& client_name) { this->client_name = client_name; }
const String& CutePortListItem::GetClientName() const { return client_name; }
String CutePortListItem::GetClientPortName() const { return client_name + ":" + port_name; }
void CutePortListItem::MarkPort(int mark) { port_mark = mark; }
int CutePortListItem::GetPortMark() const { return port_mark; }
void CutePortListItem::AddConnect(CutePortListItem* port_item) { connects.Add(port_item); }
void CutePortListItem::RemoveConnect(CutePortListItem* port_item) { int i = FindIndex(connects, port_item); if(i >= 0) connects.Remove(i); }
const Vector<CutePortListItem*>& CutePortListItem::GetConnects() const { return connects; }
void CutePortListItem::SetHilite(bool hilite) { this->hilite = hilite; }
bool CutePortListItem::IsHilite() const { return hilite; }

CuteClientListItem::CuteClientListItem() {}
CuteClientListItem::~CuteClientListItem() {}
void CuteClientListItem::SetClientName(const String& client_name) { this->client_name = client_name; }
const String& CuteClientListItem::GetClientName() const { return client_name; }
void CuteClientListItem::MarkClient(int mark) { client_mark = mark; }
int CuteClientListItem::GetClientMark() const { return client_mark; }
void CuteClientListItem::SetHilite(bool hilite) { this->hilite = hilite; }
bool CuteClientListItem::IsHilite() const { return hilite; }
void CuteClientListItem::SetOpen(bool open) { this->open = open; }
bool CuteClientListItem::IsOpen() const { return open; }

CuteClientListView::CuteClientListView() {}
void CuteClientListView::SetReadable(bool readable) { this->readable = readable; }
bool CuteClientListView::IsReadable() const { return readable; }
void CuteClientListView::SetClientNameFilter(const String& client_name) { client_name_filter = client_name; }
String CuteClientListView::GetClientNameFilter() const { return client_name_filter; }
void CuteClientListView::SetPortNameFilter(const String& port_name) { port_name_filter = port_name; }
String CuteClientListView::GetPortNameFilter() const { return port_name_filter; }

CuteConnectorView::CuteConnectorView() {}
CuteConnect::CuteConnect(CuteClientListView* output_list_view, CuteClientListView* input_list_view, CuteConnectorView* connector_view)
    : output_list_view(output_list_view), input_list_view(input_list_view), connector_view(connector_view) {}
CuteConnect::~CuteConnect() {}
bool CuteConnect::ConnectPorts(CutePortListItem* output_port, CutePortListItem* input_port) { (void)output_port; (void)input_port; return true; }
bool CuteConnect::DisconnectPorts(CutePortListItem* output_port, CutePortListItem* input_port) { (void)output_port; (void)input_port; return true; }
void CuteConnect::UpdateConnections() {}

}
