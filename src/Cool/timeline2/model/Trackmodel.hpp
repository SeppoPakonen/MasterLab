/*
    SPDX-FileCopyrightText: 2017 Nicolas Carion
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_TrackModel_h_
#define _Cool_TrackModel_h_

#include "../../Definitions.h"
#include "../../Undohelper.hpp"

namespace Mlt {
    class Tractor;
    class Playlist;
    class Producer;
    class Transition;
}

NAMESPACE_UPP

class TimelineModel;
class ClipModel;
class CompositionModel;
class EffectStackModel;
class AssetParameterModel;

class MixInfo {
public:
    int first_clip_id = -1;
    int second_clip_id = -1;
    std::pair<int, int> first_clip_in_out = {-1, -1};
    std::pair<int, int> second_clip_in_out = {-1, -1};
    int mix_offset = 0;
};

class TrackModel : public std::enable_shared_from_this<TrackModel> {
public:
    virtual ~TrackModel();

    static std::shared_ptr<TrackModel> Construct(const std::weak_ptr<TimelineModel>& parent, int id = -1, const String& track_name = "", bool audio_track = false);

    // Track state
    bool IsLocked() const { return is_locked; }
    bool IsAudioTrack() const { return audio_track; }
    bool IsSubtitleTrack() const { return subtitle_track; }
    bool IsHidden() const { return is_hidden; }
    bool IsMute() const { return is_mute; }
    
    int  GetId() const { return id; }
    int  GetClipsCount() const { return (int)clips.size(); }
    
    // MLT access
    ::Mlt::Tractor* GetTrackService() { return track_tractor.get(); }

    // Logic
    bool RequestClipInsertion(int clip_id, int position);
    bool RequestClipDeletion(int clip_id);
    
    void SetProperty(const String& name, const String& value);
    String GetProperty(const String& name) const;

protected:
    TrackModel(const std::weak_ptr<TimelineModel>& parent, int id, const String& track_name, bool audio_track);

private:
    std::weak_ptr<TimelineModel> parent;
    int id;
    bool audio_track;
    bool subtitle_track = false;
    bool is_locked = false;
    bool is_hidden = false;
    bool is_mute = false;

    std::shared_ptr<::Mlt::Tractor> track_tractor;
    // Dual playlist for mixes/transitions
    std::unique_ptr<::Mlt::Playlist> playlists[2];
    
    std::map<int, std::shared_ptr<ClipModel>> clips;
    std::map<int, std::shared_ptr<CompositionModel>> compositions;
    
    mutable Mutex lock;
    std::shared_ptr<EffectStackModel> effect_stack;
};

END_UPP_NAMESPACE

#endif
