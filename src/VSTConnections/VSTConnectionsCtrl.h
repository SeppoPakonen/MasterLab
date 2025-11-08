#ifndef _VSTConnections_VSTConnectionsCtrl_h_
#define _VSTConnections_VSTConnectionsCtrl_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <Docking/Docking.h>
#include <GridCtrl/GridCtrl.h>
#include "../Devices/IOMatrixService.h"  // Include the IOMatrixService

using namespace Upp;

namespace VSTConnections {

// Base class for all tab panes in VST Connections
class VSTTabPane : public Ctrl {
public:
    VSTTabPane();
    virtual ~VSTTabPane() {}
    virtual void Refresh() = 0;
    virtual void AddToolbar(ToolBar& toolBar) = 0;

protected:
    ToolBar toolBar;
    bool isTreeCtrl;
    Devices::IOMatrixService* ioMatrixService;
};

// Tab pane for Inputs
class InputTabPane : public VSTTabPane {
public:
    InputTabPane();
    void Refresh() override;
    void AddToolbar(ToolBar& toolBar) override;

private:
    TreeCtrl treeCtrl;
    void ExpandAll();
    void CollapseAll();
    void AddBus();
    void SavePreset();
    void DeletePreset();
    void OnTreeSel();
};

// Tab pane for Outputs
class OutputTabPane : public VSTTabPane {
public:
    OutputTabPane();
    void Refresh() override;
    void AddToolbar(ToolBar& toolBar) override;

private:
    TreeCtrl treeCtrl;
    void ExpandAll();
    void CollapseAll();
    void AddBus();
    void SavePreset();
    void DeletePreset();
    void OnTreeSel();
};

// Tab pane for Groups/FX
class GroupsFxTabPane : public VSTTabPane {
public:
    GroupsFxTabPane();
    void Refresh() override;
    void AddToolbar(ToolBar& toolBar) override;

private:
    TreeCtrl treeCtrl;
    void ExpandAll();
    void CollapseAll();
    void AddGroup();
    void AddFxChannel();
    void OnTreeSel();
};

// Tab pane for External FX
class ExternalFxTabPane : public VSTTabPane {
public:
    ExternalFxTabPane();
    void Refresh() override;
    void AddToolbar(ToolBar& toolBar) override;

private:
    TreeCtrl treeCtrl;
    void ExpandAll();
    void CollapseAll();
    void AddExternalFx();
    void OnTreeSel();
};

// Tab pane for External Instruments
class ExternalInstrumentsTabPane : public VSTTabPane {
public:
    ExternalInstrumentsTabPane();
    void Refresh() override;
    void AddToolbar(ToolBar& toolBar) override;

private:
    TreeCtrl treeCtrl;
    void ExpandAll();
    void CollapseAll();
    void AddExternalInstrument();
    void OnTreeSel();
};

// Tab pane for Studio (Control Room)
class StudioTabPane : public VSTTabPane {
public:
    StudioTabPane();
    void Refresh() override;
    void AddToolbar(ToolBar& toolBar) override;

private:
    TreeCtrl treeCtrl;
    void ExpandAll();
    void CollapseAll();
    void AddBus();
    void DisableControlRoom();
    void SavePreset();
    void DeletePreset();
    void OnTreeSel();
};

// Main VST Connections control
class VSTConnectionsCtrl : public Ctrl {
public:
    VSTConnectionsCtrl();
    void Refresh();
    
private:
    TabCtrl tabCtrl;
    InputTabPane inputTab;
    OutputTabPane outputTab;
    GroupsFxTabPane groupsFxTab;
    ExternalFxTabPane externalFxTab;
    ExternalInstrumentsTabPane externalInstrumentsTab;
    StudioTabPane studioTab;
    
    Devices::IOMatrixService ioMatrixService;
    
    void RefreshTabs();
    void InitializeTabServices();
};

}

#endif