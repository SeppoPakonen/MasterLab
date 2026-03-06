/*
    SPDX-FileCopyrightText: 2007 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_monitor_Monitor_h_
#define _Cool_monitor_Monitor_h_

#include "Abstractmonitor.h"
#include "../bin/model/Markerlistmodel.hpp"
#include "../Definitions.h"
#include "../utils/Gentime.h"
#include "../widgets/Timecodedisplay.h"

namespace Mlt {
    class Profile;
    class Filter;
    class Producer;
    class Transition;
}

NAMESPACE_UPP

class SnapModel;
class ProjectClip;
class MonitorManager;
class VideoWidget;
class MonitorAudioLevel;
class MarkerSortModel;

class Monitor : public AbstractMonitor, public ParentCtrl {
public:
    typedef Monitor CLASSNAME;

    enum MonitorOverlay {
        InfoOverlay = 0x01,
        TimecodeOverlay = 0x02,
        MarkersOverlay = 0x04,
        AudioWaveformOverlay = 0x10,
        PlaybackFpsOverlay = 0x20,
        ClipJobsOverlay = 0x40
    };

    Monitor(Kdenlive::MonitorId id, MonitorManager* manager, MainWindow* parent = nullptr);
    virtual ~Monitor();

    // Lifecycle
    void ResetProfile();
    void ResetConsumer(bool full_reset);
    
    // UI Setup
    void SetupMenu(Bar& bar);
    void SetupToolbar(Bar& bar);
    
    // Accessors
    const String GetActiveClipId(bool with_sequence = false);
    int  GetPosition() const { return position; }
    void UpdateTimecodeFormat();
    
    std::shared_ptr<ProjectClip> GetCurrentController() const { return controller; }
    void ReloadProducer(const String& id);
    
    double GetFps() const;
    Size   GetProfileSize() const;

    // Monitor Operations
    virtual void Stop() override;
    virtual void Start() override;
    virtual void Play() override;
    void Pause();
    void Mute(bool m) override;
    
    void Seek(int pos);
    void RefreshMonitor(bool visible);

    // Callbacks for owner
    std::function<void(int)> WhenSeek;
    std::function<void(bool)> WhenDurationChanged;

protected:
    virtual void Layout() override;
    virtual void Paint(Draw& draw) override;
    virtual void MouseMove(Point p, dword flags) override;
    virtual void LeftDown(Point p, dword flags) override;
    virtual void MouseWheel(Point p, int zdelta, dword flags) override;

private:
    Kdenlive::MonitorId monitor_id;
    MonitorManager* manager;
    
    std::shared_ptr<ProjectClip> controller;
    VideoWidget* video_widget = nullptr;
    
    int position = 0;
    int length = 0;
    bool is_locked = false;
    
    TimecodeDisplay* time_pos = nullptr;
    MonitorAudioLevel* audio_meter = nullptr;
    
    void BuildUI();
};

END_UPP_NAMESPACE

#endif
