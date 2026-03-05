#ifndef _VSTConnections_VSTConnections_h_
#define _VSTConnections_VSTConnections_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <Docking/Docking.h>
#include "VSTConnectionsCtrl.h"
#include "CuteConnections.h"
#include "CuteConnectForm.h"
#include "CuteConnect.h"
#include "CuteBusForm.h"
#include "CuteAudioIOMatrixForm.h"

using namespace Upp;

// VST Connections UI package for managing VST I/O routing
namespace VSTConnections {

class VSTConnectionsWindow : public ParentCtrl {
public:
    VSTConnectionsWindow();
    void InitLayout();
    void RefreshConnections();
    
private:
    VSTConnectionsCtrl connectionsCtrl;
    
    void Refresh();
};

}

#endif
