/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_TimelineModel_h_
#define _Cool_TimelineModel_h_

#include "../../Definitions.h"
#include "../../Undohelper.hpp"

namespace Mlt {
    class Tractor;
    class Producer;
    class Profile;
}

NAMESPACE_UPP

class TrackModel;
class ClipModel;
class CompositionModel;
class GroupsModel;
class SnapModel;
class DocUndoStack;

class TimelineModel {
public:
    enum {
        NameRole = 100, ResourceRole, IsProxyRole, ServiceRole, StartRole,
        MixRole, BinIdRole, TrackIdRole, MarkersRole, StatusRole,
        TypeRole, DurationRole, InPointRole, OutPointRole, FramerateRole,
        IsDisabledRole, IsAudioRole, IsLockedRole, ItemIdRole, SelectedRole
    };

    TimelineModel(const String& uuid, std::weak_ptr<DocUndoStack> undo_stack);
    virtual ~TimelineModel();

    // MLT accessors
    ::Mlt::Tractor* GetTractor() const { return tractor.get(); }
    std::shared_ptr<::Mlt::Producer> GetProducer();
    
    // Track management
    int  GetTracksCount() const;
    bool IsAudioTrack(int track_id) const;
    bool IsSubtitleTrack(int track_id) const;
    
    // Item management
    int  GetClipsCount() const;
    int  GetCompositionsCount() const;
    int  GetItemTrackId(int item_id) const;
    int  GetItemPosition(int item_id) const;
    int  GetItemPlaytime(int item_id) const;
    
    // Selection
    void RequestAddToSelection(int item_id, bool clear = false);
    void RequestClearSelection(bool on_deletion = false);
    std::unordered_set<int> GetCurrentSelection() const { return current_selection; }

    // State
    bool IsLoading() const { return is_loading; }
    String GetUuid() const { return uuid; }

protected:
    String uuid;
    std::unique_ptr<::Mlt::Tractor> tractor;
    std::shared_ptr<GroupsModel> groups;
    std::shared_ptr<SnapModel>   snaps;
    
    std::weak_ptr<DocUndoStack> undo_stack;
    
    std::unordered_map<int, std::shared_ptr<TrackModel>> tracks;
    std::unordered_map<int, std::shared_ptr<ClipModel>>  clips;
    
    std::unordered_set<int> current_selection;
    
    bool is_loading = true;
    bool is_closing = false;

    // Virtual interface for UI synchronization (implemented in TimelineItemModel)
    virtual void NotifyChange(int item_id, int role) = 0;
};

END_UPP_NAMESPACE

#endif
