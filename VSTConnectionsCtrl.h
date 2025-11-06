#ifndef _VSTConnections_VSTConnectionsCtrl_h_
#define _VSTConnections_VSTConnectionsCtrl_h_

#include "VSTConnections.h"

NAMESPACE_UPP

// Types of connection items
enum ConnectionItemType {
    CONNECTION_INPUT,
    CONNECTION_OUTPUT,
    CONNECTION_GROUP,
    CONNECTION_FX_CHANNEL,
    CONNECTION_EXTERNAL_FX,
    CONNECTION_EXTERNAL_INSTRUMENT,
    CONNECTION_STUDIO
};

// Data model for connection items
struct ConnectionItem {
    String name;
    String speakers; // e.g., "Stereo", "Mono", "5.1"
    String audioDevice;
    String devicePort;
    double delayMs;
    double sendGainDb;
    double returnGainDb;
    String midiDevice;
    bool isUsed;
    bool hasClickOutput; // For outputs tab
    String routeTo; // For Groups/FX tab
    
    ConnectionItemType type;
    Vector<ConnectionItem> children; // For tree structure
    bool isExpanded;
    
    ConnectionItem() : delayMs(0.0), sendGainDb(0.0), returnGainDb(0.0), 
                       isUsed(false), hasClickOutput(false), isExpanded(false), type(CONNECTION_INPUT) {}
};

// Toolbar for each tab
class ConnectionToolbar : public ToolBar {
public:
    virtual void ToolMenu(Bar& bar);
    
    // Event handlers
    void ExpandAll();
    void CollapseAll();
    void AddBus();
    void AddGroup();
    void AddFxChannel();
    void AddExternalFx();
    void AddExternalInstrument();
    void ToggleControlRoom();
    
    Callback WhenAddBus;
    Callback WhenAddGroup;
    Callback WhenAddFxChannel;
    Callback WhenAddExternalFx;
    Callback WhenAddExternalInstrument;
    Callback WhenToggleControlRoom;
    
private:
    bool controlRoomEnabled = true;
};

// Custom TreeCtrl for connection items
class ConnectionTreeCtrl : public TreeCtrl {
public:
    typedef ConnectionTreeCtrl CLASSNAME;
    
    ConnectionTreeCtrl();
    virtual ~ConnectionTreeCtrl();
    
    void SetData(const Vector<ConnectionItem>& items);
    void RefreshView();
    
private:
    Vector<ConnectionItem> data;
    int currentTab;
    
    void RefreshNode(int node, const ConnectionItem& item);
    virtual void RightClick(Point p, dword data) override;
    virtual void LeftDouble(Point p, dword data) override;
};

// Main control for VST Connections
class VSTConnectionsCtrl : public ParentCtrl {
public:
    typedef VSTConnectionsCtrl CLASSNAME;
    
    VSTConnectionsCtrl();
    virtual ~VSTConnectionsCtrl();
    
    void Layout();
    
private:
    TabCtrl tabCtrl;
    
    // Individual tab controls
    ConnectionToolbar inputToolbar, outputToolbar, groupsToolbar, extFxToolbar, extInstToolbar, studioToolbar;
    ConnectionTreeCtrl inputTree, outputTree, groupsTree, extFxTree, extInstTree, studioTree;
    
    // Tab contents
    Ctrl inputTab, outputTab, groupsTab, extFxTab, extInstTab, studioTab;
    
    // Initialize each tab
    void InitInputTab();
    void InitOutputTab();
    void InitGroupsTab();
    void InitExternalFxTab();
    void InitExternalInstrumentTab();
    void InitStudioTab();
    
    void TabChanged();
};

END_UPP_NAMESPACE

#endif