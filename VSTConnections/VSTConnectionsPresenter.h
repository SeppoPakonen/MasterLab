#ifndef _VSTConnections_VSTConnectionsPresenter_h_
#define _VSTConnections_VSTConnectionsPresenter_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "VSTConnectionsCtrl.h"
#include "../Devices/Devices.h"
#include "../Devices/IOMatrixService.h"

using namespace Upp;

namespace VSTConnections {

// Presenter class to handle business logic for VST Connections UI
class VSTConnectionsPresenter {
public:
    VSTConnectionsPresenter(VSTConnectionsCtrl& view);
    void ConnectView();
    void LoadConnections();
    void SaveConnections();
    void ApplyChanges();
    
private:
    VSTConnectionsCtrl& view;
    Devices::IOMatrixService& ioMatrixService;
    
    void OnConnectionChanged();
    void LoadInputs();
    void LoadOutputs();
    void LoadGroupsFx();
    void LoadExternalFx();
    void LoadExternalInstruments();
    void LoadStudio();
};

}

#endif