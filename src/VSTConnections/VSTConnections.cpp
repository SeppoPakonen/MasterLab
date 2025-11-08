#include "VSTConnections.h"

namespace VSTConnections {

VSTConnectionsWindow::VSTConnectionsWindow() {
    CtrlLayout(*this, "VST Connections");
    InitLayout();
}

void VSTConnectionsWindow::InitLayout() {
    Add(connectionsCtrl);
}

void VSTConnectionsWindow::Refresh() {
    connectionsCtrl.Refresh();
}

void VSTConnectionsWindow::RefreshConnections() {
    connectionsCtrl.Refresh();
}

}