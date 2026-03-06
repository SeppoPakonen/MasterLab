/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#include "Markerlistmodel.hpp"
#include "../../Core.h"
#include "../../doc/Docundostack.hpp"

NAMESPACE_UPP

MarkerListModel::MarkerListModel(const String& clip_id, std::weak_ptr<DocUndoStack> undo_stack)
    : clip_id(clip_id)
    , undo_stack(undo_stack)
{
}

MarkerListModel::~MarkerListModel() {
}

bool MarkerListModel::AddMarker(GenTime pos, const String& comment, int type) {
    Mutex::Lock locker(lock);
    int frame = pos.Frames(pCore.GetCurrentFps());
    
    CommentedTime marker(pos, comment, type);
    markers[frame] = marker;
    
    NotifyChanged();
    return true;
}

bool MarkerListModel::AddRangeMarker(GenTime pos, GenTime duration, const String& comment, int type) {
    Mutex::Lock locker(lock);
    int frame = pos.Frames(pCore.GetCurrentFps());
    
    CommentedTime marker(pos, comment, type, duration);
    markers[frame] = marker;
    
    NotifyChanged();
    return true;
}

bool MarkerListModel::RemoveMarker(GenTime pos) {
    Mutex::Lock locker(lock);
    int frame = pos.Frames(pCore.GetCurrentFps());
    
    auto it = markers.find(frame);
    if (it != markers.end()) {
        markers.erase(it);
        NotifyChanged();
        return true;
    }
    return false;
}

bool MarkerListModel::RemoveAllMarkers() {
    Mutex::Lock locker(lock);
    markers.clear();
    NotifyChanged();
    return true;
}

bool MarkerListModel::EditMarker(GenTime old_pos, GenTime pos, const String& comment, int type) {
    Mutex::Lock locker(lock);
    int old_frame = old_pos.Frames(pCore.GetCurrentFps());
    int new_frame = pos.Frames(pCore.GetCurrentFps());
    
    auto it = markers.find(old_frame);
    if (it != markers.end()) {
        CommentedTime marker = it->second;
        if (!comment.IsEmpty()) marker.SetComment(comment);
        if (type != -1) /* marker.SetType(type); */ ;
        
        if (old_frame != new_frame) {
            markers.erase(it);
            marker.SetTime(pos);
            markers[new_frame] = marker;
        } else {
            markers[old_frame] = marker;
        }
        
        NotifyChanged();
        return true;
    }
    return false;
}

Vector<int> MarkerListModel::GetSnapPoints() const {
    Mutex::Lock locker(lock);
    Vector<int> points;
    for (auto const& [frame, marker] : markers) {
        points.Add(frame);
    }
    return points;
}

bool MarkerListModel::HasMarker(int frame) const {
    Mutex::Lock locker(lock);
    return markers.count(frame) > 0;
}

void MarkerListModel::NotifyChanged() {
    if (WhenModelChanged) WhenModelChanged();
}

END_UPP_NAMESPACE
