#include "VSTConnectionsCtrl.h"

namespace VSTConnections {

VSTTabPane::VSTTabPane() {
    AddFrame(gridCtrl);
    gridCtrl.AddColumn("Source", 150);
    gridCtrl.AddColumn("Destination", 150);
    gridCtrl.AddColumn("Channel", 80);
    gridCtrl.AddColumn("Status", 100);
    
    AddBottom(applyBtn);
    applyBtn.SetLabel("Apply").SizePos(4, 4);
    applyBtn <<= THISBACK(ApplyChanges);
}

void VSTTabPane::Refresh() {
    // Refresh the grid with current connection data
    gridCtrl.Clear();
    
    // Add some sample data for now
    gridCtrl.Add("Input 1", "Plugin A", "1", "Active");
    gridCtrl.Add("Input 2", "Plugin B", "2", "Inactive");
}

void VSTTabPane::ApplyChanges() {
    // Apply connection changes to the system
    PromptOK("Changes applied!");
}

VSTConnectionsCtrl::VSTConnectionsCtrl() {
    AddFrame(tabCtrl);
    
    tabCtrl.Add(inputPane.SizePos(), "Inputs");
    tabCtrl.Add(outputPane.SizePos(), "Outputs");
    tabCtrl.Add(sidechainPane.SizePos(), "Sidechain");
    
    RefreshPanes();
}

void VSTConnectionsCtrl::Refresh() {
    RefreshPanes();
}

void VSTConnectionsCtrl::RefreshPanes() {
    inputPane.Refresh();
    outputPane.Refresh();
    sidechainPane.Refresh();
}

}