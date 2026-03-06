/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Clipmodel.hpp"
#include "Timelinemodel.hpp"
#include "../../Core.h"
#include "../../bin/Projectclip.h"
#include "../../bin/Projectitemmodel.h"
#include <mlt++/MltProducer.h>
#include <mlt++/MltProperties.h>

NAMESPACE_UPP

ClipModel::ClipModel(const std::shared_ptr<TimelineModel>& parent, std::shared_ptr<::Mlt::Producer> producer, 
                     const String& bin_clip_id, int id, PlaylistState::ClipState state, double speed)
    : parent(parent)
    , producer(producer)
    , bin_clip_id(bin_clip_id)
    , id(id)
    , current_state(state)
    , speed(speed)
{
    if (producer) {
        producer->set("kdenlive:id", bin_clip_id);
        producer->set("_kdenlive_cid", id);
        
        // TODO: Access EffectStackModel
        // effect_stack = EffectStackModel::Construct(producer, ...);
    }
}

ClipModel::~ClipModel() {
}

std::shared_ptr<ClipModel> ClipModel::Construct(const std::shared_ptr<TimelineModel>& parent, 
                                                const String& bin_clip_id, int id, 
                                                PlaylistState::ClipState state, double speed) {
    // Factory method usually called from TimelineModel
    // For now, we assume producer is created elsewhere or here
    std::shared_ptr<::Mlt::Producer> prod = nullptr;
    
    // std::shared_ptr<ProjectClip> binClip = pCore.GetProjectItemModel()->GetClipByBinID(bin_clip_id);
    // if (binClip) prod = binClip->GetTimelineProducer(...);
    
    return std::shared_ptr<ClipModel>(new ClipModel(parent, prod, bin_clip_id, id, state, speed));
}

String ClipModel::GetProperty(const String& name) const {
    Mutex::Lock locker(lock);
    return producer ? producer->get(name) : "";
}

void ClipModel::SetProperty(const String& name, const String& value) {
    Mutex::Lock locker(lock);
    if (producer) {
        producer->set(name, value);
    }
}

END_UPP_NAMESPACE
