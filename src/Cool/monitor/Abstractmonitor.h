/*
    SPDX-FileCopyrightText: 2011 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_monitor_AbstractMonitor_h_
#define _Cool_monitor_AbstractMonitor_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

NAMESPACE_UPP

class MonitorManager;

/** @class AbstractRender
    @brief Base class for MLT rendering logic
 */
class AbstractRender {
public:
    AbstractRender(Kdenlive::MonitorId name);
    virtual ~AbstractRender() = default;

    bool send_frame_for_analysis = false;
    bool analyse_audio = false;

    Kdenlive::MonitorId GetId() const { return id; }

    /** @brief Someone needs us to send again a frame. */
    virtual void SendFrameUpdate() = 0;

    // Callbacks replacing Qt Signals
    Callback1<const Image&> WhenFrameUpdated;
    Callback4<const audioShortVector&, int, int, int> WhenAudioSamples;
    Callback WhenScopesClear;

protected:
    Kdenlive::MonitorId id;
};

/** @class AbstractMonitor
    @brief Base class for UI monitor widgets
 */
class AbstractMonitor : public ParentCtrl {
public:
    AbstractMonitor(Kdenlive::MonitorId id, MonitorManager* manager);
    virtual ~AbstractMonitor() = default;

    Kdenlive::MonitorId GetId() const { return id; }
    
    virtual void Mute(bool mute) = 0;
    virtual void Stop() = 0;
    virtual void Start() = 0;
    virtual void Play() = 0;
    virtual void Rewind(double speed = 0) = 0;
    virtual void Forward(double speed = 0, bool allow_normal_play = false) = 0;
    virtual void RefreshMonitorIfActive(bool direct_update = false) = 0;
    virtual void MouseSeek(int event_delta, int modifiers) = 0;
    virtual void SwitchFullScreen(bool minimize_only = false) = 0;

    // Callbacks replacing Qt Signals
    Callback1<const Image&> WhenFrameUpdated;
    Callback4<const audioShortVector&, int, int, int> WhenAudioSamples;
    Callback WhenScopesClear;

protected:
    Kdenlive::MonitorId id;
    MonitorManager* monitor_manager;
};

END_UPP_NAMESPACE

#endif
