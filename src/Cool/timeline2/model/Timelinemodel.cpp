/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Timelinemodel.hpp"
#include "../../Core.h"
#include "Trackmodel.hpp"
#include "Clipmodel.hpp"
#include "Snapmodel.hpp"
#include "../../doc/Kdenlivedoc.h"
#include <mlt++/MltTractor.h>
#include <mlt++/MltProducer.h>

NAMESPACE_UPP

int TimelineModel::current_tree_id = 0;

TimelineModel::TimelineModel(const String& uuid, std::weak_ptr<DocUndoStack> undo_stack)
    : uuid(uuid)
    , undo_stack(undo_stack)
{
    tractor = std::make_shared<::Mlt::Tractor>(pCore.GetProjectProfile());
    snaps = std::make_shared<SnapModel>();
    
    // Create black background track
    std::shared_ptr<::Mlt::Producer> black_clip(new ::Mlt::Producer(pCore.GetProjectProfile(), "color:black"));
    black_clip->set("kdenlive:playlistid", "black_track");
    black_clip->set("mlt_type", "producer");
    black_clip->set("length", 2147483647); // INT_MAX
    
    tractor->insert_track(*black_clip, 0);
    
    is_loading = false;
}

TimelineModel::~TimelineModel() {
    is_closing = true;
    tracks.clear();
    clips.clear();
}

int TimelineModel::GetTracksCount() const {
    int count = tractor->count();
    return count > 0 ? count - 1 : 0;
}

bool TimelineModel::IsAudioTrack(int track_id) const {
    auto it = tracks.find(track_id);
    return (it != tracks.end()) ? it->second->IsAudioTrack() : false;
}

bool TimelineModel::IsSubtitleTrack(int track_id) const {
    auto it = tracks.find(track_id);
    return (it != tracks.end()) ? it->second->IsSubtitleTrack() : false;
}

int TimelineModel::GetTrackPosition(int track_id) const {
    for(int i = 0; i < all_tracks.GetCount(); i++) {
        if (all_tracks[i] == track_id) return i;
    }
    return -1;
}

int TimelineModel::GetTrackMltIndex(int track_id) const {
    int pos = GetTrackPosition(track_id);
    return (pos >= 0) ? pos + 1 : -1;
}

int TimelineModel::GetTrackSortValue(int track_id, int separated) const {
    // Simplified version of the complex original logic
    int pos = GetTrackPosition(track_id);
    return pos + 1;
}

int TimelineModel::GetMirrorTrackId(int track_id) const {
    if (IsAudioTrack(track_id)) return GetMirrorVideoTrackId(track_id);
    return GetMirrorAudioTrackId(track_id);
}

int TimelineModel::GetMirrorAudioTrackId(int track_id) const {
    int pos = GetTrackPosition(track_id);
    if (pos < 0 || IsAudioTrack(track_id)) return -1;
    
    // Simple mirror logic: find corresponding audio track
    int count = 0;
    for(int i = pos; i >= 0; i--) {
        int tid = all_tracks[i];
        if (!IsAudioTrack(tid)) count++;
        else {
            count--;
            if (count == 0) return tid;
        }
    }
    return -1;
}

int TimelineModel::GetMirrorVideoTrackId(int track_id) const {
    int pos = GetTrackPosition(track_id);
    if (pos < 0 || !IsAudioTrack(track_id)) return -1;
    
    int count = 0;
    for(int i = pos; i < all_tracks.GetCount(); i++) {
        int tid = all_tracks[i];
        if (IsAudioTrack(tid)) count++;
        else {
            count--;
            if (count == 0) return tid;
        }
    }
    return -1;
}

int TimelineModel::GetClipsCount() const {
    return (int)clips.size();
}

int TimelineModel::GetItemTrackId(int item_id) const {
    auto it = clips.find(item_id);
    return (it != clips.end()) ? it->second->GetTrackId() : -1;
}

int TimelineModel::GetItemPosition(int item_id) const {
    auto it = clips.find(item_id);
    return (it != clips.end()) ? it->second->GetPosition() : -1;
}

int TimelineModel::GetItemPlaytime(int item_id) const {
    auto it = clips.find(item_id);
    return (it != clips.end()) ? it->second->GetPlaytime() : -1;
}

int TimelineModel::GetItemIn(int item_id) const {
    // TODO: Implement in ClipModel
    return 0;
}

int TimelineModel::GetItemEnd(int item_id) const {
    auto it = clips.find(item_id);
    return (it != clips.end()) ? it->second->GetPosition() + it->second->GetPlaytime() : -1;
}

double TimelineModel::GetItemSpeed(int item_id) const {
    // TODO: Implement in ClipModel
    return 1.0;
}

Size TimelineModel::GetItemFrameSize(int item_id) const {
    // TODO: Implement in ClipModel
    return Size(1920, 1080);
}

void TimelineModel::RequestAddToSelection(int item_id, bool clear) {
    if (clear) current_selection.clear();
    current_selection.insert(item_id);
    NotifyChange(item_id, SelectedRole);
}

void TimelineModel::RequestClearSelection(bool on_deletion) {
    auto old_selection = current_selection;
    current_selection.clear();
    for (int id : old_selection) {
        NotifyChange(id, SelectedRole);
    }
}

std::shared_ptr<::Mlt::Producer> TimelineModel::GetProducer() {
    return std::static_pointer_cast<::Mlt::Producer>(tractor);
}

END_UPP_NAMESPACE
