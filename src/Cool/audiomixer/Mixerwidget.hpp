/*
    SPDX-FileCopyrightText: 2019 Jean-Baptiste Mardelle
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_MixerWidget_h_
#define _Cool_MixerWidget_h_

#include "../Definitions.h"

namespace Mlt {
    class Tractor;
    class Service;
}

NAMESPACE_UPP

class MixerManager;

class MixerWidget : public ParentCtrl {
public:
    typedef MixerWidget CLASSNAME;

    MixerWidget(int tid, ::Mlt::Tractor* service, const String& track_tag, const String& track_name);
    virtual ~MixerWidget();

    void ConnectMixer(bool connect);
    void PauseMonitoring(bool pause);
    void SetRecordState(bool recording);
    void MonitorAudio(bool monitor);

    // Callbacks for MixerManager
    std::function<void(int, bool)> WhenMuteTrack;

private:
    int track_id;
    String tag;
    String name;
    
    ::Mlt::Tractor* tractor = nullptr;
    
    bool is_recording = false;
    bool is_monitoring = false;
    
    void BuildUI();
};

END_UPP_NAMESPACE

#endif
