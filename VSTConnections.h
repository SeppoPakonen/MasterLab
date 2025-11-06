#ifndef _VSTConnections_VSTConnections_h_
#define _VSTConnections_VSTConnections_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <Docking/Docking.h>
#include <AudioCore/AudioCore.h>
#include <Devices/Devices.h>

NAMESPACE_UPP

// Forward declarations
class VSTConnectionsCtrl;
class VSTConnectionsWnd;

// Main VST Connections package
class VSTConnectionsApp {
public:
    void Init();
    void Exit();
    
    VSTConnectionsWnd& GetWindow() { return wnd; }
    
private:
    VSTConnectionsWnd wnd;
};

END_UPP_NAMESPACE

#endif