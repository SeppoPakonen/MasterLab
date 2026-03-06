#include "VSTConnections.h"

namespace VSTConnections {

VSTConnectionsWindow::VSTConnectionsWindow() {
    SizePos();
    InitLayout();
}

void VSTConnectionsWindow::InitLayout() {
    Add(connectionsCtrl.SizePos());
}

void VSTConnectionsWindow::Refresh() {
    connectionsCtrl.Refresh();
}

void VSTConnectionsWindow::RefreshConnections() {
    connectionsCtrl.Refresh();
}

}
