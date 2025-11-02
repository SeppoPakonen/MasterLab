#ifndef _VSTConnections_VSTConnectionsCtrl_h_
#define _VSTConnections_VSTConnectionsCtrl_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <Docking/Docking.h>
#include <GridCtrl/GridCtrl.h>

using namespace Upp;

namespace VSTConnections {

// Tab pane for VST connections
class VSTTabPane : public Ctrl {
public:
    VSTTabPane();
    void Refresh();

private:
    GridCtrl gridCtrl;
    Button applyBtn;
    
    void ApplyChanges();
};

// Main VST Connections control
class VSTConnectionsCtrl : public Ctrl {
public:
    VSTConnectionsCtrl();
    void Refresh();
    
private:
    TabCtrl tabCtrl;
    VSTTabPane inputPane;
    VSTTabPane outputPane;
    VSTTabPane sidechainPane;
    
    void RefreshPanes();
};

}

#endif