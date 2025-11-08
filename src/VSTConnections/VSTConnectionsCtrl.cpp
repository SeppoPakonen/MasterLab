#include "VSTConnectionsCtrl.h"

NAMESPACE_UPP

// ConnectionToolbar implementation
void ConnectionToolbar::ToolMenu(Bar& bar) {
    bar.Add("Expand All", CtrlImg::plus(), THISBACK(ExpandAll));
    bar.Add("Collapse All", CtrlImg::minus(), THISBACK(CollapseAll));

    switch(currentTab) {
        case 0: // Inputs
            bar.Add("Add Bus...", CtrlImg::file(), THISBACK(AddBus));
            bar.Add(Separator());
            bar.Add("Preset", CtrlImg::folder(), PopupCallback().NoCheck());
            bar.Add("Save Preset", CtrlImg::save(), THISBACK(AddBus));
            bar.Add("Delete Preset", CtrlImg::trash(), THISBACK(AddBus));
            break;
        case 1: // Outputs
            bar.Add("Add Bus...", CtrlImg::file(), THISBACK(AddBus));
            bar.Add(Separator());
            bar.Add("Preset", CtrlImg::folder(), PopupCallback().NoCheck());
            bar.Add("Save Preset", CtrlImg::save(), THISBACK(AddBus));
            bar.Add("Delete Preset", CtrlImg::trash(), THISBACK(AddBus));
            break;
        case 2: // Groups/FX
            bar.Add("Add Group...", CtrlImg::file(), THISBACK(AddGroup));
            bar.Add("Add FX Channel...", CtrlImg::plugin(), THISBACK(AddFxChannel));
            break;
        case 3: // External FX
            bar.Add("Add External FX...", CtrlImg::plugin(), THISBACK(AddExternalFx));
            bar.Add(Separator());
            bar.Add("Favorites", CtrlImg::star(), PopupCallback().NoCheck());
            break;
        case 4: // External Instruments
            bar.Add("Add External Instrument...", CtrlImg::plugin(), THISBACK(AddExternalInstrument));
            break;
        case 5: // Studio
            bar.Add("Add Bus...", CtrlImg::file(), THISBACK(AddBus));
            bar.Add(Separator());
            bar.Add("Preset", CtrlImg::folder(), PopupCallback().NoCheck());
            bar.Add("Save Preset", CtrlImg::save(), THISBACK(AddBus));
            bar.Add("Delete Preset", CtrlImg::trash(), THISBACK(AddBus));
            bar.Add(Separator());
            bar.Add(controlRoomEnabled ? "Disable Control Room" : "Enable Control Room",
                    CtrlImg::power(), THISBACK(ToggleControlRoom));
            break;
    }
}

void ConnectionToolbar::ExpandAll() {
    // Implementation for expanding all tree nodes
}

void ConnectionToolbar::CollapseAll() {
    // Implementation for collapsing all tree nodes
}

void ConnectionToolbar::AddBus() {
    if(WhenAddBus) WhenAddBus();
}

void ConnectionToolbar::AddGroup() {
    if(WhenAddGroup) WhenAddGroup();
}

void ConnectionToolbar::AddFxChannel() {
    if(WhenAddFxChannel) WhenAddFxChannel();
}

void ConnectionToolbar::AddExternalFx() {
    if(WhenAddExternalFx) WhenAddExternalFx();
}

void ConnectionToolbar::AddExternalInstrument() {
    if(WhenAddExternalInstrument) WhenAddExternalInstrument();
}

void ConnectionToolbar::ToggleControlRoom() {
    controlRoomEnabled = !controlRoomEnabled;
    if(WhenToggleControlRoom) WhenToggleControlRoom();
}

// ConnectionTreeCtrl implementation
ConnectionTreeCtrl::ConnectionTreeCtrl() {
    // Initialize tree control
    NoWantFocus();
}

ConnectionTreeCtrl::~ConnectionTreeCtrl() {
}

void ConnectionTreeCtrl::SetData(const Vector<ConnectionItem>& items) {
    data <<= items; // Deep copy using U++ Vector's <<= operator
    RefreshView();
}

void ConnectionTreeCtrl::RefreshView() {
    Clear();

    for(int i = 0; i < data.GetCount(); i++) {
        int node = Add(CtrlImg::smallright(), data[i].name);
        RefreshNode(node, data[i]);
    }
}

void ConnectionTreeCtrl::RefreshNode(int node, const ConnectionItem& item) {
    // Set the node text and other properties based on the item
    // This is a simplified implementation

    if(item.children.GetCount() > 0) {
        for(int i = 0; i < item.children.GetCount(); i++) {
            int childNode = AddChild(node, CtrlImg::smallright(), item.children[i].name);
            RefreshNode(childNode, item.children[i]);
        }
    }
}

void ConnectionTreeCtrl::RightClick(Point p, dword data) {
    TreeCtrl::RightClick(p, data);
    // Handle right-click for context menu
}

void ConnectionTreeCtrl::LeftDouble(Point p, dword data) {
    TreeCtrl::LeftDouble(p, data);
    // Handle double-click to expand/collapse
}

// VSTConnectionsCtrl implementation
VSTConnectionsCtrl::VSTConnectionsCtrl() {
    AddFrame(tabCtrl);
    tabCtrl.TabAdd(inputTab, "Inputs");
    tabCtrl.TabAdd(outputTab, "Outputs");
    tabCtrl.TabAdd(groupsTab, "Groups/FX");
    tabCtrl.TabAdd(extFxTab, "External FX");
    tabCtrl.TabAdd(extInstTab, "External Instruments");
    tabCtrl.TabAdd(studioTab, "Studio");

    tabCtrl.WhenSel = THISBACK(TabChanged);

    // Initialize each tab with proper tab indices
    inputToolbar.currentTab = 0;
    InitInputTab();
    
    outputToolbar.currentTab = 1;
    InitOutputTab();
    
    groupsToolbar.currentTab = 2;
    InitGroupsTab();
    
    extFxToolbar.currentTab = 3;
    InitExternalFxTab();
    
    extInstToolbar.currentTab = 4;
    InitExternalInstrumentTab();
    
    studioToolbar.currentTab = 5;
    InitStudioTab();

    // Default to first tab
    tabCtrl.Set(0);
}

VSTConnectionsCtrl::~VSTConnectionsCtrl() {
}

void VSTConnectionsCtrl::Layout() {
    tabCtrl.SetRect(GetSize());
}

void VSTConnectionsCtrl::Refresh() {
    // Refresh all tree views with current data
    inputTree.RefreshView();
    outputTree.RefreshView();
    groupsTree.RefreshView();
    extFxTree.RefreshView();
    extInstTree.RefreshView();
    studioTree.RefreshView();
}

void VSTConnectionsCtrl::TabChanged() {
    // Handle tab change if needed
}

void VSTConnectionsCtrl::InitInputTab() {
    // Create layout for Inputs tab
    inputTab.AddFrame(inputToolbar);
    inputTab.Add(inputTree);
    inputTree.SetCurrentTab(0); // Set correct tab index

    // Connect toolbar events
    inputToolbar.WhenAddBus = [&]() {
        // Handle Add Bus action
        PromptOK("Add Bus action triggered for Inputs tab");
    };

    // Setup tree columns for Inputs: Bus Name, Speakers, Audio Device, Device Port
    // This would normally involve connecting to actual data from IOMatrixService
}

void VSTConnectionsCtrl::InitOutputTab() {
    // Create layout for Outputs tab
    outputTab.AddFrame(outputToolbar);
    outputTab.Add(outputTree);
    outputTree.SetCurrentTab(1); // Set correct tab index

    // Connect toolbar events
    outputToolbar.WhenAddBus = [&]() {
        // Handle Add Bus action
        PromptOK("Add Bus action triggered for Outputs tab");
    };

    // Setup tree columns for Outputs: Bus Name, Speakers, Audio Device, Device Port, Click
    // This would normally involve connecting to actual data from IOMatrixService
}

void VSTConnectionsCtrl::InitGroupsTab() {
    // Create layout for Groups/FX tab
    groupsTab.AddFrame(groupsToolbar);
    groupsTab.Add(groupsTree);
    groupsTree.SetCurrentTab(2); // Set correct tab index

    // Connect toolbar events
    groupsToolbar.WhenAddGroup = [&]() {
        // Handle Add Group action
        PromptOK("Add Group action triggered for Groups/FX tab");
    };
    groupsToolbar.WhenAddFxChannel = [&]() {
        // Handle Add FX Channel action
        PromptOK("Add FX Channel action triggered for Groups/FX tab");
    };

    // Setup tree columns for Groups/FX: Bus Name, Speakers, Route To
    // This would normally involve connecting to actual data from IOMatrixService
}

void VSTConnectionsCtrl::InitExternalFxTab() {
    // Create layout for External FX tab
    extFxTab.AddFrame(extFxToolbar);
    extFxTab.Add(extFxTree);
    extFxTree.SetCurrentTab(3); // Set correct tab index

    // Connect toolbar events
    extFxToolbar.WhenAddExternalFx = [&]() {
        // Handle Add External FX action
        PromptOK("Add External FX action triggered for External FX tab");
    };

    // Setup tree columns for External FX: Bus Name, Speakers, Audio Device, Device Port, Delay, Send Gain, Return Gain, MIDI Device, Used
    // This would normally involve connecting to actual data from IOMatrixService
}

void VSTConnectionsCtrl::InitExternalInstrumentTab() {
    // Create layout for External Instruments tab
    extInstTab.AddFrame(extInstToolbar);
    extInstTab.Add(extInstTree);
    extInstTree.SetCurrentTab(4); // Set correct tab index

    // Connect toolbar events
    extInstToolbar.WhenAddExternalInstrument = [&]() {
        // Handle Add External Instrument action
        PromptOK("Add External Instrument action triggered for External Instruments tab");
    };

    // Setup tree columns for External Instruments: Bus Name, Speakers, Audio Device, Device Port, Delay, Return Gain, MIDI Device, Used
    // This would normally involve connecting to actual data from IOMatrixService
}

void VSTConnectionsCtrl::InitStudioTab() {
    // Create layout for Studio tab
    studioTab.AddFrame(studioToolbar);
    studioTab.Add(studioTree);
    studioTree.SetCurrentTab(5); // Set correct tab index

    // Connect toolbar events
    studioToolbar.WhenAddBus = [&]() {
        // Handle Add Bus action
        PromptOK("Add Bus action triggered for Studio tab");
    };
    studioToolbar.WhenToggleControlRoom = [&]() {
        // Handle Control Room enable/disable
        PromptOK("Control Room toggle action triggered for Studio tab");
    };

    // Setup tree columns for Studio: Bus Name, Speakers, Audio Device, Device Port
    // This would normally involve connecting to actual data from IOMatrixService
}

END_UPP_NAMESPACE