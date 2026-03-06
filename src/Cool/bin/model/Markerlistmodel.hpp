/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_bin_model_MarkerListModel_h_
#define _Cool_bin_model_MarkerListModel_h_

#include "../../Definitions.h"
#include "../../Undohelper.hpp"
#include "../../utils/Gentime.h"

NAMESPACE_UPP

class DocUndoStack;
class SnapInterface;

/** @class MarkerListModel
    @brief Model for a list of markers (comments at specific time points).
 */
class MarkerListModel : public std::enable_shared_from_this<MarkerListModel> {
public:
    MarkerListModel(const String& clip_id, std::weak_ptr<DocUndoStack> undo_stack);
    virtual ~MarkerListModel();

    enum { CommentRole = 100, PosRole, FrameRole, ColorRole, TypeRole, IdRole, TCRole, ClipIdRole, DurationRole, EndPosRole, HasRangeRole };

    // Marker management
    bool AddMarker(GenTime pos, const String& comment, int type = -1);
    bool AddRangeMarker(GenTime pos, GenTime duration, const String& comment, int type = -1);
    bool RemoveMarker(GenTime pos);
    bool RemoveAllMarkers();
    
    bool EditMarker(GenTime old_pos, GenTime pos, const String& comment = "", int type = -1);
    
    // Accessors
    const String& GetOwnerId() const { return clip_id; }
    int  GetMarkerCount() const { return (int)markers.size(); }
    
    Vector<int> GetSnapPoints() const;
    bool HasMarker(int frame) const;
    
    // UI Interface (replacing Qt model interface)
    Callback WhenModelChanged;
    Callback WhenCategoriesChanged;

protected:
    // Undo-aware versions
    bool AddMarker(GenTime pos, const String& comment, int type, Fun& undo, Fun& redo);
    bool RemoveMarker(GenTime pos, Fun& undo, Fun& redo);

private:
    String clip_id;
    std::weak_ptr<DocUndoStack> undo_stack;
    
    std::map<int, CommentedTime> markers; // frame -> marker
    std::vector<std::weak_ptr<SnapInterface>> registered_snaps;
    
    mutable Mutex lock;
    
    void NotifyChanged();
};

END_UPP_NAMESPACE

#endif
