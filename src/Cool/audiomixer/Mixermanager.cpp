/*
    SPDX-FileCopyrightText: 2019 Jean-Baptiste Mardelle
    U++ Conversion: 2026 MasterLab Team
*/

#include "Mixermanager.hpp"
#include "Mixerwidget.hpp"
#include "Mixerseparator.h"
#include "../Core.h"
#include "../timeline2/model/Timelineitemmodel.hpp"
#include <mlt++/MltTractor.h>

NAMESPACE_UPP

MixerManager::MixerManager() {
    // Setup U++ Layout components
    // In U++, we typically use Splitters or Frames instead of QScrollArea/Layouts
    SetupUI();
}

MixerManager::~MixerManager() {
    Cleanup();
}

void MixerManager::SetupUI() {
    // TODO: Implement U++ specific UI scaffolding
}

void MixerManager::RegisterTrack(int tid, ::Mlt::Tractor* service, const String& track_tag, const String& track_name) {
    if (mixers.count(tid) > 0) return;

    std::shared_ptr<MixerWidget> mixer(new MixerWidget(tid, service, track_tag, track_name));
    
    // In U++, we use WhenAction or specific callbacks instead of Qt signals
    mixer->WhenMuteTrack = [=](int id, bool mute) {
        if (model) {
            // model->SetTrackProperty(id, "hide", mute ? "1" : "3");
        }
    };

    mixers[tid] = mixer;
    Add(mixer->SizePos()); // Placeholder for real layout
}

void MixerManager::DeregisterTrack(int tid) {
    auto it = mixers.find(tid);
    if (it != mixers.end()) {
        mixers.erase(it);
    }
}

void MixerManager::SetModel(std::shared_ptr<TimelineItemModel> model_) {
    model = model_;
    
    // Setup master mixer
    if (model) {
        ::Mlt::Tractor* service = model->GetTractor().get();
        master_mixer.reset(new MixerWidget(-1, service, "Master", ""));
        Add(master_mixer->SizePos());
    }
}

void MixerManager::UnsetModel() {
    model.reset();
}

void MixerManager::Cleanup() {
    mixers.clear();
    master_mixer.reset();
}

void MixerManager::ConnectMixer(bool do_connect) {
    is_visible_mixer_manager = do_connect;
    for (auto& item : mixers) {
        item.second->ConnectMixer(do_connect);
    }
    if (master_mixer) {
        master_mixer->ConnectMixer(do_connect);
    }
}

void MixerManager::CollapseMixers() {
    // TODO: Implement U++ UI collapse logic
}

void MixerManager::OnRecordStateChanged(int tid, bool recording) {
    if (mixers.count(tid) > 0) {
        mixers[tid]->SetRecordState(recording);
    }
}

void MixerManager::OnMonitorAudio(int tid, bool monitor) {
    if (!monitor) {
        if (mixers.count(tid) > 0) {
            mixers[tid]->MonitorAudio(false);
        }
        monitor_track = -1;
        return;
    }
    
    if (monitor_track > -1 && mixers.count(monitor_track) > 0) {
        mixers[monitor_track]->MonitorAudio(false);
    }
    
    if (mixers.count(tid) > 0) {
        monitor_track = tid;
        mixers[tid]->MonitorAudio(true);
    }
}

void MixerManager::PauseMonitoring(bool pause) {
    for (auto& item : mixers) {
        item.second->PauseMonitoring(pause);
    }
    if (master_mixer) {
        master_mixer->PauseMonitoring(pause);
    }
}

void MixerManager::Layout() {
    // Custom layout logic for arranging track mixers and master mixer
}

END_UPP_NAMESPACE
