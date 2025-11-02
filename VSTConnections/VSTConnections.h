#ifndef _VSTConnections_VSTConnections_h_
#define _VSTConnections_VSTConnections_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <Docking/Docking.h>
#include "VSTConnectionsCtrl.h"

using namespace Upp;

// VST Connections UI package for managing VST I/O routing
namespace VSTConnections {

class VSTConnectionsWindow : public WithDockManager<ParentCtrl> {
public:
    VSTConnectionsWindow();
    void InitLayout();
    void RefreshConnections();
    
private:
    VSTConnectionsCtrl connectionsCtrl;
    ToolBar toolBar;
    
    void ToolMenu(Bar& bar);
    void Refresh();
};

}

#endif