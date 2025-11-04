#include "VSTConnectionsCtrl.h"

namespace VSTConnections {

// Base VSTTabPane implementation
VSTTabPane::VSTTabPane() : isTreeCtrl(true), ioMatrixService(nullptr) {
    // Base constructor
}

// InputTabPane implementation
InputTabPane::InputTabPane() {
    isTreeCtrl = true;
    AddFrame(toolBar);
    AddChild(treeCtrl);
    
    // Define columns for Inputs tab
    treeCtrl.AddColumn("Bus Name", 150);
    treeCtrl.AddColumn("Speakers", 100);
    treeCtrl.AddColumn("Audio Device", 150);
    treeCtrl.AddColumn("Device Port", 120);
    
    // Set up callbacks
    treeCtrl.WhenSel = THISBACK(OnTreeSel);
}

void InputTabPane::Refresh() {
    // Clear existing data
    treeCtrl.Clear();
    
    if (ioMatrixService) {
        auto inputs = ioMatrixService->GetInputs();
        for (int i = 0; i < inputs.GetCount(); i++) {
            const auto& input = inputs[i];
            int rootId = treeCtrl.Add(CtrlImg::speaker(), input.name);
            treeCtrl.Set(0, 1, rootId, input.speakerConfig);
            treeCtrl.Set(0, 2, rootId, input.audioDevice);
            treeCtrl.Set(0, 3, rootId, "");
            
            // Add child nodes for individual ports if expanded
            if (input.isExpanded) {
                for (int j = 0; j < input.devicePorts.GetCount(); j++) {
                    String portName = j == 0 ? "Left" : "Right";
                    int childId = treeCtrl.Add(rootId, portName);
                    treeCtrl.Set(0, 3, childId, input.devicePorts[j]);
                }
            }
            
            // Expand the root node by default
            treeCtrl.Expand(rootId, input.isExpanded);
        }
    } else {
        // Add sample input buses if no service available
        int rootId = treeCtrl.Add(CtrlImg::speaker(), "Stereo In");
        treeCtrl.Set(0, 1, rootId, "Stereo");
        treeCtrl.Set(0, 2, rootId, "ASIO DirectX Full Duplex");
        treeCtrl.Set(0, 3, rootId, "");
        
        // Add child nodes for left/right channels
        int leftId = treeCtrl.Add(rootId, "Left");
        treeCtrl.Set(0, 3, leftId, "Channel 1");
        
        int rightId = treeCtrl.Add(rootId, "Right");
        treeCtrl.Set(0, 3, rightId, "Channel 2");
        
        // Expand the root node
        treeCtrl.Expand(rootId, true);
    }
}

void InputTabPane::AddToolbar(ToolBar& tb) {
    tb.Add("Expand All", CtrlImg::smallright(), THISBACK(ExpandAll));
    tb.Add("Collapse All", CtrlImg::smalldown(), THISBACK(CollapseAll));
    tb.Add("Add Bus...", THISBACK(AddBus));
    tb.Add("Preset", THISBACK(SavePreset));
    tb.Add("Save Preset", CtrlImg::save(), THISBACK(SavePreset));
    tb.Add("Delete Preset", CtrlImg::trash(), THISBACK(DeletePreset));
}

void InputTabPane::ExpandAll() {
    treeCtrl.ExpandAll(true);
}

void InputTabPane::CollapseAll() {
    treeCtrl.ExpandAll(false);
}

void InputTabPane::AddBus() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add Bus functionality needs implementation");
    }
}

void InputTabPane::SavePreset() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Save Preset functionality needs implementation");
    }
}

void InputTabPane::DeletePreset() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Delete Preset functionality needs implementation");
    }
}

void InputTabPane::OnTreeSel() {
    // Handle tree selection
}

// OutputTabPane implementation
OutputTabPane::OutputTabPane() {
    isTreeCtrl = true;
    AddFrame(toolBar);
    AddChild(treeCtrl);
    
    // Define columns for Outputs tab
    treeCtrl.AddColumn("Bus Name", 150);
    treeCtrl.AddColumn("Speakers", 100);
    treeCtrl.AddColumn("Audio Device", 150);
    treeCtrl.AddColumn("Device Port", 120);
    treeCtrl.AddColumn("Click", 80);
    
    // Set up callbacks
    treeCtrl.WhenSel = THISBACK(OnTreeSel);
}

void OutputTabPane::Refresh() {
    // Clear existing data
    treeCtrl.Clear();
    
    if (ioMatrixService) {
        auto outputs = ioMatrixService->GetOutputs();
        for (int i = 0; i < outputs.GetCount(); i++) {
            const auto& output = outputs[i];
            int rootId = treeCtrl.Add(CtrlImg::speaker(), output.name);
            treeCtrl.Set(0, 1, rootId, output.speakerConfig);
            treeCtrl.Set(0, 2, rootId, output.audioDevice);
            treeCtrl.Set(0, 3, rootId, "");
            treeCtrl.Set(0, 4, rootId, "");  // Click column
            
            // Add child nodes for individual ports if expanded
            if (output.isExpanded) {
                for (int j = 0; j < output.devicePorts.GetCount(); j++) {
                    String portName = j == 0 ? "Left" : "Right";
                    int childId = treeCtrl.Add(rootId, portName);
                    treeCtrl.Set(0, 3, childId, output.devicePorts[j]);
                    treeCtrl.Set(0, 4, childId, "");  // Click column
                }
            }
            
            // Expand the root node by default
            treeCtrl.Expand(rootId, output.isExpanded);
        }
    } else {
        // Add sample output buses if no service available
        int rootId = treeCtrl.Add(CtrlImg::speaker(), "Stereo Out");
        treeCtrl.Set(0, 1, rootId, "Stereo");
        treeCtrl.Set(0, 2, rootId, "ASIO DirectX Full Duplex");
        treeCtrl.Set(0, 3, rootId, "");
        treeCtrl.Set(0, 4, rootId, "");  // Click column
        
        // Add child nodes for left/right channels
        int leftId = treeCtrl.Add(rootId, "Left");
        treeCtrl.Set(0, 3, leftId, "Channel 1");
        treeCtrl.Set(0, 4, leftId, "");  // Click column
        
        int rightId = treeCtrl.Add(rootId, "Right");
        treeCtrl.Set(0, 3, rightId, "Channel 2");
        treeCtrl.Set(0, 4, rightId, "");  // Click column
        
        // Expand the root node
        treeCtrl.Expand(rootId, true);
    }
}

void OutputTabPane::AddToolbar(ToolBar& tb) {
    tb.Add("Expand All", CtrlImg::smallright(), THISBACK(ExpandAll));
    tb.Add("Collapse All", CtrlImg::smalldown(), THISBACK(CollapseAll));
    tb.Add("Add Bus...", THISBACK(AddBus));
    tb.Add("Preset", THISBACK(SavePreset));
    tb.Add("Save Preset", CtrlImg::save(), THISBACK(SavePreset));
    tb.Add("Delete Preset", CtrlImg::trash(), THISBACK(DeletePreset));
}

void OutputTabPane::ExpandAll() {
    treeCtrl.ExpandAll(true);
}

void OutputTabPane::CollapseAll() {
    treeCtrl.ExpandAll(false);
}

void OutputTabPane::AddBus() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add Bus functionality needs implementation");
    }
}

void OutputTabPane::SavePreset() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Save Preset functionality needs implementation");
    }
}

void OutputTabPane::DeletePreset() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Delete Preset functionality needs implementation");
    }
}

void OutputTabPane::OnTreeSel() {
    // Handle tree selection
}

// GroupsFxTabPane implementation
GroupsFxTabPane::GroupsFxTabPane() {
    isTreeCtrl = false;  // This tab doesn't use tree structure according to spec
    AddFrame(toolBar);
    AddChild(treeCtrl);
    
    // Define columns for Groups/FX tab
    treeCtrl.AddColumn("Bus Name", 180);
    treeCtrl.AddColumn("Speakers", 100);
    treeCtrl.AddColumn("Route To", 150);
    
    // Set up callbacks
    treeCtrl.WhenSel = THISBACK(OnTreeSel);
}

void GroupsFxTabPane::Refresh() {
    // Clear existing data
    treeCtrl.Clear();
    
    if (ioMatrixService) {
        auto groups = ioMatrixService->GetGroupsFx();
        for (int i = 0; i < groups.GetCount(); i++) {
            const auto& group = groups[i];
            int groupId = treeCtrl.Add(CtrlImg::folder(), group.name);
            treeCtrl.Set(0, 1, groupId, group.speakerConfig);
            treeCtrl.Set(0, 2, groupId, "Stereo Out"); // Default route
        }
    } else {
        // Add sample groups and FX channels if no service available
        int groupId = treeCtrl.Add(CtrlImg::folder(), "Group 1");
        treeCtrl.Set(0, 1, groupId, "Stereo");
        treeCtrl.Set(0, 2, groupId, "Stereo Out");
        
        int fxId = treeCtrl.Add(CtrlImg::fx(), "FX1 CLA Drums (Mono->Stereo)");
        treeCtrl.Set(0, 1, fxId, "Stereo");
        treeCtrl.Set(0, 2, fxId, "Stereo Out");
    }
}

void GroupsFxTabPane::AddToolbar(ToolBar& tb) {
    tb.Add("Expand", CtrlImg::smallright(), THISBACK(ExpandAll));
    tb.Add("Collapse", CtrlImg::smalldown(), THISBACK(CollapseAll));
    tb.Add("Add Group...", THISBACK(AddGroup));
    tb.Add("Add FX Channel...", THISBACK(AddFxChannel));
}

void GroupsFxTabPane::ExpandAll() {
    // Groups/FX tab doesn't have expandable tree structure according to spec
}

void GroupsFxTabPane::CollapseAll() {
    // Groups/FX tab doesn't have expandable tree structure according to spec
}

void GroupsFxTabPane::AddGroup() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add Group functionality needs implementation");
    }
}

void GroupsFxTabPane::AddFxChannel() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add FX Channel functionality needs implementation");
    }
}

void GroupsFxTabPane::OnTreeSel() {
    // Handle tree selection
}

// ExternalFxTabPane implementation
ExternalFxTabPane::ExternalFxTabPane() {
    isTreeCtrl = true;
    AddFrame(toolBar);
    AddChild(treeCtrl);
    
    // Define columns for External FX tab
    treeCtrl.AddColumn("Bus Name", 150);
    treeCtrl.AddColumn("Speakers", 80);
    treeCtrl.AddColumn("Audio Device", 120);
    treeCtrl.AddColumn("Device Port", 100);
    treeCtrl.AddColumn("Delay", 70);
    treeCtrl.AddColumn("Send Gain", 80);
    treeCtrl.AddColumn("Return Gain", 90);
    treeCtrl.AddColumn("MIDI Device", 120);
    treeCtrl.AddColumn("Used", 60);
    
    // Set up callbacks
    treeCtrl.WhenSel = THISBACK(OnTreeSel);
}

void ExternalFxTabPane::Refresh() {
    // Clear existing data
    treeCtrl.Clear();
    
    if (ioMatrixService) {
        auto externalFxList = ioMatrixService->GetExternalFx();
        for (int i = 0; i < externalFxList.GetCount(); i++) {
            const auto& fx = externalFxList[i];
            int rootId = treeCtrl.Add(CtrlImg::externaleffects(), fx.name);
            treeCtrl.Set(0, 1, rootId, fx.sendConfig);
            treeCtrl.Set(0, 2, rootId, "");
            treeCtrl.Set(0, 3, rootId, "");
            treeCtrl.Set(0, 4, rootId, Format("%.1f ms", fx.delayMs));
            treeCtrl.Set(0, 5, rootId, Format("%.1f dB", fx.sendGainDb));
            treeCtrl.Set(0, 6, rootId, Format("%.1f dB", fx.returnGainDb));
            treeCtrl.Set(0, 7, rootId, fx.midiDevice);
            treeCtrl.Set(0, 8, rootId, fx.isUsed ? "Yes" : "");
            
            // Add child nodes for Send and Return buses
            int sendBusId = treeCtrl.Add(rootId, "Send Bus 1");
            treeCtrl.Set(0, 1, sendBusId, "Stereo");
            treeCtrl.Set(0, 2, sendBusId, "Not Connected");
            
            int returnBusId = treeCtrl.Add(rootId, "Return Bus 1");
            treeCtrl.Set(0, 1, returnBusId, "Stereo");
            treeCtrl.Set(0, 2, returnBusId, "Not Connected");
            
            // Add child nodes for Send Bus Left/Right
            int sendLeftId = treeCtrl.Add(sendBusId, "Left");
            treeCtrl.Set(0, 3, sendLeftId, "Not Connected");
            
            int sendRightId = treeCtrl.Add(sendBusId, "Right");
            treeCtrl.Set(0, 3, sendRightId, "Not Connected");
            
            // Expand the root node
            treeCtrl.Expand(rootId, true);
            treeCtrl.Expand(sendBusId, true);
        }
    } else {
        // Add external FX root node if no service available
        int rootId = treeCtrl.Add(CtrlImg::externaleffects(), "External FX");
        treeCtrl.Set(0, 1, rootId, "Stereo/Stereo");
        treeCtrl.Set(0, 2, rootId, "");
        treeCtrl.Set(0, 3, rootId, "");
        treeCtrl.Set(0, 4, rootId, "0 ms");
        treeCtrl.Set(0, 5, rootId, "0 dB");
        treeCtrl.Set(0, 6, rootId, "0 dB");
        treeCtrl.Set(0, 7, rootId, "No Link");
        treeCtrl.Set(0, 8, rootId, "");
        
        // Add child nodes for Send and Return buses
        int sendBusId = treeCtrl.Add(rootId, "Send Bus 1");
        treeCtrl.Set(0, 1, sendBusId, "Stereo");
        treeCtrl.Set(0, 2, sendBusId, "Not Connected");
        
        int returnBusId = treeCtrl.Add(rootId, "Return Bus 1");
        treeCtrl.Set(0, 1, returnBusId, "Stereo");
        treeCtrl.Set(0, 2, returnBusId, "Not Connected");
        
        // Add child nodes for Send Bus Left/Right
        int sendLeftId = treeCtrl.Add(sendBusId, "Left");
        treeCtrl.Set(0, 3, sendLeftId, "Not Connected");
        
        int sendRightId = treeCtrl.Add(sendBusId, "Right");
        treeCtrl.Set(0, 3, sendRightId, "Not Connected");
        
        // Expand the root node
        treeCtrl.Expand(rootId, true);
        treeCtrl.Expand(sendBusId, true);
    }
}

void ExternalFxTabPane::AddToolbar(ToolBar& tb) {
    tb.Add("Expand", CtrlImg::smallright(), THISBACK(ExpandAll));
    tb.Add("Collapse", CtrlImg::smalldown(), THISBACK(CollapseAll));
    tb.Add("Add External FX...", THISBACK(AddExternalFx));
    tb.Add("Favorites", THISBACK(OnTreeSel));  // Using OnTreeSel as placeholder
}

void ExternalFxTabPane::ExpandAll() {
    treeCtrl.ExpandAll(true);
}

void ExternalFxTabPane::CollapseAll() {
    treeCtrl.ExpandAll(false);
}

void ExternalFxTabPane::AddExternalFx() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add External FX functionality needs implementation");
    }
}

void ExternalFxTabPane::OnTreeSel() {
    // Handle tree selection
}

// ExternalInstrumentsTabPane implementation
ExternalInstrumentsTabPane::ExternalInstrumentsTabPane() {
    isTreeCtrl = true;
    AddFrame(toolBar);
    AddChild(treeCtrl);
    
    // Define columns for External Instruments tab (no Send Gain column)
    treeCtrl.AddColumn("Bus Name", 150);
    treeCtrl.AddColumn("Speakers", 80);
    treeCtrl.AddColumn("Audio Device", 120);
    treeCtrl.AddColumn("Device Port", 100);
    treeCtrl.AddColumn("Delay", 70);
    treeCtrl.AddColumn("Return Gain", 90);
    treeCtrl.AddColumn("MIDI Device", 120);
    treeCtrl.AddColumn("Used", 60);
    
    // Set up callbacks
    treeCtrl.WhenSel = THISBACK(OnTreeSel);
}

void ExternalInstrumentsTabPane::Refresh() {
    // Clear existing data
    treeCtrl.Clear();
    
    if (ioMatrixService) {
        auto externalInstrumentsList = ioMatrixService->GetExternalInstruments();
        for (int i = 0; i < externalInstrumentsList.GetCount(); i++) {
            const auto& inst = externalInstrumentsList[i];
            int rootId = treeCtrl.Add(CtrlImg::externalmidi(), inst.name);
            treeCtrl.Set(0, 1, rootId, "Stereo/Stereo");
            treeCtrl.Set(0, 2, rootId, "");
            treeCtrl.Set(0, 3, rootId, "");
            treeCtrl.Set(0, 4, rootId, Format("%.1f ms", inst.delayMs));
            treeCtrl.Set(0, 5, rootId, Format("%.1f dB", inst.returnGainDb));
            treeCtrl.Set(0, 6, rootId, inst.midiDevice);
            treeCtrl.Set(0, 7, rootId, inst.isUsed ? "Yes" : "");
            
            // Add child nodes for Send and Return buses
            int sendBusId = treeCtrl.Add(rootId, "Send Bus 1");
            treeCtrl.Set(0, 1, sendBusId, "Stereo");
            
            int returnBusId = treeCtrl.Add(rootId, "Return Bus 1");
            treeCtrl.Set(0, 1, returnBusId, "Stereo");
            
            // Add child nodes for Send Bus Left/Right
            int sendLeftId = treeCtrl.Add(sendBusId, "Left");
            treeCtrl.Set(0, 3, sendLeftId, "Not Connected");
            
            int sendRightId = treeCtrl.Add(sendBusId, "Right");
            treeCtrl.Set(0, 3, sendRightId, "Not Connected");
            
            // Expand the root node
            treeCtrl.Expand(rootId, true);
            treeCtrl.Expand(sendBusId, true);
        }
    } else {
        // Add external instruments root node if no service available
        int rootId = treeCtrl.Add(CtrlImg::externalmidi(), "External Instruments");
        treeCtrl.Set(0, 1, rootId, "Stereo/Stereo");
        treeCtrl.Set(0, 2, rootId, "");
        treeCtrl.Set(0, 3, rootId, "");
        treeCtrl.Set(0, 4, rootId, "0 ms");
        treeCtrl.Set(0, 5, rootId, "0 dB");
        treeCtrl.Set(0, 6, rootId, "No Link");
        treeCtrl.Set(0, 7, rootId, "");
        
        // Add child nodes for Send and Return buses
        int sendBusId = treeCtrl.Add(rootId, "Send Bus 1");
        treeCtrl.Set(0, 1, sendBusId, "Stereo");
        
        int returnBusId = treeCtrl.Add(rootId, "Return Bus 1");
        treeCtrl.Set(0, 1, returnBusId, "Stereo");
        
        // Add child nodes for Send Bus Left/Right
        int sendLeftId = treeCtrl.Add(sendBusId, "Left");
        treeCtrl.Set(0, 3, sendLeftId, "Not Connected");
        
        int sendRightId = treeCtrl.Add(sendBusId, "Right");
        treeCtrl.Set(0, 3, sendRightId, "Not Connected");
        
        // Expand the root node
        treeCtrl.Expand(rootId, true);
        treeCtrl.Expand(sendBusId, true);
    }
}

void ExternalInstrumentsTabPane::AddToolbar(ToolBar& tb) {
    tb.Add("Expand", CtrlImg::smallright(), THISBACK(ExpandAll));
    tb.Add("Collapse", CtrlImg::smalldown(), THISBACK(CollapseAll));
    tb.Add("Add External Instrument...", THISBACK(AddExternalInstrument));
}

void ExternalInstrumentsTabPane::ExpandAll() {
    treeCtrl.ExpandAll(true);
}

void ExternalInstrumentsTabPane::CollapseAll() {
    treeCtrl.ExpandAll(false);
}

void ExternalInstrumentsTabPane::AddExternalInstrument() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add External Instrument functionality needs implementation");
    }
}

void ExternalInstrumentsTabPane::OnTreeSel() {
    // Handle tree selection
}

// StudioTabPane implementation
StudioTabPane::StudioTabPane() {
    isTreeCtrl = true;
    AddFrame(toolBar);
    AddChild(treeCtrl);
    
    // Define columns for Studio (Control Room) tab
    treeCtrl.AddColumn("Bus Name", 150);
    treeCtrl.AddColumn("Speakers", 100);
    treeCtrl.AddColumn("Audio Device", 150);
    treeCtrl.AddColumn("Device Port", 120);
    
    // Set up callbacks
    treeCtrl.WhenSel = THISBACK(OnTreeSel);
}

void StudioTabPane::Refresh() {
    // Clear existing data
    treeCtrl.Clear();
    
    if (ioMatrixService) {
        auto studioBuses = ioMatrixService->GetStudio();
        for (int i = 0; i < studioBuses.GetCount(); i++) {
            const auto& bus = studioBuses[i];
            int rootId = treeCtrl.Add(CtrlImg::speaker(), bus.name);
            treeCtrl.Set(0, 1, rootId, bus.speakerConfig);
            treeCtrl.Set(0, 2, rootId, bus.audioDevice);
            treeCtrl.Set(0, 3, rootId, "");
            
            // Add child nodes for individual ports if expanded
            if (bus.isExpanded) {
                for (int j = 0; j < bus.devicePorts.GetCount(); j++) {
                    String portName = j == 0 ? "Left" : "Right";
                    int childId = treeCtrl.Add(rootId, portName);
                    treeCtrl.Set(0, 3, childId, bus.devicePorts[j]);
                }
            }
            
            // Expand the root node by default
            treeCtrl.Expand(rootId, bus.isExpanded);
        }
    } else {
        // Add monitor bus if no service available
        int rootId = treeCtrl.Add(CtrlImg::speaker(), "Monitor 1");
        treeCtrl.Set(0, 1, rootId, "Stereo");
        treeCtrl.Set(0, 2, rootId, "Not Connected");
        treeCtrl.Set(0, 3, rootId, "");
        
        // Add child nodes for left/right channels
        int leftId = treeCtrl.Add(rootId, "Left");
        treeCtrl.Set(0, 3, leftId, "Not Connected");
        
        int rightId = treeCtrl.Add(rootId, "Right");
        treeCtrl.Set(0, 3, rightId, "Not Connected");
        
        // Expand the root node
        treeCtrl.Expand(rootId, true);
    }
}

void StudioTabPane::AddToolbar(ToolBar& tb) {
    tb.Add("Expand All", CtrlImg::smallright(), THISBACK(ExpandAll));
    tb.Add("Collapse All", CtrlImg::smalldown(), THISBACK(CollapseAll));
    tb.Add("Add Bus...", THISBACK(AddBus));
    tb.Add("Preset", THISBACK(SavePreset));
    tb.Add("Save Preset", CtrlImg::save(), THISBACK(SavePreset));
    tb.Add("Delete Preset", CtrlImg::trash(), THISBACK(DeletePreset));
    tb.Add("Disable Control Room", THISBACK(DisableControlRoom));
}

void StudioTabPane::ExpandAll() {
    treeCtrl.ExpandAll(true);
}

void StudioTabPane::CollapseAll() {
    treeCtrl.ExpandAll(false);
}

void StudioTabPane::AddBus() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Add Bus functionality needs implementation");
    }
}

void StudioTabPane::DisableControlRoom() {
    if(PromptYesNo("Are you sure you want to disable Control Room?")) {
        PromptOK("Control room has been disabled.");
    }
}

void StudioTabPane::SavePreset() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Save Preset functionality needs implementation");
    }
}

void StudioTabPane::DeletePreset() {
    if (ioMatrixService) {
        // For now, just show a confirmation - actual implementation would involve creating a modal
        PromptOK("Delete Preset functionality needs implementation");
    }
}

void StudioTabPane::OnTreeSel() {
    // Handle tree selection
}

// Main VSTConnectionsCtrl implementation
VSTConnectionsCtrl::VSTConnectionsCtrl() {
    AddFrame(tabCtrl);
    
    // Initialize the IOMatrixService and link it to each tab
    InitializeTabServices();
    
    tabCtrl.Add(inputTab.SizePos(), "Inputs");
    tabCtrl.Add(outputTab.SizePos(), "Outputs");
    tabCtrl.Add(groupsFxTab.SizePos(), "Groups/FX");
    tabCtrl.Add(externalFxTab.SizePos(), "External FX");
    tabCtrl.Add(externalInstrumentsTab.SizePos(), "External Instruments");
    tabCtrl.Add(studioTab.SizePos(), "Studio");
    
    RefreshTabs();
}

void VSTConnectionsCtrl::InitializeTabServices() {
    // Link the IOMatrixService to each tab pane
    inputTab.ioMatrixService = &ioMatrixService;
    outputTab.ioMatrixService = &ioMatrixService;
    groupsFxTab.ioMatrixService = &ioMatrixService;
    externalFxTab.ioMatrixService = &ioMatrixService;
    externalInstrumentsTab.ioMatrixService = &ioMatrixService;
    studioTab.ioMatrixService = &ioMatrixService;
}

void VSTConnectionsCtrl::Refresh() {
    RefreshTabs();
}

void VSTConnectionsCtrl::RefreshTabs() {
    inputTab.Refresh();
    outputTab.Refresh();
    groupsFxTab.Refresh();
    externalFxTab.Refresh();
    externalInstrumentsTab.Refresh();
    studioTab.Refresh();
}

}