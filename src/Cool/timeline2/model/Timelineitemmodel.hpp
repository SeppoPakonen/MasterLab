/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_TimelineItemModel_h_
#define _Cool_TimelineItemModel_h_

#include "Timelinemodel.hpp"

NAMESPACE_UPP

class SubtitleModel;

/** 
 * @class TimelineItemModel
 * @brief thin wrapper around TimelineModel for UI interfacing
 */
class TimelineItemModel : public TimelineModel {
public:
    typedef TimelineItemModel CLASSNAME;

    static std::shared_ptr<TimelineItemModel> Construct(const String& uuid, std::weak_ptr<DocUndoStack> undo_stack);
    virtual ~TimelineItemModel();

    // Track operations
    bool AddTracksAtPosition(int position, int tracks_count, String& track_name, bool add_audio, bool add_av, bool add_rec);
    void SetTrackProperty(int tid, const String& name, const String& value);
    void SetTrackName(int tid, const String& name);
    
    // UI Notification Implementation
    virtual void NotifyChange(int item_id, int role) override;

    // Logic
    void RebuildMixer();
    std::shared_ptr<SubtitleModel> CreateSubtitleModel();

protected:
    TimelineItemModel(const String& uuid, std::weak_ptr<DocUndoStack> undo_stack);

private:
    std::shared_ptr<SubtitleModel> subtitle_model;
};

END_UPP_NAMESPACE

#endif
