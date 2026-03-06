/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_Definitions_h_
#define _Cool_Definitions_h_

#include <Core/Core.h>
#include "utils/Gentime.h"

NAMESPACE_UPP

const int MAXCLIPDURATION = 15000;

namespace Kdenlive {
    enum MonitorId { NoMonitor = 0x01, ClipMonitor = 0x02, ProjectMonitor = 0x04, RecordMonitor = 0x08, StopMotionMonitor = 0x10, RenderMonitor = 0x20 };
    enum ConfigPage {
        PageMisc = 0, PageEnv, PageTimeline, PageTools, PageCapture, PageJogShuttle,
        PagePlayback, PageTranscode, PageProjectDefaults, PageColorsGuides, PageSpeech, NoPage
    };
    const int DefaultThumbHeight = 100;
}

enum LinuxPackageType { AppImage, Flatpak, Snap, Unknown };

enum class GroupType { Normal, Selection, AVSplit, Leaf };

const String GroupTypeToStr(GroupType t);
GroupType GroupTypeFromStr(const String& s);

enum class KdenliveObjectType { TimelineClip, TimelineComposition, TimelineTrack, TimelineMix, TimelineSubtitle, BinClip, Master, NoItem };

struct ObjectId {
    KdenliveObjectType type;
    int item_id;
    String uuid;
    
    ObjectId(const KdenliveObjectType tp = KdenliveObjectType::NoItem, int id = -1, const String& uid = "")
        : type(tp), item_id(id), uuid(uid) {}
        
    inline bool operator==(const ObjectId& a) const {
        return (a.type == type && a.item_id == item_id && a.uuid == uuid);
    }
    inline bool operator!=(const ObjectId& a) const {
        return !(*this == a);
    }
};

enum class MixAlignment { AlignNone, AlignLeft, AlignRight, AlignCenter };

namespace PlaylistState {
    enum ClipState { VideoOnly = 1, AudioOnly = 2, Disabled = 3, Unknown = 4 };
}

namespace FileStatus {
    enum ClipStatus { StatusReady = 0, StatusProxy, StatusMissing, StatusWaiting, StatusDeleting, StatusProxyOnly };
}

namespace TimelineMode {
    enum EditMode { NormalEdit = 0, OverwriteEdit = 1, InsertEdit = 2 };
}

namespace AssetListType {
    enum AssetType {
        Preferred, Video, Audio, Custom, CustomAudio, Template, TemplateAudio,
        TemplateCustom, TemplateCustomAudio, Favorites, AudioComposition,
        VideoShortComposition, VideoComposition, AudioTransition, VideoTransition,
        Text, Hidden = -1
    };
}

namespace ClipType {
    enum ProducerType {
        Unknown = 0, Audio, Video, AV, Color, Image, Text, SlideShow, Virtual,
        Playlist, WebVfx, TextTemplate, QText, Composition, Track, Qml, Animation, Timeline
    };
}

enum ProjectItemType { ProjectClipType = 0, ProjectFolderType, ProjectSubclipType };

enum TrackType { AudioTrack = 0, VideoTrack = 1, AnyTrack = 2, SubtitleTrack = 3 };

struct SequenceInfo {
    String sequence_name;
    String sequence_id;
    String sequence_duration;
    int sequence_frame_duration = 0;
};

// Renamed from StringMap to avoid clash with U++ internal function
typedef VectorMap<String, String> KdenliveStringMap;
typedef Vector<int16> audioShortVector;

class ItemInfo {
public:
    int position = -1;
    int end_pos = -1;
    int crop_start = 0;
    int play_time;
    int max_duration = -1;
    int track_id = -1;
    int item_id = -1;
    
    ItemInfo() = default;
    bool IsValid() const { return position != end_pos; }
};

class CommentedTime {
public:
    CommentedTime();
    CommentedTime(const GenTime& time, String comment, int marker_type = 0, const GenTime& duration = GenTime(0));
    
    String GetComment() const { return comment; }
    GenTime GetTime() const { return time; }
    void SetComment(const String& c) { comment = c; }
    void SetTime(const GenTime& t) { time = t; }

private:
    GenTime time;
    String comment;
    int type = 0;
    GenTime duration = GenTime(0);
};

END_UPP_NAMESPACE

#endif
