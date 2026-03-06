/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Trackmodel.hpp"
#include "Timelinemodel.hpp"
#include "Clipmodel.hpp"
#include "../../Core.h"
#include <mlt++/MltTractor.h>
#include <mlt++/MltPlaylist.h>
#include <mlt++/MltField.h>

NAMESPACE_UPP

TrackModel::TrackModel(const std::weak_ptr<TimelineModel>& parent, int id, const String& track_name, bool audio_track)
    : parent(parent)
    , id(id)
    , audio_track(audio_track)
{
    if (auto ptr = parent.lock()) {
        track_tractor = std::make_shared<::Mlt::Tractor>(pCore.GetProjectProfile());
        
        playlists[0].reset(new ::Mlt::Playlist(pCore.GetProjectProfile()));
        playlists[1].reset(new ::Mlt::Playlist(pCore.GetProjectProfile()));
        
        track_tractor->insert_track(*playlists[0], 0);
        track_tractor->insert_track(*playlists[1], 1);
        
        if (!track_name.IsEmpty()) {
            track_tractor->set("kdenlive:track_name", track_name);
        }
        
        if (audio_track) {
            track_tractor->set("kdenlive:audio_track", 1);
            playlists[0]->set("hide", 1);
            playlists[1]->set("hide", 1);
        } else {
            playlists[0]->set("hide", 2);
            playlists[1]->set("hide", 2);
        }
        
        track_tractor->set("kdenlive:timeline_active", 1);
        
        // TODO: Construct EffectStackModel
    }
}

TrackModel::~TrackModel() {
    if (track_tractor) {
        // MLT Cleanup: remove tracks from field
        std::unique_ptr<::Mlt::Field> field(track_tractor->field());
        if (field) {
            field->block();
            // TODO: disconnect transitions and producers
            field->unblock();
        }
        
        track_tractor->remove_track(1);
        track_tractor->remove_track(0);
    }
}

std::shared_ptr<TrackModel> TrackModel::Construct(const std::weak_ptr<TimelineModel>& parent, int id, const String& track_name, bool audio_track) {
    return std::shared_ptr<TrackModel>(new TrackModel(parent, id, track_name, audio_track));
}

void TrackModel::SetProperty(const String& name, const String& value) {
    if (track_tractor) {
        track_tractor->set(name, value);
    }
}

String TrackModel::GetProperty(const String& name) const {
    return track_tractor ? track_tractor->get(name) : "";
}

END_UPP_NAMESPACE
