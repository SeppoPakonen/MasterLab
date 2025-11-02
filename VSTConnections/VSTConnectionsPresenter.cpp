#include "VSTConnectionsPresenter.h"

namespace VSTConnections {

VSTConnectionsPresenter::VSTConnectionsPresenter(VSTConnectionsCtrl& view) 
    : view(view) {
    
}

void VSTConnectionsPresenter::ConnectView() {
    // Connect the UI events to presenter methods
    LoadConnections();
}

void VSTConnectionsPresenter::LoadConnections() {
    // Load connection data from the IOMatrixService
    view.Refresh();
}

void VSTConnectionsPresenter::SaveConnections() {
    // Save connection data through IOMatrixService
}

void VSTConnectionsPresenter::ApplyChanges() {
    // Apply all connection changes to the system
    // This could involve updating routing in real-time
}

void VSTConnectionsPresenter::OnConnectionChanged() {
    // Handle connection change events
}

}