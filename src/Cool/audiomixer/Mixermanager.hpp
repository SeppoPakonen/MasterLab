/*
    SPDX-FileCopyrightText: 2019 Jean-Baptiste Mardelle
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_MixerManager_h_
#define _Cool_MixerManager_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

namespace Mlt {
    class Tractor;
}

NAMESPACE_UPP

class MixerWidget;
class TimelineItemModel;

class MixerManager : public ParentCtrl {
public:
    typedef MixerManager CLASSNAME;

    MixerManager(MainWindow* parent = nullptr);
    virtual ~MixerManager();

    // Track management
    void RegisterTrack(int tid, ::Mlt::Tractor* service, const String& track_tag, const String& track_name);
    void DeregisterTrack(int tid);
    void SetModel(std::shared_ptr<TimelineItemModel> model);
    void UnsetModel();
    void Cleanup();

    // Logic
    void ConnectMixer(bool do_connect);
    void CollapseMixers();
    void PauseMonitoring(bool pause);
    
    int  GetRecordTrack() const { return monitor_track; }
    bool HasAudioLevelV2() const { return filter_is_v2; }

    // UI Events
    void OnRecordStateChanged(int tid, bool recording);
    void OnMonitorAudio(int tid, bool monitor);

protected:
    virtual void Layout() override;

private:
    std::unordered_map<int, std::shared_ptr<MixerWidget>> mixers;
    std::shared_ptr<MixerWidget> master_mixer;
    
    std::shared_ptr<TimelineItemModel> model;
    
    bool is_visible_mixer_manager = false;
    int  expanded_width = 0;
    Vector<int> solo_muted;
    int  monitor_track = -1;
    bool filter_is_v2 = false;
    
    void SetupUI();
};

END_UPP_NAMESPACE

#endif
