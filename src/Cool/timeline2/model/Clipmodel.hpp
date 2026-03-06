/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_ClipModel_h_
#define _Cool_ClipModel_h_

#include "../../Definitions.h"
#include "../../Undohelper.hpp"

namespace Mlt {
    class Producer;
}

NAMESPACE_UPP

class TimelineModel;
class TrackModel;
class EffectStackModel;
class MarkerListModel;

class ClipModel : public std::enable_shared_from_this<ClipModel> {
public:
    virtual ~ClipModel();

    static std::shared_ptr<ClipModel> Construct(const std::shared_ptr<TimelineModel>& parent, 
                                                const String& bin_clip_id, int id, 
                                                PlaylistState::ClipState state, double speed = 1.0);

    // Properties
    const String& GetBinClipId() const { return bin_clip_id; }
    int  GetId() const { return id; }
    int  GetTrackId() const { return track_id; }
    int  GetPosition() const { return position; }
    int  GetPlaytime() const { return playtime; }
    
    PlaylistState::ClipState GetClipState() const { return current_state; }
    ClipType::ProducerType   GetClipType() const { return clip_type; }
    
    // MLT access
    ::Mlt::Producer* GetProducer() const { return producer.get(); }

    // Logic
    void SetPosition(int pos) { position = pos; }
    void SetTrackId(int tid) { track_id = tid; }
    
    virtual String GetProperty(const String& name) const;
    void SetProperty(const String& name, const String& value);

protected:
    ClipModel(const std::shared_ptr<TimelineModel>& parent, std::shared_ptr<::Mlt::Producer> producer, 
              const String& bin_clip_id, int id, PlaylistState::ClipState state, double speed);

private:
    std::weak_ptr<TimelineModel> parent;
    std::shared_ptr<::Mlt::Producer> producer;
    
    String bin_clip_id;
    int    id;
    int    track_id = -1;
    int    position = 0;
    int    playtime = 0;
    
    PlaylistState::ClipState current_state;
    ClipType::ProducerType   clip_type;
    double speed = 1.0;
    
    std::shared_ptr<EffectStackModel> effect_stack;
    std::shared_ptr<MarkerListModel>  marker_model;
    
    mutable Mutex lock;
};

END_UPP_NAMESPACE

#endif
