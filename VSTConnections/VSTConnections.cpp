#include "VSTConnections.h"

namespace VSTConnections {

VSTConnectionsWindow::VSTConnectionsWindow() {
    CtrlLayout(*this, "VST Connections");
    InitLayout();
}

void VSTConnectionsWindow::InitLayout() {
    AddFrame(toolBar);
    toolBar.Set(THISBACK(ToolMenu));
    
    Add(connectionsCtrl);
}

void VSTConnectionsWindow::ToolMenu(Bar& bar) {
    bar.Add("Refresh", CtrlImg::refresh(), THISBACK(Refresh));
    bar.Add("Save", CtrlImg::save(), THISBACK(Refresh));
}

void VSTConnectionsWindow::Refresh() {
    connectionsCtrl.Refresh();
}

void VSTConnectionsWindow::RefreshConnections() {
    connectionsCtrl.Refresh();
}

}