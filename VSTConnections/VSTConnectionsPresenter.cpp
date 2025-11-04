#include "VSTConnectionsPresenter.h"

namespace VSTConnections {

VSTConnectionsPresenter::VSTConnectionsPresenter(VSTConnectionsCtrl& view) 
    : view(view), ioMatrixService(view.ioMatrixService) {
    
}

void VSTConnectionsPresenter::ConnectView() {
    // Connect the UI events to presenter methods
    LoadConnections();
}

void VSTConnectionsPresenter::LoadConnections() {
    LoadInputs();
    LoadOutputs();
    LoadGroupsFx();
    LoadExternalFx();
    LoadExternalInstruments();
    LoadStudio();
    
    view.Refresh();
}

void VSTConnectionsPresenter::LoadInputs() {
    // Load input connections from the IOMatrixService
    auto inputs = ioMatrixService.GetInputs();
    // The data will be displayed in the UI when Refresh() is called
}

void VSTConnectionsPresenter::LoadOutputs() {
    // Load output connections from the IOMatrixService
    auto outputs = ioMatrixService.GetOutputs();
    // The data will be displayed in the UI when Refresh() is called
}

void VSTConnectionsPresenter::LoadGroupsFx() {
    // Load groups and FX connections from the IOMatrixService
    auto groupsFx = ioMatrixService.GetGroupsFx();
    // The data will be displayed in the UI when Refresh() is called
}

void VSTConnectionsPresenter::LoadExternalFx() {
    // Load external FX connections from the IOMatrixService
    auto externalFx = ioMatrixService.GetExternalFx();
    // The data will be displayed in the UI when Refresh() is called
}

void VSTConnectionsPresenter::LoadExternalInstruments() {
    // Load external instrument connections from the IOMatrixService
    auto externalInstruments = ioMatrixService.GetExternalInstruments();
    // The data will be displayed in the UI when Refresh() is called
}

void VSTConnectionsPresenter::LoadStudio() {
    // Load studio connections from the IOMatrixService
    auto studio = ioMatrixService.GetStudio();
    // The data will be displayed in the UI when Refresh() is called
}

void VSTConnectionsPresenter::SaveConnections() {
    // Save connection data through IOMatrixService
    ioMatrixService.ApplyChanges();
}

void VSTConnectionsPresenter::ApplyChanges() {
    // Apply all connection changes to the system
    // This could involve updating routing in real-time
    ioMatrixService.ApplyChanges();
    PromptOK("All connection changes applied to the system.");
}

void VSTConnectionsPresenter::OnConnectionChanged() {
    // Handle connection change events
    // Could update the UI or trigger updates to the audio system
}

}